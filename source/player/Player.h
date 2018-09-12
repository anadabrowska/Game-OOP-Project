#ifndef PLAYER_H
#define PLAYER_H

#include "../map/Map.h"

class Player {
private:
  int speed;
  int animation_counter;
  int x;
  int y;
public:
  int dir;
  int animation;
  bool moving;
  bool hasKey;

  Player();

  int getX();
  int getY();

  void setX(int _x);
  void setY(int _y);
  void update(Map map);
};

#endif
