#ifndef GRAPHIC_OBJECT_H
#define GRAPHIC_OBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_TTF.h>
#include <string>

class GraphicObject
{
private:
	SDL_Rect rect;
	SDL_Surface * img;
public:
	GraphicObject(std::string path);
	void render(SDL_Surface * target, int x, int y);
	void free();
	void setSize(int w, int h);
	SDL_Rect getPos();
	~GraphicObject();
};

#endif
