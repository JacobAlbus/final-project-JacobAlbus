#include "engine/game_engine.h"

namespace jjba_strategy {

GameEngine::GameEngine(float window_size, const std::string& json_file_path) :
                       kWindowSize(window_size),
                       board_(kWindowSize, json_file_path),
                       character_index_(0) {

  characters_ = Character::GenerateCharacters(json_file_path);
  player_ = &characters_[FindCurrentPlayerIndex()];
  board_size_ = board_.GetBoard().size();
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

void GameEngine::RenderBoardState() const {
  board_.RenderBoard(kWindowSize);
  for(const auto& character : characters_) {
    character.RenderCharacter(board_size_, kWindowSize);
  }
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
    case ci::app::KeyEvent::KEY_SPACE: {
      UpdateBoardState("C:\\Users\\asus\\CLionProjects\\cinder_0.9.2_vc2015\\my-projects\\final-project-JacobAlbus\\assets\\boards\\board2.json");
      break;
    }
  }
}

bool GameEngine::IsCharacterOnScreen(const glm::vec2& position) const {
  const size_t kWindowTopMargin = 2;
  const size_t kWindowMargin = 1;

  return position.x >= kWindowTopMargin &&
         position.x <= static_cast<float>(board_size_ - 1 - kWindowMargin) &&
         position.y >= kWindowMargin &&
         position.y <= static_cast<float>(board_size_ - 1- kWindowMargin);
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

void GameEngine::UpdateBoardState(const std::string& json_file_path) {
  board_.GenerateBoard(json_file_path);
  characters_ = Character::GenerateCharacters(json_file_path);
  player_ = &characters_[FindCurrentPlayerIndex()];
  board_size_ = board_.GetBoard().size();
  character_index_ = 0;
}

//TODO make it return reference to character
size_t GameEngine::FindCurrentPlayerIndex() const {
  for(size_t index = 0; index < characters_.size(); index++) {
    if(characters_[index].IsPlayer()) {
      return index;
    }
  }
  //TODO is this bad implementation
  throw std::invalid_argument("No player found");
}

} // namespace jjba_strategy