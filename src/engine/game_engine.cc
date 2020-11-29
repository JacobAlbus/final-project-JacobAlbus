#include "engine/game_engine.h"

namespace jjba_strategy {

GameEngine::GameEngine(float window_size, const std::string& json_file_path) :
                       kWindowSize(window_size),
                       board_(kWindowSize, json_file_path),
                       current_input_(InputType::kAttack),
                       in_menu_(true),
                       player_movement_option_index(0),
                       character_index_(0),
                       targeted_character_index_(0),
                       message_("Pick an input (use enter bar to confirm)") {
  allied_characters_ = Character::GenerateCharacters(json_file_path, "allied characters");
  enemy_characters_ = Character::GenerateCharacters(json_file_path, "enemy characters");
  player_ = &allied_characters_[FindCurrentPlayerIndex()];
  board_size_ = board_.GetBoard().size();
}

void GameEngine::UpdateGameState() {
  for(size_t index = 0; index < allied_characters_.size(); index++) {
    if(allied_characters_[index].GetHealth() <= 0.0f) {
      allied_characters_.erase(allied_characters_.begin() + index);
    }
  }

  for(size_t index = 0; index < enemy_characters_.size(); index++) {
    if(enemy_characters_[index].GetHealth() <= 0.0f) {
      enemy_characters_.erase(enemy_characters_.begin() + index);
    }
  }

  if(allied_characters_.empty()) {
    message_ = "Enemies Win!!!";
    current_input_ = InputType::kGameOver;
  }
  if(enemy_characters_.empty()) {
    message_ = "Allies Win!!!";
    current_input_ = InputType::kGameOver;
  }

  if(in_menu_ && !allied_characters_.empty() && !enemy_characters_.empty()) {
    message_ = "Pick an input (use enter bar to confirm)";
  } else {
    switch(current_input_) {
      case InputType::kMovementInput :
        message_ = "Pick a tile to move to (use backspace to go back)";
        break;
      case InputType::kAttack :
        message_ = "Pick a character to attack (use backspace to go back)";
        break;
    }
  }
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
  bool player_is_moving = current_input_ == InputType::kMovementInput && !in_menu_;
  board_.RenderBoard(kWindowSize, player_is_moving,
                     player_movement_option_index, CalculatePlayerMovement());

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
    case ci::app::KeyEvent::KEY_ESCAPE :
      exit(0);
    case ci::app::KeyEvent::KEY_BACKSPACE :
      in_menu_ = true;
      break;
    case ci::app::KeyEvent::KEY_a :
      if(player_movement_option_index == 0) {
        player_movement_option_index = movement_options.size() - 1;
      } else {
        player_movement_option_index--;
      }
      break;
    case ci::app::KeyEvent::KEY_d :
      if(player_movement_option_index == movement_options.size() - 1) {
        player_movement_option_index = 0;
      } else {
        player_movement_option_index++;
      }
      break;
    case ci::app::KeyEvent::KEY_RETURN :
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
  auto max_input = static_cast<size_t>(kGameOver) - 1;
  auto current_input = static_cast<size_t>(current_input_);

  switch(event.getCode()) {
    case ci::app::KeyEvent::KEY_a :
      if(current_input <= 0) {
        current_input_ = static_cast<InputType>(max_input);
      } else {
        current_input_ = static_cast<InputType>(current_input - 1);
      }
      break;
    case ci::app::KeyEvent::KEY_d :
      current_input++;
      if(current_input > max_input) {
        current_input_ = static_cast<InputType>(0);
      } else {
        current_input_ = static_cast<InputType>(current_input);
      }
      break;
    case ci::app::KeyEvent::KEY_RETURN : {
      in_menu_ = false;

      //TODO fix shoddy implementation
      bool is_player_allied = character_index_ < allied_characters_.size();
      auto targeted_characters = FindCharactersIndexesInAttackRange(is_player_allied);
      if(!targeted_characters.empty() && current_input_ == InputType::kAttack) {
        GetTargetedCharacter(is_player_allied, targeted_characters)->UpdateIsTarget();
      }

      //TODO pass in event object with left or right arrow input
      //HandleMenuInput(event);
      break;
    }
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
  auto targeted_characters = FindCharactersIndexesInAttackRange(is_player_allied);

  if(!targeted_characters.empty()) {
    switch (event.getCode()) {
      //TODO remove brackets
      case ci::app::KeyEvent::KEY_BACKSPACE: {
        Character *target_character = GetTargetedCharacter(is_player_allied, targeted_characters);
        target_character->UpdateIsTarget();
        in_menu_ = true;
        break;
      } case ci::app::KeyEvent::KEY_d:
        GetTargetedCharacter(is_player_allied, targeted_characters)->UpdateIsTarget();
        targeted_character_index_++;
        if(targeted_character_index_ >= targeted_characters.size()) {
          targeted_character_index_ = 0;
        }
        GetTargetedCharacter(is_player_allied, targeted_characters)->UpdateIsTarget();
        break;
      case ci::app::KeyEvent::KEY_a:
        GetTargetedCharacter(is_player_allied, targeted_characters)->UpdateIsTarget();
        if(targeted_character_index_ <= 0) {
          targeted_character_index_ = targeted_characters.size() - 1;
        } else {
          targeted_character_index_--;
        }
        GetTargetedCharacter(is_player_allied, targeted_characters)->UpdateIsTarget();
        break;
      case ci::app::KeyEvent::KEY_RETURN:
        Character* target_character = GetTargetedCharacter(is_player_allied, targeted_characters);
        target_character->UpdateHealth(target_character->GetHealth() - 10.0f);
        target_character->UpdateIsTarget();
        targeted_character_index_ = 0;
        in_menu_ = true;
        UpdatePlayableCharacter();
        break;
    }
  } else {
    in_menu_ = true;
  }
}

Character* GameEngine::GetTargetedCharacter(bool is_player_allied,
                                         const std::vector<size_t>& targeted_characters) {
  if(is_player_allied) {
    return &enemy_characters_[targeted_characters[targeted_character_index_]];
  } else {
    return &allied_characters_[targeted_characters[targeted_character_index_]];
  }
}

} // namespace jjba_strategy