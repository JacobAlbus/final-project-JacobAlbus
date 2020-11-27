#ifndef JJBA_STRATEGY_RPG_SRC_ENGINE_GAME_ENGINE_H_
#define JJBA_STRATEGY_RPG_SRC_ENGINE_GAME_ENGINE_H_

#include "engine/board.h"
#include "engine/character.h"
#include "cinder/app/App.h"

namespace jjba_strategy {

enum InputType {
  kAttack,
  kMovementInput,
  kMenuInput,
};

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
   * Handles User Inputs
   * @param event object containing input
   */
  void HandleInput(const ci::app::KeyEvent& event);

  /**
   * Renders the board and characters
   */
  void RenderBoardState() const;

  inline const characters_t& GetAlliedCharacters() const { return allied_characters_; }
  inline const characters_t& GetEnemyCharacters() const { return enemy_characters_; }
  inline size_t GetBoardSize() const { return board_size_; }
  inline InputType GetInputType() const { return current_input_; }
  inline size_t GetCharacterIndex() const { return character_index_; }

 private:
  /**
   * Moves player based on user input
   * @param event object containing input
   */
  void HandleMovementInput(const ci::app::KeyEvent& event);

  /**
   * Returns true or false depending if a character exists at tile
   * @param given position object
   * @return true or false
   */
  bool IsCharacterAtTile(const glm::vec2& tile_position) const;

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

  /**
   * Finds the index of current player
   * @return index of current player
   */
  size_t FindCurrentPlayerIndex() const;

  /**
   * Calculates tiles player is able to move to in turn
   * @return vector of positions player can move to
   */
  std::vector<glm::vec2> CalculatePlayerMovement() const;

  /**
   * Handles inputs to the character action menu
   * @param event object containing input
   */
  void HandleMenuInput(const ci::app::KeyEvent& event);

  /**
   * Handles input for when player attacks
   * @param event object containing input
   */
  void HandleAttackInput(const ci::app::KeyEvent& event);

  /**
   * Finds characters within attack range of player
   * @return vector characters in attack range of player
   */
  std::vector<size_t> FindCharactersIndexesInAttackRange(bool is_player_allied);

  const float kWindowSize;
  size_t character_index_;
  size_t board_size_;
  size_t player_movement_option_index;
  InputType current_input_;
  bool in_menu_;
  Board board_;
  characters_t allied_characters_;
  characters_t enemy_characters_;
  Character* player_;
};

} // namespace jjba_strategy

#endif //JJBA_STRATEGY_RPG_SRC_ENGINE_GAME_ENGINE_H_
