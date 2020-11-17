#include "engine/game_engine.h"
#include "nlohmann/json.hpp"

namespace jjba_strategy {

GameEngine::GameEngine(size_t board_size) :
                       board_size_(board_size),
                       board_(),
                       character_index_(0) {
  //TODO implement JSON
  characters_.push_back(Character("Jotaro", glm::vec2(2, 1), "characters/jotaro.jpg", true));
  characters_.push_back(Character("Joseph", glm::vec2(2, 0), "characters/joseph.jpg", false));
  characters_.push_back(Character("Dio", glm::vec2(0, 3), "characters/dio.jpg", false));
  characters_.push_back(Character("Polnareff", glm::vec2(3, 0), "characters/polnareff.png", false));

  player_ = &characters_[0];
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