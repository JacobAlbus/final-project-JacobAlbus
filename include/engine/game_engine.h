#ifndef JJBA_STRATEGY_RPG_SRC_ENGINE_GAME_ENGINE_H_
#define JJBA_STRATEGY_RPG_SRC_ENGINE_GAME_ENGINE_H_

#include "engine/board.h"
#include "engine/character.h"
#include "cinder/app/App.h"
#include "cinder/audio/Voice.h"

namespace jjba_strategy {

enum MenuInputType {
  kAttack,
  kMovement,
  kSkip,
  kGameOver,
};

typedef std::vector<Character> characters_t;

class GameEngine {
 public:
  /**
   * Instantiates GameEngine
   * @param board size of initial board
   * @param path to json file containing board state
   */
  GameEngine(float window_size, const std::string& json_file_path, bool is_unit_test);

  /**
   * Handles User Inputs
   * @param event object containing input
   */
  void HandleInput(const ci::app::KeyEvent& event);

  /**
   * Renders the board and characters
   */
  void RenderBoardState() const;

  /**
   * Checks for win conditions and deaths and updates game accordingly
   */
  void UpdateGameState();

  /**
   * Updates which character is currently being controlled
   */
  void UpdatePlayableCharacter(); // Made public for testing

  /**
   * Returns true or false depending on if a character exists at tile
   * @param given position object
   * @return true or false
   */
  bool IsCharacterAtTile(const glm::vec2& tile_position) const; // Made public for testing

  /**
   * Checks to see if tile is on the screen
   * @param position of tile
   * @return true or false depending on if tile is off screen
   */
  bool IsTileOffScreen(const glm::vec2& position) const; // Made public for testing

  /**
   * Checks to see if currently selected movement tile is within range
   * @param vector of possible movement option
   * @return true or false depending on if the selected tile is within range
   */
  bool IsMovementInRange(const std::vector<glm::vec2>& movement_options,
                         const glm::vec2& selected_tile) const; // Made public for testing

  /**
   * Calculates tiles player is able to move to in turn
   * @return vector of positions player can move to
   */
  std::vector<glm::vec2> CalculatePlayerMovement() const; // Made public for testing

  inline const characters_t& GetAlliedCharacters() const { return allied_characters_; }
  inline const characters_t& GetEnemyCharacters() const { return enemy_characters_; }
  inline size_t GetBoardSize() const { return board_size_; }
  inline const Character* GetPlayer() const { return player_; }
  size_t GetInputType() const;
  inline const std::string& GetMessage() const { return message_; }
  inline size_t GetCharacterIndex() const { return character_index_; }
  inline bool InInputMenu() const { return in_input_menu_; }
  inline bool InAttackMenu() const { return in_attack_menu_; }
  inline bool InMainMenu() const { return in_main_menu_; }

private:
  /**
   * Moves player based on user input
   * @param event object containing input
   */
  void HandleMovementInput(const ci::app::KeyEvent& event);

  /**
   * Updates the state of board, including the characters
   */
  void UpdateBoardState(const std::string& json_file_path);

  /**
   * Finds the index of current player
   * @return index of current player
   */
  Character* FindCurrentPlayer();

  /**
   * Handles inputs to the character action menu
   * @param event object containing input
   */
  void HandleMenuInput(const ci::app::KeyEvent& event);

  /**
   * Handles input for when player is choosing an attack
   * @param event object containing input
   */
  void HandleAttackMenuInput(const ci::app::KeyEvent& event);

  /**
   * Handles input for when player attacks
   * @param event object containing input
   */
  void HandleAttackInput(const ci::app::KeyEvent& event);

  /**
   * Finds characters within attack range of player
   * @return vector characters in attack range of player
   */
  std::vector<size_t> FindCharactersIndexesInAttackRange();

  /**
   * Gets character who is currently targeted by player
   * @param whether or not the player is on the allied team
   * @param vector of indexes containing opposing characters in attack range
   * @return character is currently targeted by player
   */
  Character* GetTargetedCharacter(const std::vector<size_t>& targeted_character_indexes);

  /**
   * Updates message to player
   */
  void UpdateMessage();

  /**
   * Handles input for when the game is over;
   * @param event object containing input
   */
  void HandleGameOverInput(const ci::app::KeyEvent& event);

  /**
   * Plays the audio for the last used attack
   */
  void PlayAttackAudio();

  /**
   * Width and length of window
   */
  const float kWindowSize;
  /**
   * Path to boards folder
   */
  const std::string kBoardsFolderPath;
  /**
   * Index of player in list of characters from both team
   */
  size_t character_index_;

  /**
   * Message to users
   */
  std::string message_;
  /**
   * Current selection in menu selecting input type
   */
  MenuInputType current_menu_input_;

  /**
   * Whether or not the player is selecting a menu input (move, attack, etc.)
   */
  bool in_input_menu_;
  /**
   * Whether or not the player is in the main menu
   */
  bool in_main_menu_;
  /**
   * Whether or not the player is selecting an attack input
   */
  bool in_attack_menu_;

  /**
   * Width and length of board
   */
  size_t board_size_;
  /**
   * Board object containing board data
   */
  Board board_;

  /**
   * Whether or not the current player is allied
   */
  bool is_player_allied_;
  /**
   * Currently selected tile for movement
   */
  glm::vec2 player_movement_option_;
  /**
   * Index of targeted character in list of characters on opposing team
   */
  size_t targeted_character_index_;

  /**
   * List of characters on allied team
   */
  characters_t allied_characters_;
  /**
   * List of characters on enemy team
   */
  characters_t enemy_characters_;
  /**
   * Current player controlled by user
   */
  Character* player_;

  /**
   * Object able to play sounds
   */
  ci::audio::VoiceRef audio_player_;
};

} // namespace jjba_strategy

#endif //JJBA_STRATEGY_RPG_SRC_ENGINE_GAME_ENGINE_H_
