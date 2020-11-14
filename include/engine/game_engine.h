#ifndef JJBA_STRATEGY_RPG_SRC_ENGINE_GAME_ENGINE_H_
#define JJBA_STRATEGY_RPG_SRC_ENGINE_GAME_ENGINE_H_

#include "engine/board.h"
#include "engine/character.h"
#include "cinder/app/App.h"

namespace jjba_strategy {

typedef std::vector<Character> characters_t;

class GameEngine {
 public:
  GameEngine(size_t board_size);

  /**
   * Returns true or false depending if a character exists at tile
   * @param given position object
   * @return true or false
   */
  bool IsCharacterAtTile(const glm::vec2& tile_position) const;

  /**
   * Finds character at given position returns SOMETHING if not found
   * @param given position object
   * @return character at position if found, SOMETHING otherwise
   */
  const Character& FindCharacterAtPosition(const glm::vec2& position) const;

  /**
   * Handles User Inputs
   * @param event object containing input
   */
  void HandleInput(const ci::app::KeyEvent& event);

  inline const board_t& GetBoard() const { return board_; };

  inline const characters_t& GetCharacters() const { return characters_; };

 private:
  size_t kBoardSize;
  board_t board_;
  characters_t characters_;
};

} // namespace jjba_strategy

#endif //JJBA_STRATEGY_RPG_SRC_ENGINE_GAME_ENGINE_H_
