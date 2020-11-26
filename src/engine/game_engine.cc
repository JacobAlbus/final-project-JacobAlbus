#include "engine/game_engine.h"

namespace jjba_strategy {

GameEngine::GameEngine(float window_size, const std::string& json_file_path) :
                       kWindowSize(window_size),
                       board_(kWindowSize, json_file_path),
                       current_input_(InputType::kAttack),
                       in_menu_(true),
                       character_index_(0) {
  allied_characters_ = Character::GenerateCharacters(json_file_path, "allied characters");
  enemy_characters_ = Character::GenerateCharacters(json_file_path, "enemy characters");
  player_ = &allied_characters_[FindCurrentPlayerIndex()];
  board_size_ = board_.GetBoard().size();
}

bool GameEngine::IsCharacterAtTile(const glm::vec2& tile_position) const {
  for(const auto& character : allied_characters_) {
    if(character.GetPosition() == tile_position) {
      return true;
    }
  }

  return false;
  //TODO get this to work
  //return std::any_of(characters_.begin(), characters_.end(), tile_position);
}

void GameEngine::RenderBoardState() const {
  std::vector<glm::vec2> player_movement_options = CalculatePlayerMovement();
  board_.RenderBoard(kWindowSize, player_movement_options);
  for(const auto& character : allied_characters_) {
    character.RenderCharacter(board_size_, kWindowSize);
  }
  for(const auto& character : enemy_characters_) {
    character.RenderCharacter(board_size_, kWindowSize);
  }
}

void GameEngine::HandleInput(const ci::app::KeyEvent& event) {
  if(in_menu_) {
    HandleMenuInput(event);
  } else {
    switch(current_input_) {
      case InputType::kMovementInput :
        HandleMovementInput(event);
        in_menu_ = true;
        break;
      case InputType::kAttack :
        player_->UpdateHealth(player_->GetHealth() - 10.0f);
        in_menu_ = true;
        break;
    }
  }
}

bool GameEngine::IsCharacterOnScreen(const glm::vec2& position) const {
  const size_t kWindowTopMargin = 2;
  const size_t kWindowSideMargin = 2;
  const size_t kWindowBottomMargin = 1;

  return position.x >= kWindowTopMargin &&
         position.x <= static_cast<float>(board_size_ - kWindowSideMargin) &&
         position.y >= kWindowBottomMargin &&
         position.y <= static_cast<float>(board_size_ - kWindowSideMargin);
}

void GameEngine::UpdatePlayableCharacter() {
  player_->UpdateIsPlayer();
  if(character_index_ < allied_characters_.size() - 1) {
    character_index_++;
    player_ = &allied_characters_[character_index_];
    player_->UpdateIsPlayer();
  } else {
    character_index_ = 0;
    player_ = &allied_characters_[character_index_];
    player_->UpdateIsPlayer();
  }
}

void GameEngine::UpdateBoardState(const std::string& json_file_path) {
  board_.GenerateBoard(json_file_path);
  allied_characters_ = Character::GenerateCharacters(json_file_path, "allied characters");
  enemy_characters_ = Character::GenerateCharacters(json_file_path, "enemy characters");
  player_ = &allied_characters_[FindCurrentPlayerIndex()];
  board_size_ = board_.GetBoard().size();
  character_index_ = 0;
}

//TODO make it return reference to character
size_t GameEngine::FindCurrentPlayerIndex() const {
  for(size_t index = 0; index < allied_characters_.size(); index++) {
    if(allied_characters_[index].IsPlayer()) {
      return index;
    }
  }
  throw std::invalid_argument("No player found");
}

//TODO actually calculate based on board state and character
std::vector<glm::vec2> GameEngine::CalculatePlayerMovement() const {
  std::vector<glm::vec2> player_movement_options;
  player_movement_options.push_back(player_->GetPosition() - glm::vec2(1, 1));
  player_movement_options.push_back(player_->GetPosition() - glm::vec2(0, 1));
  player_movement_options.push_back(player_->GetPosition() - glm::vec2(1, 0));
  player_movement_options.push_back(player_->GetPosition() + glm::vec2(1, 0));
  player_movement_options.push_back(player_->GetPosition() + glm::vec2(-1, 1));
  player_movement_options.push_back(player_->GetPosition() + glm::vec2(1, -1));
  player_movement_options.push_back(player_->GetPosition() + glm::vec2(0, 1));
  player_movement_options.push_back(player_->GetPosition() + glm::vec2(1, 1));

  return player_movement_options;
}

void GameEngine::HandleMovementInput(const ci::app::KeyEvent& event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_ESCAPE: {
      exit(0);
    }
    case ci::app::KeyEvent::KEY_UP: {
      glm::vec2 updated_position = player_->GetPosition();
      updated_position.x--;
      if(IsCharacterOnScreen(updated_position) && !IsCharacterAtTile(updated_position)) {
        player_->UpdateHealth(player_->GetHealth() - 10.0f);
        player_->UpdatePosition(updated_position);
        UpdatePlayableCharacter();
      }
      break;
    }
    case ci::app::KeyEvent::KEY_DOWN: {
      glm::vec2 updated_position = player_->GetPosition();
      updated_position.x++;
      if(IsCharacterOnScreen(updated_position) && !IsCharacterAtTile(updated_position)) {
        player_->UpdateHealth(player_->GetHealth() - 10.0f);
        player_->UpdatePosition(updated_position);
        UpdatePlayableCharacter();
      }
      break;
    }
    case ci::app::KeyEvent::KEY_LEFT: {
      glm::vec2 updated_position = player_->GetPosition();
      updated_position.y--;
      if(IsCharacterOnScreen(updated_position) && !IsCharacterAtTile(updated_position)) {
        player_->UpdateHealth(player_->GetHealth() - 10.0f);
        player_->UpdatePosition(updated_position);
        UpdatePlayableCharacter();
      }
      break;
    }
    case ci::app::KeyEvent::KEY_RIGHT: {
      glm::vec2 updated_position = player_->GetPosition();
      updated_position.y++;
      if(IsCharacterOnScreen(updated_position) && !IsCharacterAtTile(updated_position)) {
        player_->UpdateHealth(player_->GetHealth() - 10.0f);
        player_->UpdatePosition(updated_position);
        UpdatePlayableCharacter();
      }
      break;
    }
    case ci::app::KeyEvent::KEY_SPACE: {
      UpdateBoardState("assets\\boards\\board2.json");
      break;
    }
  }
}

void GameEngine::HandleMenuInput(const ci::app::KeyEvent &event) {
  auto max_input = static_cast<size_t>(kMenuInput) - 1;
  auto current_input = static_cast<size_t>(current_input_);

  switch(event.getCode()) {
    case ci::app::KeyEvent::KEY_LEFT :
      current_input--;
      if(current_input < 0) {
        current_input_ = static_cast<InputType>(max_input);
      } else {
        current_input_ = static_cast<InputType>(current_input);
      }
      break;
    case ci::app::KeyEvent::KEY_RIGHT :
      current_input++;
      if(current_input > max_input) {
        current_input_ = static_cast<InputType>(0);
      } else {
        current_input_ = static_cast<InputType>(current_input);
      }
      break;
    case ci::app::KeyEvent::KEY_SPACE :
      in_menu_ = false;
      break;
  }
}

} // namespace jjba_strategy