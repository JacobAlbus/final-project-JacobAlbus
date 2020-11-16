#include "engine/character.h"
#include "cinder/app/App.h"

namespace jjba_strategy {

Character::Character(const std::string& name,
                     bool is_player,
                     const glm::vec2& position,
                     const std::string& image_path) :
                     kName(name),
                     is_player_(is_player),
                     position_(position){

  ci::fs::path path = ci::fs::path(image_path);
  kImage = ci::gl::Texture::create(ci::loadImage(cinder::app::loadAsset(path)));

  if(is_player) {
    color_ = ci::Color(0, 0, 0);
  } else {
    color_ = ci::Color(1, 0, 1);
  }
}

void Character::UpdatePosition(const glm::vec2 &updated_position) {
  position_ = updated_position;
}

} // namespace jjba_strategy
