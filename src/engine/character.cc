#include "engine/character.h"

namespace jjba_strategy {

Character::Character(const std::string& name,
                     bool is_player,
                     const glm::vec2& position) :
                     kName(name),
                     is_player_(is_player),
                     position_(position){

  if(is_player) {
    color_ = ci::Color(0, 0, 0);
  } else {
    color_ = ci::Color(1, 0, 1);
  }
}

} // namespace jjba_strategy
