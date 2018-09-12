#ifndef RENDERER_H
#define RENDERER_H

#define PLAYER_INDEX_GFX 20
#define FONT_SIZE        40
#define MAX_MENU         4

#include <iostream>
#include "GraphicObject.h"
#include "Frame.h"
#include "../map/Map.h"
#include "../player/Player.h"
#include "../game/Game.h"

class Renderer {
private:
  int WIDTH;
  int HEIGHT;

  int currentMap, currentQuest, currentMenuItem;

	SDL_Window  * window;
	SDL_Surface * screen;
	SDL_Event     event;

  SDL_Surface * textSurface;
  TTF_Font    * font;
  SDL_Color     textColor;
  SDL_Rect      textRect;

	std::vector <GraphicObject> objs;
  std::vector <Map> maps;

  Player player;
  Frame frame;
  Game * game;

	bool running;
  bool quest;

  void unlockKeyDoors();
  void unlockExitDoors();
  void OpenQuest();
  void nextMap();
  void nextQuest();
  void drawText(std::string s, int x, int y);
public:
  static const std::string menu_items[MAX_MENU];

	Renderer(int _WIDTH, int _HEIGHT, std::string title);
  ~Renderer();

  void setMap(int id);
	void load();
	void start();
	void refresh();
  void keyboardManager(int key);
};

#endif
