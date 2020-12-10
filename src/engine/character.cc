#include "engine/character.h"
#include "cinder/app/App.h"

namespace jjba_strategy {

Character::Character(const std::string& name,
                     const glm::vec2& position,
                     const std::string& image_path,
                     bool is_player,
                     size_t character_type_index,
                     bool is_unit_testing) :
                     current_attack_type_(static_cast<AttackType>(0)),
                     kName(name),
                     position_(position),
                     character_type(static_cast<CharacterType>(character_type_index)),
                     is_player_(is_player),
                     is_targeted_(false) {

  switch(character_type) {
    case CharacterType::kBrawler:
      health_ = 200.0f;
      movement_range_ = 1;
      attacks_.emplace_back(AttackType::kStarFinger);
      break;
    case kLongRange:
      health_ = 150.0f;
      movement_range_ = 2;
      attacks_.emplace_back(AttackType::kStarFinger);
      attacks_.emplace_back(AttackType::kEmeraldSplash);
      break;
    case kSupport:
      health_ = 100.0f;
      movement_range_ = 3;
      attacks_.emplace_back(AttackType::kStarFinger);
      attacks_.emplace_back(AttackType::kEmeraldSplash);
      attacks_.emplace_back(AttackType::kHermitPurple);
      break;
  }

  if(!is_unit_testing) {
    ci::fs::path path = ci::fs::path(image_path);
    image_ = ci::gl::Texture::create(ci::loadImage(cinder::app::loadAsset(path)));
  }
}

std::vector<Character> Character::GenerateCharacters(const std::string &json_file_path,
                                                     const std::string &characters_type) {

  nlohmann::json board_state = ReadJSONFile(json_file_path);
  CheckIfCharactersExists(board_state);
  CheckIfCharactersEmpty(board_state);
  std::vector<Character> characters;

  for(const auto& json_characters : board_state[characters_type]) {
    for(const auto& character: json_characters){
      std::string name = character[0];
      size_t x_position = character[1][0];
      size_t y_position = character[1][1];
      glm::vec2 position(x_position, y_position);
      std::string image_path = character[2];
      bool is_player = character[3];
      size_t character_type_index = character[4];
      characters.emplace_back(name, position, image_path,
                              is_player, character_type_index, false);
    }
  }

  return characters;
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
  ci::gl::draw(image_, pixel_bounding_box);
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

  ci::gl::draw(image_, pixel_bounding_box);

  const float kSpacing = -10.0f;
  auto health = static_cast<size_t>(health_);
  ci::gl::drawStringCentered(std::to_string(health),
                             pixel_bottom_right - glm::vec2(kTileSize / 2, kSpacing),
                             ci::Color("white"), ci::Font("Impact", 20));
  ci::gl::drawStringCentered(kName,
                             pixel_bottom_right - glm::vec2(kTileSize / 2, kSpacing * 3),
                             ci::Color("white"), ci::Font("Impact", 20));
}

std::vector<glm::vec2> Character::CalculateCharacterMovementOptions() const {
  std::vector<glm::vec2> movement_options;
  for(int row = -movement_range_; row < movement_range_ + 1; row++) {
    for(int col = -movement_range_; col < movement_range_ + 1; col++) {
      glm::vec2 option(position_.x + static_cast<float>(row), position_.y + static_cast<float>(col));
      movement_options.emplace_back(option);
    }
  }

  return movement_options;
}

void Character::AttackCharacter(Character* character) {
  Attack current_attack = attacks_[static_cast<size_t>(current_attack_type_)];
  character->health_ -= current_attack.base_power;
}

nlohmann::json Character::ReadJSONFile(const std::string& json_file_path) {
  std::ifstream file(json_file_path);
  nlohmann::json board_state;

  try {
    file >> board_state;
  }
  catch (nlohmann::detail::parse_error& ex) {
    std::cerr << "Passed JSON is Null" << ex.byte << std::endl;
    throw std::invalid_argument("");
  }

  return board_state;
}

void Character::CheckIfCharactersEmpty(const nlohmann::json& board_state) {
  if(board_state["allied characters"].empty()) {
    std::cerr << "The allied character lists in the passed JSON is empty" << std::endl;
    throw std::exception("");
  } else if(board_state["enemy characters"].empty()) {
    std::cerr << "The enemy character lists in the passed JSON is empty" << std::endl;
    throw std::exception("");
  }
}
void Character::CheckIfCharactersExists(const nlohmann::json &board_state) {
  bool allies_exist = false;
  bool enemies_exist = false;

  for (auto it = board_state.begin(); it != board_state.end(); it++){
    const auto& key = it.key();
    if(key == "allied characters") {
      allies_exist = true;
    } else if(key == "enemy characters") {
      enemies_exist = true;
    }
  }

  if(!allies_exist) {
    std::cerr << "The passed JSON file does not contain a list of allied characters"
    << std::endl;
    throw std::exception("");
  } else if (!enemies_exist) {
    std::cerr << "The passed JSON file does not contain a list of enemy characters"
              << std::endl;
    throw std::exception("");
  }
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
