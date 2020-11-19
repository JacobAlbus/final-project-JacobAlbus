#ifndef JJBA_STRATEGY_RPG_SRC_ENGINE_GAME_ENGINE_H_
#define JJBA_STRATEGY_RPG_SRC_ENGINE_GAME_ENGINE_H_

#include "engine/board.h"
#include "engine/character.h"
#include "cinder/app/App.h"

namespace jjba_strategy {

typedef std::vector<Character> characters_t;

class GameEngine {
 public:
  /**
   * Instantiates GameEngine
   * @param board size of initial board
   * @param path to json file containing board state
   */
  GameEngine(float window_size, const std::string& json_file_path);

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
  const Character* FindCharacterAtPosition(const glm::vec2& position) const;

  /**
   * Handles User Inputs
   * @param event object containing input
   */
  void HandleInput(const ci::app::KeyEvent& event);

  void RenderBoardState() const;

  //TODO change naming possibly
  inline const board_t& GetBoard() const { return board_.GetBoard(); };

  inline const characters_t& GetCharacters() const { return characters_; };

 private:
  /**
   * Checks to see if character is on screen
   * @param position object of character
   * @return true or false depending on if character is on screen
   */
  bool IsCharacterOnScreen(const glm::vec2& position) const;

  /**
   * Updates which character is currently being controlled
   */
  void UpdatePlayableCharacter();

  /**
   * Updates the state of board, including the characters
   */
  void UpdateBoardState(const std::string& json_file_path);

  const float kWindowSize;
  size_t character_index_;
  size_t board_size_;
  Board board_;
  characters_t characters_;
  Character* player_;
};

} // namespace jjba_strategy

#endif //JJBA_STRATEGY_RPG_SRC_ENGINE_GAME_ENGINE_H_
