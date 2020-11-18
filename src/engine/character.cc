#include "engine/character.h"
#include "cinder/app/App.h"

namespace jjba_strategy {

Character::Character(const std::string& name,
                     const glm::vec2& position,
                     const std::string& image_path,
                     bool is_player) :
                     kName(name),
                     position_(position),
                     is_player_(is_player) {

  ci::fs::path path = ci::fs::path(image_path);
  kImage = ci::gl::Texture::create(ci::loadImage(cinder::app::loadAsset(path)));
}

void Character::UpdatePosition(const glm::vec2 &updated_position) {
  position_ = updated_position;
}

void Character::UpdateIsPlayer() {
  is_player_ = !is_player_;
}

void Character::RenderCharacter(const ci::Rectf& character_location) const {
  if(is_player_) {
    ci::gl::color(ci::Color("gray"));
  } else {
    ci::gl::color(ci::Color("white"));
  }

  ci::gl::draw(kImage, character_location);
}

} // namespace jjba_strategy
