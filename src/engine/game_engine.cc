#include "engine/game_engine.h"

namespace jjba_strategy {

GameEngine::GameEngine(float window_size, const std::string& json_file_path) :
                       kWindowSize(window_size),
                       board_(kWindowSize, json_file_path),
                       current_input_(InputType::kAttack),
                       in_menu_(true),
                       player_movement_option_index(0),
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
  for(const auto& character : enemy_characters_) {
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
  bool player_is_moving = current_input_ == InputType::kMovementInput;
  board_.RenderBoard(kWindowSize, player_is_moving,
                     player_movement_option_index, player_movement_options);
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
        break;
      case InputType::kAttack :
        HandleAttackInput(event);
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
  } else if(character_index_ < allied_characters_.size() + enemy_characters_.size() - 1) {
    character_index_++;
    player_ = &enemy_characters_[character_index_ - allied_characters_.size()];
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
  player_movement_options.push_back(player_->GetPosition() - glm::vec2(1, 0));
  player_movement_options.push_back(player_->GetPosition() - glm::vec2(1, -1));
  player_movement_options.push_back(player_->GetPosition() + glm::vec2(0, 1));
  player_movement_options.push_back(player_->GetPosition() + glm::vec2(1, 1));
  player_movement_options.push_back(player_->GetPosition() + glm::vec2(1, 0));
  player_movement_options.push_back(player_->GetPosition() + glm::vec2(1, -1));
  player_movement_options.push_back(player_->GetPosition() - glm::vec2(0, 1));

  return player_movement_options;
}

void GameEngine::HandleMovementInput(const ci::app::KeyEvent& event) {
  const auto& movement_options = CalculatePlayerMovement();

  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_ESCAPE:
      exit(0);
    case ci::app::KeyEvent::KEY_LEFT:
      if(player_movement_option_index == 0) {
        player_movement_option_index = movement_options.size() - 1;
      } else {
        player_movement_option_index--;
      }
      break;
    case ci::app::KeyEvent::KEY_RIGHT:
      if(player_movement_option_index == movement_options.size() - 1) {
        player_movement_option_index = 0;
      } else {
        player_movement_option_index++;
      }
      break;
    case ci::app::KeyEvent::KEY_SPACE:
      glm::vec2 new_position = movement_options[player_movement_option_index];
      if(!IsCharacterAtTile(new_position) && IsCharacterOnScreen(new_position)) {
        player_->UpdatePosition(new_position);
        UpdatePlayableCharacter();
        in_menu_ = true;
      }
      break;
  }
}

void GameEngine::HandleMenuInput(const ci::app::KeyEvent &event) {
  auto max_input = static_cast<size_t>(kMenuInput) - 1;
  auto current_input = static_cast<size_t>(current_input_);

  switch(event.getCode()) {
    case ci::app::KeyEvent::KEY_LEFT :
      if(current_input <= 0) {
        current_input_ = static_cast<InputType>(max_input);
      } else {
        current_input_ = static_cast<InputType>(current_input - 1);
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
    case ci::app::KeyEvent::KEY_ESCAPE :
      exit(0);
  }
}

std::vector<size_t> GameEngine::FindCharactersIndexesInAttackRange(bool is_player_allied) {
  std::vector<size_t> character_indexes;
  const auto& attack_range_tiles = CalculatePlayerMovement();

  if(is_player_allied) {
    for(const auto& position : attack_range_tiles) {
      for(size_t index = 0; index < enemy_characters_.size(); index++) {
        if(enemy_characters_[index].GetPosition() == position) {
          character_indexes.push_back(index);
        }
      }
    }
  } else {
    for(const auto& position : attack_range_tiles) {
      for(size_t index = 0; index < allied_characters_.size(); index++) {
        if(allied_characters_[index].GetPosition() == position) {
          character_indexes.push_back(index);
        }
      }
    }
  }

  return character_indexes;
}

void GameEngine::HandleAttackInput(const ci::app::KeyEvent& event) {
  bool is_player_allied = character_index_ < allied_characters_.size();
  auto characters_indexes = FindCharactersIndexesInAttackRange(is_player_allied);

  if(!characters_indexes.empty()) {
    if(is_player_allied) {
      Character* enemy = &enemy_characters_[characters_indexes[0]];
      enemy->UpdateHealth(enemy->GetHealth() - 10.0f);
      UpdatePlayableCharacter();
    } else {
      Character* enemy = &allied_characters_[characters_indexes[0]];
      enemy->UpdateHealth(enemy->GetHealth() - 10.0f);
      UpdatePlayableCharacter();
    }
  }

  in_menu_ = true;
}

} // namespace jjba_strategy