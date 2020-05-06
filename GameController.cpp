#include"game_controller_h.h"
#include "res_manager_h.h"
#include "renderer_h.h"
#include <iostream>
#include "ball_object.h"
#include "collision_manager.h"
#include "particle_h.h"
#include "audio_h.h"
using namespace std;



RendererSprite *mRenderer;

// The intialize paddle size
const vec2 PADDLE_SIZE(PADDLE_SIZE_X, PADDLE_SIZE_Y);
// The initial velocity of the player paddle
const GLfloat PADDLE_VELOCITY(PADDLE_VEL);

GameObj* mPlayerPaddle;

//Ball code
const vec2 BALL_VEL_ON_START(BALL_VEL_ON_START_X, BALL_VEL_ON_START_Y);
const GLfloat BALL_RADIUS = RADIUS_BALL;

BallObj* mBall;

ParticleEmitter* mParticleEmitter;

AudioManager* mAudio = new AudioManager();




void GameController::Initialize() {

    // Loading the shaders
    ResManager::LoadShader(PATH_VERTEX_SHADER_V1, PATH_FRAGMENT_SHADER_V1, SPRITE_SHADER);
    ResManager::LoadShader(PATH_PARTICLE_VERTEX_SHADER,PATH_PARTICLE_FRAGMENT_SHADER, PARTICLE_SHADER);
    
    // Configuring the shaders
    mat4 projection = ortho(0.0f, static_cast<GLfloat>(this->width),
        static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);

    
    ResManager::GetShader(SPRITE_SHADER).Equip().setInteger(SHADER_VAR_TEX_IMAGE, 0);
    ResManager::GetShader(SPRITE_SHADER).setMatrix4(SHADER_VAR_PROJECTION, projection);
    ResManager::GetShader(PARTICLE_SHADER).Equip().setMatrix4(SHADER_VAR_PROJECTION, projection);
    ResManager::GetShader(PARTICLE_SHADER).setFloat(SHADER_VAR_SCALE, PARTICLE_SCALE_FLOATS);

    Shader shader = ResManager::GetShader(SPRITE_SHADER);
    mRenderer = new RendererSprite(shader);

    init_loadTextures();

    vec2 player_pos = vec2(
        this->width / 2 - PADDLE_SIZE.x / 2,
        this->height - PADDLE_SIZE.y
    );
    mPlayerPaddle = new GameObj(player_pos, PADDLE_SIZE, ResManager::GetTexture(TEXTURE_PADDLE));

    vec2 ball_pos = player_pos + vec2(PADDLE_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);

    mBall = new BallObj(ball_pos, BALL_RADIUS, BALL_VEL_ON_START,
        ResManager::GetTexture(BALL));

    mParticleEmitter = new ParticleEmitter(
        ResManager::GetShader(PARTICLE_SHADER),
        ResManager::GetTexture(TEXTURE_PARTICLE),
        NUM_PARTICLES
    );

    init_loadLevels();

    //start the BGM
    mAudio->PlayTrack(PATH_SOUND_BGM,true); //this will loop indefinitely, since it's the background music

}

void GameController::InputProcessing(GLfloat delta) {
    if (this->state == STATE::ACTIVE)
    {
        GLfloat velocity = PADDLE_VELOCITY * delta;
        // Move playerboard
        if (this->keys[GLFW_KEY_LEFT])
        {
            if (mPlayerPaddle->pos.x >= 0) {
                mPlayerPaddle->pos.x -= velocity;
                if (mBall->isStuck)
                    mBall->pos.x -= velocity;
            }
        }
        if (this->keys[GLFW_KEY_RIGHT])
        {
            if (mPlayerPaddle->pos.x <= this->width - mPlayerPaddle->size.x)
            {
                mPlayerPaddle->pos.x += velocity;
                if (mBall->isStuck)
                    mBall->pos.x += velocity;
            }
        }
        if (this->keys[GLFW_KEY_SPACE])
            mBall->isStuck = false;
    }
}

void GameController::Update(GLfloat delta) {
    if (state == STATE::FAILURE) {
        return;
    }

    //The ball has gone out of the bounds
    if (mBall->pos.y > this->height) {
        state = STATE::FAILURE;
        mAudio->StopAll();
        mAudio->PlayTrack(PATH_SOUND_FAILED,false);
    }


    mBall->Move(delta, this->width);

    //Particle System Update
    mParticleEmitter->Update(delta, *mBall, 2, vec2(mBall->radius / 2.0f));

    //Checking for collisions after the move code
    this->collisionAssessment();
}

