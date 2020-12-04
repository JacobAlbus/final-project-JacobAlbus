#include "engine/character.h"
#include "cinder/app/App.h"

namespace jjba_strategy {

Character::Character(const std::string& name,
                     const glm::vec2& position,
                     const std::string& image_path,
                     bool is_player,
                     bool is_targeted,
                     size_t character_type_index) :
                     current_attack_type_(static_cast<AttackType>(0)),
                     kName(name),
                     position_(position),
                     character_type(static_cast<CharacterType>(character_type_index)),
                     is_player_(is_player),
                     is_targeted_(is_targeted) {

  switch(character_type) {
    case CharacterType::kBrawler :
      health_ = 200.0f;
      attacks_.emplace_back(AttackType::kStarFinger);
      break;
    case kLongRange:
      health_ = 150.0f;
      attacks_.emplace_back(AttackType::kStarFinger);
      attacks_.emplace_back(AttackType::kEmeraldSplash);
      break;
    case kSupport:
      health_ = 100.0f;
      attacks_.emplace_back(AttackType::kStarFinger);
      attacks_.emplace_back(AttackType::kEmeraldSplash);
      attacks_.emplace_back(AttackType::kHermitPurple);
      break;
  }

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
  } else if(is_targeted_){
    ci::gl::color(ci::Color("red"));
  } else {
    ci::gl::color(ci::Color("gray"));
  }

  ci::Rectf pixel_bounding_box = CalculatePixelBoundingBox(board_size,
                                                           window_size);
  ci::gl::draw(kImage, pixel_bounding_box);
}

void Character::RenderCharacterFacePlate(bool is_enemy, size_t board_size,
                                         size_t index, float window_size) const {

  const auto kTileSize = static_cast<float>(window_size / board_size);
  const auto kSideMargin = static_cast<float>(board_size * index);
  const auto kTopMargin = static_cast<float>(board_size);

  glm::vec2 pixel_top_left;
  if(is_enemy) {
    pixel_top_left = glm::vec2(window_size - ((index + 1) * kTileSize) - kSideMargin - kTopMargin, kTopMargin);
  } else {
    pixel_top_left = glm::vec2(index * kTileSize + kSideMargin + kTopMargin, kTopMargin);
  }

  glm::vec2 pixel_bottom_right = pixel_top_left + glm::vec2(kTileSize, kTileSize);
  ci::Rectf pixel_bounding_box(pixel_top_left, pixel_bottom_right);

  ci::gl::draw(kImage, pixel_bounding_box);

  //TODO implement health bar
  const float kSpacing = -15.0f;
  auto health = static_cast<size_t>(health_);
  ci::gl::drawStringCentered(std::to_string(health), pixel_bottom_right - glm::vec2(kTileSize / 2, kSpacing),
                             ci::Color("white"));
  ci::gl::drawStringCentered(kName, pixel_bottom_right - glm::vec2(kTileSize / 2, kSpacing * 2),
                             ci::Color("white"));
}

void Character::UpdateHealth(float new_health) {
  health_ = new_health;
}

void Character::AttackCharacter(Character* character) {
  Attack current_attack = attacks_[static_cast<size_t>(current_attack_type_)];
  character->health_ -= current_attack.base_power;
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

  return {pixel_top_left, pixel_bottom_right};
}

} // namespace jjba_strategy
