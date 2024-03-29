#ifndef JJBA_STRATEGY_RPG_SRC_ENGINE_BOARD_H_
#define JJBA_STRATEGY_RPG_SRC_ENGINE_BOARD_H_

#include "engine/tile.h"
#include <vector>

namespace jjba_strategy {

typedef std::vector<std::vector<Tile>> board_t;

class Board {
 public:
  /**
   * Instantiates board object
   * @param path to json file containing board state
   */
  explicit Board(const std::string& json_file_path, bool is_unit_test);

  inline const board_t& GetBoard() const { return board_; }

  /**
   * Generates board from a json file
   * @param path to json
   */
  void GenerateBoard(const std::string& json_file_path);

  /**
   * Renders board object
   * @param size of window length/width
   * @param all positions player can move
   */
  void RenderBoard(float window_size,
                   bool is_player_moving,
                   const glm::vec2& selected_movement_option,
                   const std::vector<glm::vec2>& player_movement_options)
                   const;

  /**
   * Creates a json object containing board date
   * @return json object containing board data
   */
  static nlohmann::json ReadJSONFile(const std::string& json_file_path) ;

  /**
   * Checks to see if Board is square, throws error if not
   * @param json object containing board
   */
   static void CheckIfBoardSquare(const nlohmann::json& board_state) ;

  /**
   * Checks to see if Board is empty, throws error if not
   * @param json object containing board
   */
  static void CheckIfBoardEmpty(const nlohmann::json& board_state) ;

  /**
   * Checks to see if Board object exists in JSON, throws error if not
   * @param json object containing board
   */
  static void CheckIfBoardExists(const nlohmann::json& board_state) ;

 private:
  /**
   * Updates the color of a tile depending player movement
   * @param whether or not player is selecting a tile to move to
   * @param currently selected tile to move to
   * @param tile to be colored
   * @param tiles player can move to
   */
  void UpdateCharacterColor(bool is_player_moving,
                            const glm::vec2& selected_movement_option,
                            const glm::vec2& current_tile,
                            const std::vector<glm::vec2>& player_movement_options)
                            const;

  /**
   * width and length of board
   */
  size_t board_size_;

  /**
   * 2d vector of tiles representing every square on board
   */
  board_t board_;
};

} // namespace jjba_strategy

#endif //JJBA_STRATEGY_RPG_SRC_ENGINE_BOARD_H_
