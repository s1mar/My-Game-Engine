#pragma once
#include<vector>
#include"game_obj_h.h"
#include <fstream>
#include<sstream>
#include"res_manager_h.h"
#include "constants_h.h"
using namespace std;
using namespace glm;
class Level {

	public:
		
		vector<GameObj> tiles;

		Level() {}
		Level(const GLchar* file, GLuint width, GLuint height) {
			this->Load(file, width, height);
		}
		//load level from file
		void Load(const GLchar* file, GLuint width, GLuint height);
		void LoadFromRaw(const GLchar* file, GLuint width, GLuint height);
		void Draw(RendererSprite& renderer);

		GLboolean isCompleted();

	private:
		void Initialize(GLuint width, GLuint height, vector<vector<GLuint>> tileData);

};