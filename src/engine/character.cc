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
}

Character& Character::operator=(const Character& rhs) {
  kImage = rhs.kImage;
  kName = rhs.kName;
  position_ = rhs.position_;
  is_player_ = rhs.is_player_;

  return *this;
}

void Character::UpdatePosition(const glm::vec2 &updated_position) {
  position_ = updated_position;
}

} // namespace jjba_strategy
