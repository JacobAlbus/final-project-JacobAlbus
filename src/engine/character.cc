#include "engine/character.h"

namespace jjba_strategy {

Character::Character(const std::string& name,
                     bool is_player) :
                     kName(name),
                     is_player_(is_player){

  if(is_player) {
    character_color = ci::Color(0, 0, 0);
  } else {
    character_color = ci::Color(1, 0, 1);
  }
}

} // namespace jjba_strategy
