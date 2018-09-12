#include "Renderer.h"

const std::string Renderer::menu_items[MAX_MENU] = {
  "Continue",
  "Save",
  "Load",
  "Exit"
};

Renderer::Renderer(int _WIDTH, int _HEIGHT, std::string title){
  WIDTH  = _WIDTH;
  HEIGHT = _HEIGHT;

  quest = false;

  currentMap = -1;
  currentQuest = 0;
  currentMenuItem = 0;

  font = TTF_OpenFont("fonts/main_font2.ttf", FONT_SIZE);

  if(font == nullptr)
    exit(0);

  textColor.r = 0;
  textColor.g = 0;
  textColor.b = 0;
  textColor.a = 255;

	window = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		_WIDTH,
		_HEIGHT,
		0
  );

  nextMap();

	screen = SDL_GetWindowSurface(window);
}

Renderer::~Renderer(){
  for (int i = 0;i < objs.size(); i++)
		objs[i].free();

	SDL_Quit();
}

void Renderer::start(){
	load();

	while (running) {
		SDL_UpdateWindowSurface(window);

    player.update(maps[currentMap]);
		refresh();

    if(player.hasKey && player.getX() > (Map::WIDTH + 1) * Map::BLOCK_SIZE)
      nextMap();

    SDL_Delay(17); // 1000/60 fps
	}
}

void Renderer::load(){

  //GRAPHIC
	objs.push_back(GraphicObject("graphics/wood4.jpg"));
  objs.push_back(GraphicObject("graphics/black.png"));
  objs.push_back(GraphicObject("graphics/stone2.png"));
  objs.push_back(GraphicObject("graphics/stone2.png"));
  objs.push_back(GraphicObject("graphics/stone2.png"));

  //OBJECTS
  objs.push_back(GraphicObject("graphics/key2.png"));
  objs.push_back(GraphicObject("graphics/paper.png"));
  objs.push_back(GraphicObject("graphics/bookshelf.png"));
  objs.push_back(GraphicObject("graphics/shelf1.png"));
  objs.push_back(GraphicObject("graphics/shelf2.png"));
  objs.push_back(GraphicObject("graphics/shelf3.png"));
  objs.push_back(GraphicObject("graphics/shelf4.png"));
  objs.push_back(GraphicObject("graphics/box.png"));
  objs.push_back(GraphicObject("graphics/table.png"));
  objs.push_back(GraphicObject("graphics/fireplace.png"));
  objs.push_back(GraphicObject("graphics/wardrobe.png"));
  objs.push_back(GraphicObject("graphics/skull.png"));
  
  //MENU
  objs.push_back(GraphicObject("graphics/menu/background_menu.jpg"));
  objs.push_back(GraphicObject("graphics/menu/btn_norm.png"));
  objs.push_back(GraphicObject("graphics/menu/btn_down.png"));

  //PLAYER
  objs.push_back(GraphicObject("graphics/64/left1.png"));
  objs.push_back(GraphicObject("graphics/64/right1.png"));
  objs.push_back(GraphicObject("graphics/64/back1.png"));
  objs.push_back(GraphicObject("graphics/64/front1.png"));

  objs.push_back(GraphicObject("graphics/64/left2.png"));
  objs.push_back(GraphicObject("graphics/64/right2.png"));
  objs.push_back(GraphicObject("graphics/64/back2.png"));
  objs.push_back(GraphicObject("graphics/64/front2.png"));

  objs.push_back(GraphicObject("graphics/64/left3.png"));
  objs.push_back(GraphicObject("graphics/64/right3.png"));
  objs.push_back(GraphicObject("graphics/64/back3.png"));
  objs.push_back(GraphicObject("graphics/64/front3.png"));

  //MAPS
  maps.push_back(Map("maps/map1.level"));
  maps.push_back(Map("maps/map2.level"));
  maps.push_back(Map("maps/map3.level"));

	running = true;
}

void Renderer::refresh(){
	while (SDL_PollEvent(&event)){
		if (event.type == SDL_QUIT)
      running = false;
    else if(event.type == SDL_KEYDOWN)
      keyboardManager(event.key.keysym.sym);
    else if(event.type == SDL_KEYUP)
      player.moving = false;
  }
  if(frame.check_frame() == 0) {

    for(int y = 0; y < maps[currentMap].HEIGHT; y++){
      for(int x = 0; x < maps[currentMap].WIDTH; x++){
        objs[maps[currentMap].map[y][x]].render(
          screen,
          x * Map::BLOCK_SIZE,
          y * Map::BLOCK_SIZE
        );
      }
    }

    for(int i = 0; i < game->objects.size(); i++){
      objs[game->objects[i].id].render(
        screen,
        game->objects[i].x * Map::BLOCK_SIZE,
        game->objects[i].y * Map::BLOCK_SIZE
      );
    }

    if(!player.hasKey){
      objs[5].render(
        screen,
        game->x * Map::BLOCK_SIZE,
        game->y * Map::BLOCK_SIZE
      );
    }

    objs[PLAYER_INDEX_GFX+player.dir+(player.moving?player.animation*4:4)].render(
      screen,
      player.getX(),
      player.getY()
    );

    if(quest)
      OpenQuest();
  }else if(frame.check_frame() == 1){
    int space = 20;
    int btw = objs[18].getPos().w;
    int bth = objs[18].getPos().h;
    int pos_x = WIDTH/2 + btw/3;
    int pos_y = bth + space;
    int offset = (HEIGHT - 4 * pos_y)/2;

    objs[17].render(screen, 0, 0);
    for(int i=0;i<MAX_MENU;i++){
      if(i == currentMenuItem)
        objs[18].render(
          screen,
          pos_x,
          pos_y * i + offset
        );
      else
        objs[19].render(
          screen,
          pos_x,
          pos_y * i + offset
        );

      drawText(
        menu_items[i],
        pos_x + (btw - (FONT_SIZE/2 * menu_items[i].length()))/2,
        pos_y * i + offset + (bth - FONT_SIZE)/2
      );
    }
  }
}

