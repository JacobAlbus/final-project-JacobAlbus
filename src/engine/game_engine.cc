#include "engine/game_engine.h"

namespace jjba_strategy {

GameEngine::GameEngine(size_t board_size) :
                       kBoardSize(board_size),
                       board_(board_size) {

  characters_.push_back(Character("Jotaro", true, glm::vec2(2, 1)));
  characters_.push_back(Character("Dio", false, glm::vec2(0, 3)));
  characters_.push_back(Character("Polnareff", false, glm::vec2(3, 0)));
  characters_.push_back(Character("Joseph", false, glm::vec2(2, 0)));
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

const Character& GameEngine::FindCharacterAtPosition(const glm::vec2 &position) const {
  for(const auto& character : characters_) {
    if(character.GetPosition() == position) {
      return character;
    }
  }

  //TODO handle case where no player is found
  return characters_[0];
}

//TODO implement controls class
void GameEngine::HandleInput(const ci::app::KeyEvent& event) {
    switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_ESCAPE: {
      exit(0);
      break;
    }
    case ci::app::KeyEvent::KEY_UP: {
      glm::vec2 updated_position = characters_[0].GetPosition();
      updated_position.x--;
      characters_[0].UpdatePosition(updated_position);
      break;
    }
    case ci::app::KeyEvent::KEY_DOWN: {
      glm::vec2 updated_position = characters_[0].GetPosition();
      updated_position.x++;
      characters_[0].UpdatePosition(updated_position);
      break;
    }
    case ci::app::KeyEvent::KEY_LEFT: {
      glm::vec2 updated_position = characters_[0].GetPosition();
      updated_position.y--;
      characters_[0].UpdatePosition(updated_position);
      break;
    }
    case ci::app::KeyEvent::KEY_RIGHT: {
      glm::vec2 updated_position = characters_[0].GetPosition();
      updated_position.y++;
      characters_[0].UpdatePosition(updated_position);
      break;
    }
  }
}

} // namespace jjba_strategy