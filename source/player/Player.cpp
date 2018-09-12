#include "Player.h"

Player::Player(){
  x   = 0;
  y   = 0;
  dir = 1;

  speed  = 6;
  hasKey = false;
  moving = false;
}

void Player::update(Map map){
  // ANIMATION
  if(animation_counter < 29)
    animation_counter++;
  else
    animation_counter = 0;
  animation = animation_counter/10;
  // --------

  if(moving){
    switch(dir){
      case 0: // LEFT
        if(map.map[y/(Map::BLOCK_SIZE)][(x-speed+10)/(Map::BLOCK_SIZE)] == 0 &&
           map.map[(y+60)/(Map::BLOCK_SIZE)][(x-speed+10)/(Map::BLOCK_SIZE)] == 0)
          x -= speed;
        break;
      case 1: // RIGHT
        if(map.map[y/(Map::BLOCK_SIZE)][(x+speed+50)/(Map::BLOCK_SIZE)] == 0 &&
           map.map[(y+60)/(Map::BLOCK_SIZE)][(x+speed+50)/(Map::BLOCK_SIZE)] == 0)
          x += speed;
        break;
      case 2: // UP
        if(map.map[(y-speed)/(Map::BLOCK_SIZE)][(x+10)/(Map::BLOCK_SIZE)] == 0 &&
           map.map[(y-speed)/(Map::BLOCK_SIZE)][(x+50)/(Map::BLOCK_SIZE)] == 0)
          y -= speed;
        break;
      case 3: // DOWN
        if(map.map[(y+speed+60)/(Map::BLOCK_SIZE)][(x+10)/(Map::BLOCK_SIZE)] == 0 &&
           map.map[(y+speed+60)/(Map::BLOCK_SIZE)][(x+50)/(Map::BLOCK_SIZE)] == 0)
          y += speed;
        break;
    }
  }
}

int Player::getX(){
  return x;
}

int Player::getY(){
  return y;
}

void Player::setX(int _x){
  x = _x;
}

void Player::setY(int _y){
  y = _y;
}
