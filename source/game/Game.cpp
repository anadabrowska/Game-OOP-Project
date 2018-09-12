#include "Game.h"

Game::Game(int currentGame){
  std::fstream file;
  std::string path = "maps/map" + std::to_string(currentGame+1) + ".data";
  file.open(path.c_str());

  int curr = 0, objs_size;
  quest temp;
  std::string line;

  file >> start_x >> start_y >> x >> y >> objs_size;

  for(int i = 0; i < objs_size; i++){
    object temp;
    file >> temp.id >> temp.x >> temp.y;
    objects.push_back(temp);
  }

  while(getline(file, line)){
    if(line == "{") continue;

    if(line == "}" && curr == 0) {
      curr = 1;
    }else if(line == "}" && curr == 1) {
      curr = 0;
      question.push_back(temp);
      temp = quest();
    }else if(curr == 0 && line != "") {
      temp.text.push_back(line);
    }else if(curr == 1) {
      std::stringstream str;
      str << line;
      str >> temp.x >> temp.y;
    }
  }

  file.close();
}

Game::quest Game::get_quest(int id){
  return question[id];
}

int Game::size(){
  return question.size();
}
