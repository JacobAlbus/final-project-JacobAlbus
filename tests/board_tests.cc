#include <iostream>
#include <catch2/catch.hpp>

#include "nlohmann/json.hpp"
#include "engine/board.h"

using namespace jjba_strategy;

TEST_CASE("A") {
  std::ifstream i("C:\\Users\\asus\\CLionProjects\\cinder_0.9.2_vc2015\\my-projects\\final-project-JacobAlbus\\assets\\boards\\board1.json");
  nlohmann::json j;
  i >> j;

  board_t board;
  for(const auto& row : j["board"]) {
    std::vector<Tile> enum_row;
    for(const auto& item : row) {
      Tile tile = Tile(static_cast<TileType>(*item.begin()));
      enum_row.push_back(tile);
    }
    board.push_back(enum_row);
  }
}

