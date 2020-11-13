#ifndef JJBA_STRATEGY_RPG_SRC_ENGINE_BOARD_H_
#define JJBA_STRATEGY_RPG_SRC_ENGINE_BOARD_H_

#include "engine/tile.h"
#include <vector>

namespace jjba_strategy {

typedef std::vector<std::vector<Tile>> board_t;

class Board {
 public:
  Board(size_t board_size);

  inline const board_t& GetBoard() const { return board_; }
 private:
  size_t kBoardSize;
  board_t board_;
};

} // namespace jjba_strategy

#endif //JJBA_STRATEGY_RPG_SRC_ENGINE_BOARD_H_
