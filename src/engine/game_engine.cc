#include "engine/game_engine.h"

namespace jjba_strategy {

GameEngine::GameEngine(float window_size, const std::string& boards_folder_path) :
                       kWindowSize(window_size),
                       kBoardsFolderPath(boards_folder_path),
                       board_(boards_folder_path + "board1.json"),
                       current_menu_input_(MenuInputType::kAttack),
                       current_attack_input_(AttackType::kStarFinger),
                       in_input_menu_(true),
                       in_attack_menu_(false),
                       in_main_menu_(true),
                       player_movement_option_index(0),
                       player_movement_option(glm::vec2(0, 0)),
                       is_player_allied_(true),
                       character_index_(0),
                       targeted_character_index_(0),
                       message_("Pick an input (use enter bar to confirm)") {

  allied_characters_ = Character::GenerateCharacters(boards_folder_path + "board1.json", "allied characters");
  enemy_characters_ = Character::GenerateCharacters(boards_folder_path + "board1.json", "enemy characters");
  player_ = FindCurrentPlayer();
  board_size_ = board_.GetBoard().size();
}

void GameEngine::UpdateGameState() {
  is_player_allied_ = character_index_ < allied_characters_.size();

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

  if(allied_characters_.empty() || enemy_characters_.empty()) {
    current_menu_input_ = MenuInputType::kGameOver;
  }

  UpdateMessage();
}

void GameEngine::RenderBoardState() const {
  bool player_is_moving = (current_menu_input_ == MenuInputType::kMovement) && !in_input_menu_;
  board_.RenderBoard(kWindowSize, player_is_moving,
                     player_movement_option, CalculatePlayerMovement());

  for(const auto& character : allied_characters_) {
    character.RenderCharacter(board_size_, kWindowSize);
  }
  for(const auto& character : enemy_characters_) {
    character.RenderCharacter(board_size_, kWindowSize);
  }
}

void GameEngine::HandleInput(const ci::app::KeyEvent& event) {
  if(in_main_menu_ && event.getCode() == ci::app::KeyEvent::KEY_ESCAPE) {
    exit(0);
  } else if(in_input_menu_) {
    in_main_menu_ = false;
    HandleMenuInput(event);
  } else {
    in_main_menu_ = false;
    switch(current_menu_input_) {
      case MenuInputType::kMovement:
        HandleMovementInput(event);
        break;
      case MenuInputType::kAttack:
        if(in_attack_menu_) {
          HandleAttackMenuInput(event);
        } else {
          HandleAttackInput(event);
        }
        break;
      case kGameOver:
        HandleGameOverInput(event);
        break;
    }
  }
}

void GameEngine::UpdateMessage() {
  if(in_input_menu_) {
    message_ = "Pick an input (use enter to confirm)";
  } else {
    switch(current_menu_input_) {
      case MenuInputType::kMovement:
        message_ = "Pick a tile to move to (use backspace to go back)";
        break;
      case MenuInputType::kAttack: {
        if(in_attack_menu_) {
          message_ = "Pick an attack (use enter to confirm)";
        } else {
          auto targeted_characters = FindCharactersIndexesInAttackRange();
          if (!targeted_characters.empty()) {
            message_ = "Pick a character to attack (use backspace to go back)";
          } else {
            message_ = "No enemies in attack range, pick another input";
          }
        }
        break;
      }
      case kGameOver:
        if(allied_characters_.empty()) {
          message_ = "Enemies Win!";
        }
        if(enemy_characters_.empty()) {
          message_ = "Allies Win!";
        }
        break;
    }
  }
}

void GameEngine::UpdatePlayableCharacter() {
  player_->ToggleIsPlayer();
  if(character_index_ < allied_characters_.size() - 1) {
    character_index_++;
    player_ = &allied_characters_[character_index_];
    player_->ToggleIsPlayer();
  } else if(character_index_ < allied_characters_.size() + enemy_characters_.size() - 1) {
    character_index_++;
    player_ = &enemy_characters_[character_index_ - allied_characters_.size()];
    player_->ToggleIsPlayer();
  } else {
    character_index_ = 0;
    player_ = &allied_characters_[character_index_];
    player_->ToggleIsPlayer();
  }
}

void GameEngine::UpdateBoardState(const std::string& json_file_path) {
  board_.GenerateBoard(json_file_path);
  board_size_ = board_.GetBoard().size();

  allied_characters_ = Character::GenerateCharacters(json_file_path, "allied characters");
  enemy_characters_ = Character::GenerateCharacters(json_file_path, "enemy characters");
  player_ = FindCurrentPlayer();

  current_menu_input_ = MenuInputType::kAttack;
  in_input_menu_ = true;

  character_index_ = 0;
  player_movement_option_index = 0;
  targeted_character_index_ = 0;
}

Character* GameEngine::FindCurrentPlayer() {
  for(auto& character : allied_characters_) {
    if(character.IsPlayer()) {
      return &character;
    }
  }

  throw std::invalid_argument("No player found");
}

void GameEngine::HandleMenuInput(const ci::app::KeyEvent &event) {
  auto max_input = static_cast<size_t>(kGameOver) - 1;
  auto current_input = static_cast<size_t>(current_menu_input_);

  switch(event.getCode()) {
    case ci::app::KeyEvent::KEY_a:
      if(current_input <= 0) {
        current_menu_input_ = static_cast<MenuInputType>(max_input);
      } else {
        current_menu_input_ = static_cast<MenuInputType>(current_input - 1);
      }
      break;
    case ci::app::KeyEvent::KEY_d:
      current_input++;
      if(current_input > max_input) {
        current_menu_input_ = static_cast<MenuInputType>(0);
      } else {
        current_menu_input_ = static_cast<MenuInputType>(current_input);
      }
      break;
    case ci::app::KeyEvent::KEY_RETURN:
      in_input_menu_ = false;
      if(current_input == MenuInputType::kAttack) {
        in_attack_menu_ = true;
      } else if(current_input == MenuInputType::kMovement) {
        player_movement_option = CalculatePlayerMovement()[0];
      }
      break;
    case ci::app::KeyEvent::KEY_ESCAPE:
      in_main_menu_ = true;
  }
}

void GameEngine::HandleMovementInput(const ci::app::KeyEvent& event) {
  const auto& movement_options = CalculatePlayerMovement();

  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_ESCAPE:
      in_main_menu_ = true;
    case ci::app::KeyEvent::KEY_BACKSPACE:
      in_input_menu_ = true;
      break;
    case ci::app::KeyEvent::KEY_a: {
      glm::vec2 temp_tile(player_movement_option.x, player_movement_option.y - 1);
      if (IsMovementInRange(movement_options, temp_tile)) {
        player_movement_option = temp_tile;
      }
      break;
    }
    case ci::app::KeyEvent::KEY_d: {
      glm::vec2 temp_tile(player_movement_option.x, player_movement_option.y + 1);
      if (IsMovementInRange(movement_options, temp_tile)) {
        player_movement_option = temp_tile;
      }
      break;
    }
    case ci::app::KeyEvent::KEY_w:  {
      glm::vec2 temp_tile(player_movement_option.x - 1, player_movement_option.y);
      if (IsMovementInRange(movement_options, temp_tile)) {
        player_movement_option = temp_tile;
      }
      break;
    }
    case ci::app::KeyEvent::KEY_s: {
      glm::vec2 temp_tile(player_movement_option.x + 1, player_movement_option.y);
      if (IsMovementInRange(movement_options, temp_tile)) {
        player_movement_option = temp_tile;
      }
      break;
    }
    case ci::app::KeyEvent::KEY_RETURN:
      if(player_movement_option != player_->GetPosition()) {
        player_->SetPosition(player_movement_option);
        UpdatePlayableCharacter();
        in_input_menu_ = true;
      }
      break;
  }
}

