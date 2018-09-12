#include "GraphicObject.h"

GraphicObject::GraphicObject(std::string path) {
	img = IMG_Load(path.c_str());
  rect.w = img->w;
  rect.h = img->h;
}

void GraphicObject::render(SDL_Surface * target, int x, int y) {
	rect.x = x;
	rect.y = y;
	SDL_BlitSurface(img, NULL, target, &rect);
}

void GraphicObject::free() {
	SDL_FreeSurface(img);
}

void GraphicObject::setSize(int w, int h){
	rect.w = w;
	rect.h = h;
}

SDL_Rect GraphicObject::getPos(){
	return rect;
}

GraphicObject::~GraphicObject(){

}
