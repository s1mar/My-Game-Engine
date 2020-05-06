#pragma once

#include<glew.h>
#include<glfw3.h>
#include<vector>
#include"game_level_h.h"
#include "constants_h.h"

enum class STATE{ACTIVE,MENU,WIN,FAILURE};

class GameController {

public: 
	STATE state;
	GLboolean keys[1024];
	GLuint width, height;
	

	GameController(GLuint width, GLuint height) {
		this->width = width;
		this->height = height;
		state = STATE::ACTIVE;
		currentLevel = 0;
		levels = {};
	}

	void Initialize();
	void InputProcessing(GLfloat delta);
	void Update(GLfloat delta);
	void Render();
	vector<Level> levels;
	GLuint currentLevel;
	
	
private:
	
	void init_loadTextures();
	void init_loadLevels(); 
	void collisionAssessment();
	Level getCurrentLevel();
	void addLevel(Level level);
	void drawCurrentLevel();
};
