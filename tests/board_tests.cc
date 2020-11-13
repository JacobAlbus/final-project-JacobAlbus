#include <iostream>
#include <catch2/catch.hpp>
#include <cinder/Rand.h>

#include "engine/board.h"

using namespace jjba_strategy;

TEST_CASE("A") {
  board_t board_;
  size_t kBoardSize = 30;

  for(size_t row = 0; row < kBoardSize; row++) {
    std::vector<Tile> empty;
    board_.push_back(empty);
    for(size_t column = 0; column < kBoardSize; column++) {
      //TODO fix magic
      auto type = static_cast<TileType>(ci::randInt(0, 3));
      board_[row].push_back(Tile(type));
    }
  }
}