void Renderer::keyboardManager(int key){
  int frm = frame.check_frame();
  switch(key){
    case SDLK_ESCAPE:
      if(quest){
        quest = false;
        break;
      }
      frame.change_frame((frm == 0 ? 1 : 0));
      break;
    case SDLK_LEFT:
      if(frm == 0){
        player.moving = true;
        player.dir = 0;
      }
      break;
    case SDLK_RIGHT:
      if(frm == 0){
        player.moving = true;
        player.dir = 1;
      }
      break;
    case SDLK_UP:
      if(frm == 0){
        player.moving = true;
        player.dir = 2;
      }else if(frm == 1){
        currentMenuItem -= (currentMenuItem > 0 ? 1 : -MAX_MENU + 1);
      }
      break;
    case SDLK_DOWN:
      if(frm == 0){
        player.moving = true;
        player.dir = 3;
      }else if(frm == 1){
        currentMenuItem += (currentMenuItem < MAX_MENU-1 ? 1 : -MAX_MENU + 1);
      }
      break;
    case SDLK_z:
      if(frm == 0){
        if( player.getX() + Map::BLOCK_SIZE > game->x * Map::BLOCK_SIZE &&
            player.getX() < (game->x + 1) * Map::BLOCK_SIZE &&
            player.getY() + Map::BLOCK_SIZE > game->y * Map::BLOCK_SIZE &&
            player.getY() < (game->y +1) * Map::BLOCK_SIZE){
          player.hasKey = true;
          unlockExitDoors();
        }else if(player.getX() + Map::BLOCK_SIZE > game->get_quest(currentQuest).x * Map::BLOCK_SIZE &&
                 player.getX() < (game->get_quest(currentQuest).x + 1) * Map::BLOCK_SIZE &&
                 player.getY() + Map::BLOCK_SIZE > game->get_quest(currentQuest).y * Map::BLOCK_SIZE &&
                 player.getY() < (game->get_quest(currentQuest).y +1) * Map::BLOCK_SIZE){
          nextQuest();
        }
      }
      break;
    case SDLK_c:
      if(frm == 0){
        quest = !quest;
      }
      break;
    case SDLK_RETURN:
      if(frm == 1){
        switch(currentMenuItem){
          case 0:
            frame.continues();
            break;
          case 1:
            frame.save(currentMap);
            frame.continues();
            break;
          case 2:
            setMap(frame.load());
            frame.continues();
            break;
          case 3:
            running = false;
            break;
        }
      }
      break;
  }
}

void Renderer::unlockKeyDoors(){
  for(int y = 0; y < Map::HEIGHT; y++)
    for(int x = 0; x < Map::WIDTH; x++)
      if(maps[currentMap].map[y][x] == 3)
        maps[currentMap].map[y][x] = 0;
}

void Renderer::unlockExitDoors(){
  for(int y = 0; y < Map::HEIGHT; y++)
    for(int x = 0; x < Map::WIDTH; x++)
      if(maps[currentMap].map[y][x] == 4)
        maps[currentMap].map[y][x] = 0;
}

void Renderer::OpenQuest(){
  int pos_x = WIDTH/2 - objs[6].getPos().w/2;
  int pos_y = HEIGHT/2 - objs[6].getPos().h/2;
  objs[6].render(screen,pos_x,pos_y);
  Game::quest temp = game->get_quest(currentQuest);
  for(int i = 0; i < temp.text.size(); i++)
    drawText(
      temp.text[i],
      pos_x+75,
      pos_y+100+(i*(FONT_SIZE+10))
    );
}

void Renderer::setMap(int id){
  currentMap = id;
  currentQuest = 0;
  game = new Game(currentMap);
  player.setX(game->start_x * Map::BLOCK_SIZE);
  player.setY(game->start_y * Map::BLOCK_SIZE);
  player.hasKey = false;
  quest = true;
}

void Renderer::nextMap(){
  currentMap++;
  currentQuest = 0;
  game = new Game(currentMap);
  player.setX(game->start_x * Map::BLOCK_SIZE);
  player.setY(game->start_y * Map::BLOCK_SIZE);
  player.hasKey = false;
  quest = true;
}

void Renderer::nextQuest(){
  if(currentQuest < game->size() - 2){
    currentQuest++;
    quest = true;
  }
  else if(currentQuest < game->size() - 1){
    currentQuest++;
    unlockKeyDoors();
    quest = true;
  }
}

void Renderer::drawText(std::string s, int x, int y){
  textRect.x = x;
  textRect.y = y;
  textRect.w = 400;
  textRect.h = 400;
  textSurface = TTF_RenderText_Blended(font, s.c_str(), textColor);
  SDL_BlitSurface(textSurface, NULL, screen, &textRect);
}
