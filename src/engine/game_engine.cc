#include "engine/game_engine.h"
#include "nlohmann/json.hpp"

namespace jjba_strategy {

GameEngine::GameEngine(size_t board_size) :
                       board_size_(board_size),
                       board_(),
                       character_index_(0) {
  //TODO fix file pathing
  std::ifstream file("C:\\Users\\asus\\CLionProjects\\cinder_0.9.2_vc2015\\my-projects\\final-project-JacobAlbus\\assets\\boards\\board1.json");
  nlohmann::json board_state;
  file >> board_state;

  for(const auto& characters : board_state["characters"]) {
    for(const auto& character: characters){
      std::string name = character[0];
      size_t x_position = character[1][0];
      size_t y_position = character[1][1];
      glm::vec2 position(x_position, y_position);
      std::string image_path = character[2];
      bool is_player = character[3];
      characters_.push_back(Character(name, position, image_path, is_player));
    }
  }
  //TODO fix initial player instantiation
  player_ = &characters_[2];
}

bool GameEngine::IsCharacterAtTile(const glm::vec2& tile_position) const {
  for(const auto& character : characters_) {
    if(character.GetPosition() == tile_position) {
      return true;
    }
  }

  return false;
  //TODO get this to work
  //return std::any_of(characters_.begin(), characters_.end(), tile_position);
}

const Character* GameEngine::FindCharacterAtPosition(const glm::vec2& position) const {
  for(const auto& character : characters_) {
    if(character.GetPosition() == position) {
       return &character;
    }
  }

  return nullptr;
}

void GameEngine::HandleInput(const ci::app::KeyEvent& event) {
    switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_ESCAPE: {
      exit(0);
    }
    case ci::app::KeyEvent::KEY_UP: {
      glm::vec2 updated_position = player_->GetPosition();
      updated_position.x--;
      if(IsCharacterOnScreen(updated_position) && !IsCharacterAtTile(updated_position)) {
        player_->UpdatePosition(updated_position);
        UpdatePlayableCharacter();
      }
      break;
    }
    case ci::app::KeyEvent::KEY_DOWN: {
      glm::vec2 updated_position = player_->GetPosition();
      updated_position.x++;
      if(IsCharacterOnScreen(updated_position) && !IsCharacterAtTile(updated_position)) {
        player_->UpdatePosition(updated_position);
        UpdatePlayableCharacter();
      }
      break;
    }
    case ci::app::KeyEvent::KEY_LEFT: {
      glm::vec2 updated_position = player_->GetPosition();
      updated_position.y--;
      if(IsCharacterOnScreen(updated_position) && !IsCharacterAtTile(updated_position)) {
        player_->UpdatePosition(updated_position);
        UpdatePlayableCharacter();
      }
      break;
    }
    case ci::app::KeyEvent::KEY_RIGHT: {
      glm::vec2 updated_position = player_->GetPosition();
      updated_position.y++;
      if(IsCharacterOnScreen(updated_position) && !IsCharacterAtTile(updated_position)) {
        player_->UpdatePosition(updated_position);
        UpdatePlayableCharacter();
      }
      break;
    }
  }
}

bool GameEngine::IsCharacterOnScreen(const glm::vec2& position) const {
  return position.x >= 0 &&
         position.x <= static_cast<float>(board_size_ - 1) &&
         position.y >= 0 &&
         position.y <= static_cast<float>(board_size_ - 1);
}

void GameEngine::UpdatePlayableCharacter() {
  player_->UpdateIsPlayer();
  if(character_index_ < characters_.size() - 1) {
    character_index_++;
    player_ = &characters_[character_index_];
    player_->UpdateIsPlayer();
  } else {
    character_index_ = 0;
    player_ = &characters_[character_index_];
    player_->UpdateIsPlayer();
  }
}

} // namespace jjba_strategy