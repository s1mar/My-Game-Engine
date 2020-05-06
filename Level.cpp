#include "game_level_h.h"

void Level::Load(const GLchar* file, GLuint width, GLuint height) {

    // A fresh start; clearing old objects before starting anew
    this->tiles.clear();

    // Load from file
    GLuint tileCode;
    Level level;
    string line;
    ifstream fileStream(file);

    vector<vector<GLuint>> tileData;

    if (fileStream)
    {
        while (getline(fileStream, line)) // Read each line from level file
        {
            istringstream is_stream(line);
            vector<GLuint> row;
            while (is_stream >> tileCode) // Read each word seperated by spaces
                row.push_back(tileCode);
            tileData.push_back(row);
        }
        if (tileData.size() > 0)
            this->Initialize(width, height, tileData);
    }
}

void Level::LoadFromRaw(const GLchar* file, GLuint width, GLuint height){
    // A fresh start; clearing old objects before starting anew
    this->tiles.clear();
    // Load from file
    Level level;
    vector<vector<GLuint>> tileData;
    vector<GLuint> row;
    int length = strlen(file);
    for (int i = 0; i <length ; i++) {
            GLchar tileCode = file[i];
            if (tileCode == '\n') {
                tileData.push_back(row);
                row = vector<GLuint>(); //replacing the row with a fresh reference
            }
            else if (!isspace(tileCode)){
                row.push_back(tileCode-'0');
            }
    }
        if (tileData.size() > 0)
            this->Initialize(width, height, tileData);
    
}
    
void Level::Initialize(GLuint scrWidth, GLuint scrHeight, vector<vector<GLuint>> tileData) {
    
    // Calculating the tile dimensions
    GLuint tileHeight = tileData.size();
    GLuint tileWidth = tileData[0].size(); //Since all the tiles are same in dimension, we can just take the size of any one element
    
    GLfloat unit_width = scrWidth / static_cast<GLfloat>(tileWidth); //Dividing the width of the level by a tile width(since all tiles are common in dimens) to get the unit width
    GLfloat unit_height = scrHeight / tileHeight;                    //Similarly, for height as well
    
    // Initialize the tiles on the level based 
   
    for (GLuint y = 0; y < tileHeight; ++y)
    {
        for (GLuint x = 0; x < tileWidth; ++x) {
            // Check block type from level data 
            GLuint tileType = tileData[y][x]; //to see if it's an empty space, an indestructible tile or a destructible 
            if (tileType == 1) // Solid
            {
                vec2 pos(unit_width * x, unit_height * y);
                vec2 size(unit_width, unit_height);
                GameObj tileObj(pos, size,
                    ResManager::GetTexture(TEXTURE_TILE_SOLID),
                    vec3(0.8f, 0.8f, 0.7f)
                );
                tileObj.isSolid = GL_TRUE;
                this->tiles.push_back(tileObj);
            }
            else if (tileType > 1) //It's a destroyable tile with the color varying with magnitude
            {
                vec3 color = vec3(1.0f); // base color; default color of white

                switch (tileType) {
                case 2:
                    color = vec3(COLOR_TILE_TYPE_2); //blue
                    break;
                case 3:
                    color = vec3(COLOR_TILE_TYPE_3); //green
                    break;
                case 4:
                    color = vec3(COLOR_TILE_TYPE_4); //yellow-green; mustard
                    break;
                case 5:
                    color = vec3(COLOR_TILE_TYPE_5); //orange
                    break;

                }

                vec2 pos(unit_width * x, unit_height * y);
                vec2 size(unit_width, unit_height);

                this->tiles.push_back(
                    GameObj(pos, size, ResManager::GetTexture(TEXTURE_TILE), color)
                );
            }
        }
        
    }



}

void Level::Draw(RendererSprite& renderer)
{
    for (auto& tile : this->tiles)
    {
        if (!tile.isDestroyed) { //if the tile isn't isDestroyed, draw it
            tile.Draw(renderer);
        }
    }
}

GLboolean Level::isCompleted()
{
    for (auto& tile : this->tiles)
        if (!tile.isSolid && !tile.isDestroyed) {
            return GL_FALSE;
        }
    return GL_TRUE;
}
