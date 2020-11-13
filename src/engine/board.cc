#include "engine/board.h"
#include <cinder/Rand.h>

namespace jjba_strategy {

Board::Board(size_t board_size) : kBoardSize(board_size) {
  for(size_t row = 0; row < kBoardSize; row++) {
    std::vector<Tile> empty;
    board_.push_back(empty);
    for(size_t column = 0; column < kBoardSize; column++) {
      //TODO fix magic
      auto type = static_cast<TileType>(ci::randInt(0, 4));
      board_[row].push_back(Tile(type));
    }
  }
}

} // namespace jjba_strategy