#ifndef FRAME_H
#define FRAME_H

#include <fstream>
#include "Encription.h"

class Frame{
private:
  int currentFrame;
  Encription encryptor;
public:
  static const int FRAMES_COUNT = 2;

  void save(int currentMap);
  int load();
  void continues();
  void change_frame(int id);
  int check_frame();
};

#endif
