#include "Frame.h"

void Frame::change_frame(int id){
  currentFrame = (id < FRAMES_COUNT ? id : currentFrame);
}

int Frame::check_frame(){
  return currentFrame;
}

void Frame::save(int currentMap){
  encryptor.encode(currentMap);
}

int Frame::load(){
  int res = encryptor.decode();
  return res;
}

void Frame::continues(){
  currentFrame = 0;
}
