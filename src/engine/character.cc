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

void Character::RenderCharacter(size_t board_size, float window_size) const {
  if(is_player_) {
    ci::gl::color(ci::Color("white"));
  } else {
    ci::gl::color(ci::Color("gray"));
  }

  ci::Rectf pixel_bounding_box = CalculatePixelBoundingBox(board_size,
                                                           window_size);
  ci::gl::draw(kImage, pixel_bounding_box);
}

ci::Rectf Character::CalculatePixelBoundingBox(size_t board_size,
                                               float window_size)
                                               const {
  const auto kTileSize = static_cast<float>(window_size / board_size);
  float col = position_.y;
  float row = position_.x;

  glm::vec2 pixel_top_left = glm::vec2(col * kTileSize, row * kTileSize);
  glm::vec2 pixel_bottom_right = pixel_top_left +
                                 glm::vec2(kTileSize, kTileSize);

  //TODO isn't passing by copy slower?
  return ci::Rectf(pixel_top_left, pixel_bottom_right);
}

} // namespace jjba_strategy
