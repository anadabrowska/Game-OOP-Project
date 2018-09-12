#include "Encription.h"

void Encription::encode(int number){
  std::ofstream file;
  file.open("saves/save.data", std::ios::out | std::ios::binary);
  file.write( (char*)&number, sizeof(int));
  file.close();
}

int Encription::decode(){
  std::ifstream file;
  int currentMap;
  file.open("saves/save.data", std::ios::in | std::ios::binary);
  file.read( (char*)&currentMap, sizeof(int));
  file.close();
  return currentMap;
}
