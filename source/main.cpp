#include "renderer/Renderer.h"

int main (int argc, char** argv){
  if(SDL_Init(SDL_INIT_EVERYTHING) == -1 || TTF_Init() == -1)
    return -1;

  Renderer(960, 640, "Question Rooms v0.2alpha").start();

  return EXIT_SUCCESS;
}