void GameController::Render() {
    if (state == STATE::ACTIVE)
    {
        //Drawing the background
        Texture textureBackground = ResManager::GetTexture(BACKGROUND_TEX);
        mRenderer->Draw(textureBackground,
            vec2(0, 0), vec2(this->width, this->height), 0.0f
        );
       
        //Drawing the level elements
        drawCurrentLevel();
        
        //Render the player paddle
        mPlayerPaddle->Draw(*mRenderer);
        

        //Render the particles
        if(!mBall->isStuck)
            mParticleEmitter->Draw();
       
        //Render the ball
        mBall->Draw(*mRenderer);
        
    }
    else if (state == STATE::FAILURE) {
        //Drawing the failure background
        Texture textureBackground = ResManager::GetTexture(FAILURE_SCREEN_IMAGE);
        mRenderer->Draw(textureBackground,
            vec2(0, 0), vec2(this->width, this->height), 0.0f
        );
    }
}

void GameController::drawCurrentLevel() {
    try {

        Level levelToDraw = levels[currentLevel];
        levelToDraw.Draw(*mRenderer);
    }
    catch (exception& e) {
        cerr << "Error drawing level, e: " << e.what() << endl;
    }
}


void GameController::init_loadTextures() {
    ResManager::LoadTexture("res/Textures/city_night.jpg", GL_FALSE, BACKGROUND_TEX);
    ResManager::LoadTexture("res/Textures/ball.png", GL_TRUE, BALL);
    ResManager::LoadTexture("res/Textures/tile_blue.png", GL_FALSE, BLOCK);
    ResManager::LoadTexture("res/Textures/tile_blue_solid.png", GL_FALSE, BLOCK_SOLID);
    ResManager::LoadTexture("res/Textures/paddle2.png", GL_TRUE, PADDLE);
    ResManager::LoadTexture("res/Textures/particle.png", GL_TRUE, PARTICLE);
    ResManager::LoadTexture("res/Textures/failedThisCity.jpg", GL_TRUE, FAILURE_SCREEN_IMAGE);
}

void GameController::init_loadLevels() {
   
    const GLchar* raw_level = "5 5 5 5 5 5 5 5 5 5 5 5 5 5 5\n5 5 4 4 4 0 0 5 5 5 5 5 5 5 5\n4 4 4 4 4 0 0 0 5 5 5 0 0 4 4 4 4 4\n4 1 4 1 4 0 0 1 0 0 3 3 3 0 0 4 1 4 1 4\n3 3  4 1 4 1 0 0 0 3 3 3 3 3\n3 3 1 3 3 3 3 3 3 3 3 3 1 3 3\n2 2 2 2 2 2 2 2 2 2 2 2 2 2 2\n2 2 2 2 2 2 2 2 2 2 2 2 2 2 2";
    Level one;
    one.LoadFromRaw(raw_level, this->width, this->height * 0.5f);
    addLevel(one);
    this->currentLevel = 0;

}

void GameController::addLevel(Level level) {
    this->levels.push_back(level);
}

Level GameController::getCurrentLevel() {
    return this->levels[this->currentLevel];
}

void GameController::collisionAssessment() {
    
    for (GameObj& tile : levels[this->currentLevel].tiles) {
        
        CollisionData* collisionData = &CollisionManager::CheckCollisionAABBCircle(*mBall, tile);
        

        if (collisionData->collisonHappened)
        {
            if (tile.isSolid) {
               
                mAudio->PlayTrack(PATH_SOUND_COLL_SOLID_TILE, false);
                
                //Collision processing

                if (collisionData->direction == UP || collisionData->direction == DOWN) // Collision happened on the y-plane
                {
                    GLfloat y_vec = mBall->velocity.y;
                    mBall->velocity.y = -y_vec;

                }
                else // Collision happened on the x-plane
                {
                    GLfloat x_vec = mBall->velocity.x;
                    mBall->velocity.x = -x_vec;
                }

                
                //I noticed a gltichy behavior in which the ball after collision seems to be 
                //going under the tile before being rebounded, which means I'll have to manually offset by the amount it has gone under

                GLfloat differenceGoneUnder_Y = mBall->radius - collisionData->differenceVector.y;
                GLfloat differenceGoneUnder_X = mBall->radius - collisionData->differenceVector.x;
                Direction collisionDirection = collisionData->direction;

                switch (collisionDirection)
                {
                case UP:
                    mBall->pos.y -= differenceGoneUnder_Y;
                    break;
                case RIGHT:
                    mBall->pos.x += differenceGoneUnder_X;
                    break;
                case DOWN:
                    mBall->pos.y += differenceGoneUnder_Y;
                    break;
                case LEFT:
                    mBall->pos.x -= differenceGoneUnder_X;
                    break;
                case NA:
                    break;
                default:
                    break;
                }
            
            }
            else {
                
                if(!tile.isDestroyed)
                    mAudio->PlayTrack(PATH_SOUND_TILE_DESTROYED, false);
               
               
                tile.isDestroyed = GL_TRUE;
            }

            
            
        }
    }

    //Collision check with the paddle
    if (CollisionManager::CheckCollisionAABBCircle(*mBall, *mPlayerPaddle).collisonHappened) {
        mBall->velocity.y =  -abs(mBall->velocity.y);
    }

   }
     
