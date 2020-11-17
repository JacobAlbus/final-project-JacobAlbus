#include "engine/character.h"
#include "cinder/app/App.h"

namespace jjba_strategy {

Character::Character(const std::string& name,
                     const glm::vec2& position,
                     const std::string& image_path) :
                     kName(name),
                     position_(position){

  ci::fs::path path = ci::fs::path(image_path);
  kImage = ci::gl::Texture::create(ci::loadImage(cinder::app::loadAsset(path)));
}

void Character::UpdatePosition(const glm::vec2 &updated_position) {
  position_ = updated_position;
}

} // namespace jjba_strategy