std::vector<glm::vec2> GameEngine::CalculatePlayerMovement() const {
  std::vector<glm::vec2> movement_options = player_->CalculateCharacterMovementOptions();
  std::vector<size_t> valid_tiles_indexes;

  if(current_menu_input_ != MenuInputType::kAttack) {
    for(size_t index = 0; index < movement_options.size(); index++) {
      glm::vec2 movement_tile = movement_options[index];
      if(!IsCharacterAtTile(movement_tile) && !IsTileOffScreen(movement_tile)) {
        valid_tiles_indexes.emplace_back(index);
      }
    }
  } else {
    return movement_options;
  }

  std::vector<glm::vec2> valid_movement_options;
  valid_movement_options.reserve(valid_tiles_indexes.size());
  for(auto index : valid_tiles_indexes) {
    valid_movement_options.emplace_back(movement_options[index]);
  }

  return valid_movement_options;
}

bool GameEngine::IsCharacterAtTile(const glm::vec2& tile_position) const {
  for(const auto& character : allied_characters_) {
    if(tile_position == player_->GetPosition()) {
      break;
    } else if(character.GetPosition() == tile_position) {
      return true;
    }
  }

  for(const auto& character : enemy_characters_) {
    if(tile_position == player_->GetPosition()) {
      break;
    } else if(character.GetPosition() == tile_position) {
      return true;
    }
  }

  return false;
}

bool GameEngine::IsTileOffScreen(const glm::vec2& position) const {
  return position.x < 2 ||
         position.x > static_cast<float>(board_size_ - 2) ||
         position.y < 1 ||
         position.y > static_cast<float>(board_size_ - 2);
}

