#include "game_obj_h.h"

GameObj::GameObj() {
    pos = vec2(0,0);
    size = vec2(1, 1);
    velocity = vec2(0.0f);
    color = vec3(1.0f);
    rotation = 0.0f;
    texture = Texture();
    isSolid = false;
    isDestroyed = false;
}


GameObj::GameObj(vec2 pos, vec2 size, Texture textureSprite, vec3 color, vec2 velocity) {
    this->pos = pos;
    this->size = size;
    this->velocity = velocity;
    this->color = color;
    this->rotation = 0.0f;
    this->texture = textureSprite;
    this->isSolid = false;
    this->isDestroyed = false;

}
  

void GameObj::Draw(RendererSprite& renderer)
{
    renderer.Draw(this->texture, this->pos, this->size, this->rotation, this->color);
}