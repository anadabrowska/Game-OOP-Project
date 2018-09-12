#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

class Game{
public:
  struct quest{
    int x, y;
    std::vector <std::string> text;
  };
  struct object{
    int id, x, y;
  };

  std::vector <object> objects;
private:
  std::vector <quest> question;
public:
  Game(int currentGame);

  int x, y, start_x, start_y;
  quest get_quest(int id);
  int size();
};

#endif
