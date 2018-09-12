#include "Map.h"

Map::Map(std::string path){
  std::fstream file;
  file.open(path.c_str());

  for(int y = 0; y < HEIGHT; y++)
    for(int x = 0; x < WIDTH+2; x++)
      if(x >= WIDTH)
        map[y][x] = 0;
      else
        file >> map[y][x];

  file.close();
}