void GameEngine::HandleAttackMenuInput(const ci::app::KeyEvent &event) {
  auto max_input = player_->GetAttacks().size() - 1;
  auto current_input = static_cast<size_t>(player_->GetCurrentAttackType());

  switch(event.getCode()) {
    case ci::app::KeyEvent::KEY_a:
      if(current_input <= 0) {
        player_->UpdateCurrentAttackType(static_cast<AttackType>(max_input));
      } else {
        player_->UpdateCurrentAttackType(static_cast<AttackType>(current_input - 1));
      }
      break;
    case ci::app::KeyEvent::KEY_d:
      current_input++;
      if(current_input > max_input) {
        player_->UpdateCurrentAttackType(static_cast<AttackType>(0));
      } else {
        player_->UpdateCurrentAttackType(static_cast<AttackType>(current_input));
      }
      break;
    case ci::app::KeyEvent::KEY_RETURN: {
      in_attack_menu_ = false;
      //does the initial render of targeted character
      auto targeted_characters = FindCharactersIndexesInAttackRange();
      if (!targeted_characters.empty()) {
        GetTargetedCharacter(targeted_characters)->ToggleIsTarget();
      }
      break;
    }
    case ci::app::KeyEvent::KEY_BACKSPACE:
      in_attack_menu_ = false;
      in_input_menu_ = true;
      break;
    case ci::app::KeyEvent::KEY_ESCAPE:
      in_main_menu_ = true;
  }
}

void GameEngine::HandleAttackInput(const ci::app::KeyEvent& event) {
  auto targeted_characters = FindCharactersIndexesInAttackRange();

  if(!targeted_characters.empty()) {
    switch (event.getCode()) {
      case ci::app::KeyEvent::KEY_BACKSPACE: {
        GetTargetedCharacter(targeted_characters)->ToggleIsTarget();
        in_attack_menu_ = true;
        break;
      } case ci::app::KeyEvent::KEY_d:
        GetTargetedCharacter(targeted_characters)->ToggleIsTarget();
        targeted_character_index_++;
        if(targeted_character_index_ >= targeted_characters.size()) {
          targeted_character_index_ = 0;
        }
        GetTargetedCharacter(targeted_characters)->ToggleIsTarget();
        break;
      case ci::app::KeyEvent::KEY_a:
        GetTargetedCharacter(targeted_characters)->ToggleIsTarget();
        if(targeted_character_index_ <= 0) {
          targeted_character_index_ = targeted_characters.size() - 1;
        } else {
          targeted_character_index_--;
        }
        GetTargetedCharacter(targeted_characters)->ToggleIsTarget();
        break;
      case ci::app::KeyEvent::KEY_RETURN:
        Character* target_character = GetTargetedCharacter(targeted_characters);
        player_->AttackCharacter(target_character);
        PlayAttackAudio();
        target_character->ToggleIsTarget();
        targeted_character_index_ = 0;
        in_input_menu_ = true;
        UpdatePlayableCharacter();
        break;
    }
  } else {
    in_input_menu_ = true;
  }
}

std::vector<size_t> GameEngine::FindCharactersIndexesInAttackRange() {
  std::vector<size_t> character_indexes;
  const auto& attack_range_tiles = CalculatePlayerMovement();

  if(is_player_allied_) {
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

Character* GameEngine::GetTargetedCharacter(const std::vector<size_t>& targeted_characters) {
  if(is_player_allied_) {
    return &enemy_characters_[targeted_characters[targeted_character_index_]];
  } else {
    return &allied_characters_[targeted_characters[targeted_character_index_]];
  }
}

void GameEngine::HandleGameOverInput(const ci::app::KeyEvent& event) {
  switch(event.getCode()) {
    case ci::app::KeyEvent::KEY_1:
      UpdateBoardState(kBoardsFolderPath + "board1.json");
      break;
    case ci::app::KeyEvent::KEY_2:
      UpdateBoardState(kBoardsFolderPath + "board2.json");
      break;
    case ci::app::KeyEvent::KEY_ESCAPE:
      in_main_menu_ = true;
  }
}

size_t GameEngine::GetInputType() const  {
  if(in_input_menu_) {
    return static_cast<size_t>(current_menu_input_);
  } else if(in_attack_menu_) {
    return static_cast<size_t>(player_->GetCurrentAttackType());
  } else {
    return 0;
  }
}

bool GameEngine::IsMovementInRange(const std::vector<glm::vec2>& movement_options, const glm::vec2& selected_tile) const {
  for(const auto& position : movement_options) {
    if(position == selected_tile) {
      return true;
    }
  }

  return false;
  //  //TODO get this to work
//  return std::any_of(allied_characters_.begin()->GetPosition(),
//                     allied_characters_.end()->GetPosition(),
//                     [] (const auto& other_pos) { return tile_position == other_pos; });
}

void GameEngine::PlayAttackAudio() {
  if(player_->GetCurrentAttackType() == AttackType::kStarFinger) {
    ci::audio::SourceFileRef source = ci::audio::load(ci::app::loadAsset("audio/star_finger.mp3"));
    audio_player_ = ci::audio::Voice::create(source);
    audio_player_->start();
  } else if(player_->GetCurrentAttackType() == AttackType::kEmeraldSplash) {
    ci::audio::SourceFileRef source = ci::audio::load(ci::app::loadAsset("audio/emerald_splash.mp3"));
    audio_player_ = ci::audio::Voice::create(source);
    audio_player_->start();
  } else if(player_->GetCurrentAttackType() == AttackType::kHermitPurple) {
    ci::audio::SourceFileRef source = ci::audio::load(ci::app::loadAsset("audio/hermit_purple.mp3"));
    audio_player_ = ci::audio::Voice::create(source);
    audio_player_->start();
  }
}

} // namespace jjba_strategy