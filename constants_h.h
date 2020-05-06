#pragma once
#define BACKGROUND_TEX "background"
#define BLOCK "destroyable_tile"
#define BLOCK_SOLID "non_destroyable_tile"
#define BALL "ball"
#define PADDLE "paddle"
#define PARTICLE "particle"
#define FAILURE_SCREEN_IMAGE "ollie_failed"

//path constants
#define PATH_VERTEX_SHADER_V1 "res/shaders/vertexShaderV1.shader"
#define PATH_FRAGMENT_SHADER_V1 "res/shaders/fragmentShaderV1.shader"
#define PATH_PARTICLE_VERTEX_SHADER "res/shaders/vertexShader_particleSystem.shader"
#define PATH_PARTICLE_FRAGMENT_SHADER "res/shaders/fragmentShader_particleSystem.shader"
#define PATH_SOUND_BGM "res/sounds/background/g2.mp3"
#define PATH_SOUND_FAILED "res/sounds/effects/f.mp3"
#define PATH_SOUND_COLL_SOLID_TILE "res/sounds/effects/solid.wav"
#define PATH_SOUND_TILE_DESTROYED "res/sounds/effects/liquid.wav"

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
#define TEXTURE_PARTICLE "particle"
#define TEXTURE_PADDLE "paddle" 
#define SHADER_VAR_OFFSET "offset"
#define SHADER_VAR_COLOR "color"
