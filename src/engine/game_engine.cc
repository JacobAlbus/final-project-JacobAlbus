#include "engine/game_engine.h"

namespace jjba_strategy {

GameEngine::GameEngine(size_t board_size) :
                       kBoardSize(board_size),
                       board_(board_size),
                       character_index_(0) {
  //TODO implement JSON
  characters_.push_back(Character("Jotaro", true, glm::vec2(2, 1), "characters/jotaro.jpg"));
  characters_.push_back(Character("Dio", false, glm::vec2(0, 3), "characters/dio.jpg"));
  characters_.push_back(Character("Polnareff", false, glm::vec2(3, 0), "characters/polnareff.png"));
  characters_.push_back(Character("Joseph", false, glm::vec2(2, 0), "characters/joseph.jpg"));

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
         position.x <= static_cast<float>(kBoardSize - 1) &&
         position.y >= 0 &&
         position.y <= static_cast<float>(kBoardSize - 1);
}

void GameEngine::UpdatePlayableCharacter() {
  if(character_index_ < characters_.size() - 1) {
    character_index_++;
    player_ = &characters_[character_index_];
  } else {
    character_index_ = 0;
    player_ = &characters_[character_index_];
  }
}

} // namespace jjba_strategy