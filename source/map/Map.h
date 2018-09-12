#ifndef MAP_H
#define MAP_H

#include <string>
#include <fstream>

class Map{
public:
  static const int WIDTH      = 15;
  static const int HEIGHT     = 10;
  static const int BLOCK_SIZE = 64;

  int map[HEIGHT][WIDTH+2];

  Map(std::string path);

};

#endif
