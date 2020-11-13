#include "engine/board.h"
#include <cinder/Rand.h>

namespace jjba_strategy {

//TODO implement JSON reader
Board::Board(size_t board_size) : kBoardSize(board_size) {
  std::vector<Tile> empty;
  board_.push_back(empty);
  board_.push_back(empty);
  board_.push_back(empty);
  board_.push_back(empty);

  board_[0].push_back(Tile(TileType::kMountain));
  board_[0].push_back(Tile(TileType::kMountain));
  board_[0].push_back(Tile(TileType::kMountain));
  board_[0].push_back(Tile(TileType::kMountain));

  board_[1].push_back(Tile(TileType::kGrass));
  board_[1].push_back(Tile(TileType::kGrass));
  board_[1].push_back(Tile(TileType::kWater));
  board_[1].push_back(Tile(TileType::kWater));

  board_[2].push_back(Tile(TileType::kGrass));
  board_[2].push_back(Tile(TileType::kGrass));
  board_[2].push_back(Tile(TileType::kWater));
  board_[2].push_back(Tile(TileType::kDesert));

  board_[3].push_back(Tile(TileType::kGrass));
  board_[3].push_back(Tile(TileType::kGrass));
  board_[3].push_back(Tile(TileType::kWater));
  board_[3].push_back(Tile(TileType::kDesert));
}

} // namespace jjba_strategy