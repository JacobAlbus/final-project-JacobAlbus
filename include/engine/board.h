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
  Board(float window_size, const std::string& json_file_path);

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
  void RenderBoard(float window_size, const std::vector<glm::vec2>& player_movement_options) const;

 private:
  size_t board_size_;
  board_t board_;
};

} // namespace jjba_strategy

#endif //JJBA_STRATEGY_RPG_SRC_ENGINE_BOARD_H_
