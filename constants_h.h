#pragma once
//texture constants
#define TEXTURE_BALL "ball"
#define TEXTURE_BACKGROUND "background"
#define TEXTURE_TILE "destroyable_tile"
#define TEXTURE_TILE_SOLID "non_destroyable_tile"
#define TEXTURE_PARTICLE "particle"
#define TEXTURE_PADDLE "paddle" 
#define TEXTURE_PARTICLE "particle"
#define TEXTURE_FAILURE_SCREEN_IMAGE "ollie_failed"
#define TEXTURE_MENU_SCREEN "menu"

//path constants
#define PATH_VERTEX_SHADER_V1 "res/shaders/vertexShaderV1.shader"
#define PATH_FRAGMENT_SHADER_V1 "res/shaders/fragmentShaderV1.shader"
#define PATH_PARTICLE_VERTEX_SHADER "res/shaders/vertexShader_particleSystem.shader"
#define PATH_PARTICLE_FRAGMENT_SHADER "res/shaders/fragmentShader_particleSystem.shader"
#define PATH_SOUND_BGM "res/sounds/background/g2.mp3"
#define PATH_SOUND_FAILED "res/sounds/effects/f.mp3"
#define PATH_SOUND_COLL_SOLID_TILE "res/sounds/effects/solid.wav"
#define PATH_SOUND_TILE_DESTROYED "res/sounds/effects/liquid.wav"
#define PATH_SOUND_BGM_MENU "res/sounds/background/g_menu.mp3"
#define PATH_LVL_1 "res/levels/uno.level"
#define PATH_LVL_2 "res/levels/duo.level"
#define PATH_LVL_3 "res/levels/tres.level"
#define LVL1_BACKGROUND_PATH "res/Textures/b1.jpg"
#define LVL2_BACKGROUND_PATH "res/Textures/b2.png"
#define LVL3_BACKGROUND_PATH "res/Textures/b3.png"
#define LVL1_BALL_PATH "res/Textures/ball_blue.png"
#define LVL2_BALL_PATH "res/Textures/ball_green.png"
#define LVL3_BALL_PATH "res/Textures/ball_red.png"
#define LVL1_TILE_PATH "res/Textures/tile_blue.png"
#define LVL2_TILE_PATH "res/Textures/tile_green.png"
#define LVL3_TILE_PATH "res/Textures/tile_red.png"
#define LVL1_TILE_SOLID_PATH "res/Textures/tile_blue_solid.png"
#define LVL2_TILE_SOLID_PATH "res/Textures/tile_green_solid.png"
#define LVL3_TILE_SOLID_PATH "res/Textures/tile_red_solid.png"
#define LVL1_PADDLE_PATH "res/Textures/paddle_blue.png"
#define LVL2_PADDLE_PATH "res/Textures/paddle_green.png"
#define LVL3_PADDLE_PATH "res/Textures/paddle_red.png"
#define PATH_TEXTURE_PARTICLE "res/Textures/particle.png"
#define PATH_TEXTURE_FAIL_SCREEN "res/Textures/failedThisCity.png"
#define PATH_TEXTURE_MENU_SCREEN "res/Textures/menu.png"

//value constants
#define RADIUS_BALL 14.0f
#define PADDLE_SIZE_X 100
#define PADDLE_SIZE_Y 20
#define PADDLE_VEL 520.0f
#define BALL_VEL_ON_START_X   200.0f
#define BALL_VEL_ON_START_Y  -700.0f
#define PARTICLE_SCALE_FLOATS 12.0f
#define FPS_TEXT_UPDATE_FREQUENCY 0.25f
#define NUM_PARTICLES 450

//color holders
#define COLOR_TILE_TYPE_2 1, 0.627, 0.478   
#define COLOR_TILE_TYPE_3 0, 0.501, 0.501   
#define COLOR_TILE_TYPE_4 0, 0.392, 0       
#define COLOR_TILE_TYPE_5 0.274, 0.509, 0.705

//Shader Constants
#define SHADER_MODEL "model"
#define SHADER_SPRITE_COLOR "spriteColor"
#define PARTICLE_SHADER "particle_shader"
#define SPRITE_SHADER "sprite_shader"
#define SHADER_VAR_TEX_IMAGE "texImage"
#define SHADER_VAR_PROJECTION "projection"
#define SHADER_VAR_SCALE "scale"
#define SHADER_VAR_OFFSET "offset"
#define SHADER_VAR_COLOR "color"
