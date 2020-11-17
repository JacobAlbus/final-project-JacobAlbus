#include "engine/board.h"
#include "nlohmann/json.hpp"

namespace jjba_strategy {

Board::Board() {
  //TODO fix file pathing
  std::ifstream file("C:\\Users\\asus\\CLionProjects\\cinder_0.9.2_vc2015\\my-projects\\final-project-JacobAlbus\\assets\\boards\\board1.json");
  nlohmann::json board_state;
  file >> board_state;

  for(const auto& file_row : board_state["board"]) {
    std::vector<Tile> board_row;
    for(const auto& file_tile : file_row) {
      Tile board_tile = Tile(static_cast<TileType>(*file_tile.begin()));
      board_row.push_back(board_tile);
    }
    board_.push_back(board_row);
  }
}

} // namespace jjba_strategy