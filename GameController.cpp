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

    //Loading textures that will be reused throughout
    ResManager::LoadTexture(PATH_TEXTURE_PARTICLE, GL_TRUE, TEXTURE_PARTICLE);
    ResManager::LoadTexture(PATH_TEXTURE_FAIL_SCREEN, GL_TRUE, TEXTURE_FAILURE_SCREEN_IMAGE);
    ResManager::LoadTexture(PATH_TEXTURE_MENU_SCREEN, GL_FALSE, TEXTURE_MENU_SCREEN);

    
    loadMenu();
   

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
    else if (state == STATE::MENU) {
       
        if (keys[GLFW_KEY_1]) {
            //Load level 1
            loadLevel(1);
        }
        else if (keys[GLFW_KEY_2]) {
            //Load level 2
            loadLevel(2);
        }
        else if (keys[GLFW_KEY_3]) {
            //Load level 3
            loadLevel(3);
        }
        
    }
    else if (state == STATE::FAILURE) {
        
        if (keys[GLFW_KEY_M]) {
            
            loadMenu();
        }
    
    }
}


void GameController :: loadMenu() {
    state = STATE::MENU;
    mAudio->StopAll();
    mAudio->PlayTrack(PATH_SOUND_BGM_MENU, true);
}

void GameController::loadLevel(int levelIndex) {
    state = STATE::ACTIVE;
    
    //Setting the current level
    this->currentLevel = 0; //Since I've rolled back the code to just having one level loaded at an instance, this will always point to the zeroeth index

    //Load Level Respective Textures
    const char* pathToBackgroundTexture;
    const char* pathToPaddleTexture;
    const char* pathToTileTexture;
    const char* pathToBallTexture;
    const char* pathToTileSolidTexture;
    
    switch (levelIndex)
    {
    
    default:
    case 1:
        pathToBackgroundTexture = LVL1_BACKGROUND_PATH;
        pathToPaddleTexture = LVL1_PADDLE_PATH;
        pathToBallTexture = LVL1_BALL_PATH;
        pathToTileTexture = LVL1_TILE_PATH;
        pathToTileSolidTexture = LVL1_TILE_SOLID_PATH;
        break;
    case 2:
        pathToBackgroundTexture = LVL2_BACKGROUND_PATH;
        pathToPaddleTexture = LVL2_PADDLE_PATH;
        pathToBallTexture = LVL2_BALL_PATH;
        pathToTileTexture = LVL2_TILE_PATH;
        pathToTileSolidTexture = LVL2_TILE_SOLID_PATH;
        break;
    case 3:
        pathToBackgroundTexture = LVL3_BACKGROUND_PATH;
        pathToPaddleTexture = LVL3_PADDLE_PATH;
        pathToBallTexture = LVL3_BALL_PATH;
        pathToTileTexture = LVL3_TILE_PATH;
        pathToTileSolidTexture = LVL3_TILE_SOLID_PATH;
        break;
    }

    //Load Level Specific textures
    loadLevelTextures(pathToBackgroundTexture, pathToPaddleTexture, pathToTileTexture, pathToTileSolidTexture, pathToBallTexture);

    //Clearing the exisiting level(s) for I want the now being loaded level to be start anew (state resetted)
    levels.clear();


    loadLevelDataFromFile(levelIndex);
   
    
    vec2 player_pos = vec2(
        this->width / 2 - PADDLE_SIZE.x / 2,
        this->height - PADDLE_SIZE.y
    );
    mPlayerPaddle = new GameObj(player_pos, PADDLE_SIZE, ResManager::GetTexture(TEXTURE_PADDLE));

    vec2 ball_pos = player_pos + vec2(PADDLE_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);

    mBall = new BallObj(ball_pos, BALL_RADIUS, BALL_VEL_ON_START,
        ResManager::GetTexture(TEXTURE_BALL));

    mParticleEmitter = new ParticleEmitter(
        ResManager::GetShader(PARTICLE_SHADER),
        ResManager::GetTexture(TEXTURE_PARTICLE),
        NUM_PARTICLES
    );

    mAudio->StopAll();

    //start the BGM
    mAudio->PlayTrack(PATH_SOUND_BGM, true); //this will loop indefinitely, since it's the background music
}

void GameController::Update(GLfloat delta) {
    if (state == STATE::FAILURE || state == STATE::MENU) {
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
        Texture textureBackground = ResManager::GetTexture(TEXTURE_BACKGROUND);
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
        Texture textureBackground = ResManager::GetTexture(TEXTURE_FAILURE_SCREEN_IMAGE);
        mRenderer->Draw(textureBackground,
            vec2(0, 0), vec2(this->width, this->height), 0.0f
        );
    }
    else if (state == STATE::MENU) {
        //Drawing the menu
        Texture menuBack = ResManager::GetTexture(TEXTURE_MENU_SCREEN);
        mRenderer->Draw(menuBack, vec2(0, 0), vec2(this->width, this->height), 0.0f
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


void GameController::loadLevelTextures(const char* tBackground, const char* tPaddle, const char* tTile, const char* tTileSolid, const char* tBall) {
    
    ResManager::UnloadTexture(TEXTURE_BACKGROUND);
    ResManager::UnloadTexture(TEXTURE_BALL);
    ResManager::UnloadTexture(TEXTURE_TILE);
    ResManager::UnloadTexture(TEXTURE_TILE_SOLID);
    ResManager::UnloadTexture(TEXTURE_PADDLE);

    ResManager::LoadTexture(tBackground, GL_FALSE, TEXTURE_BACKGROUND);
    ResManager::LoadTexture(tBall, GL_TRUE, TEXTURE_BALL);
    ResManager::LoadTexture(tTile, GL_TRUE, TEXTURE_TILE);
    ResManager::LoadTexture(tTileSolid, GL_TRUE, TEXTURE_TILE_SOLID);
    ResManager::LoadTexture(tPaddle, GL_TRUE, TEXTURE_PADDLE);
   
}

//Deprecated
void GameController::init_loadLevels_RAW() {
   
    const GLchar* raw_level = "5 5 5 5 5 5 5 5 5 5 5 5 5 5 5\n5 5 4 4 4 0 0 5 5 5 5 5 5 5 5\n4 4 4 4 4 0 0 0 5 5 5 0 0 4 4 4 4 4\n4 1 4 1 4 0 0 1 0 0 3 3 3 0 0 4 1 4 1 4\n3 3  4 1 4 1 0 0 0 3 3 3 3 3\n3 3 1 3 3 3 3 3 3 3 3 3 1 3 3\n2 2 2 2 2 2 2 2 2 2 2 2 2 2 2\n2 2 2 2 2 2 2 2 2 2 2 2 2 2 2";
    Level one;
    one.LoadFromRaw(raw_level, this->width, this->height * 0.5f);
    addLevel(one);
}


void GameController::loadLevelDataFromFile(GLuint levelIndex) {

    if (levelIndex == 1) {
        Level one(PATH_LVL_1, this->width, this->height * 0.5f);
        addLevel(one);
    }
    else if (levelIndex == 2)
    {
        Level two(PATH_LVL_2, this->width, this->height * 0.5f);
        addLevel(two);
    }
    else if (levelIndex == 3) {
        Level three(PATH_LVL_3, this->width, this->height * 0.5f);
        addLevel(three);
    }
    
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
     
