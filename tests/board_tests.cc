#include <iostream>
#include <catch2/catch.hpp>

#include "engine/board.h"
#include "engine/game_engine.h"
#include <nlohmann/json.hpp>

using namespace jjba_strategy;

const std::string kBoardsFolderPath = "../../../assets/boards/";

TEST_CASE("Generate Board") {
  SECTION("Exceptions and Errors") {
    SECTION("Throws error when json is empty") {
      REQUIRE_THROWS(Board::ReadJSONFile(kBoardsFolderPath + "null_board.json"));
    }

    SECTION("Throws error when board object in json is empty") {
      nlohmann::json board_state = Board::ReadJSONFile(kBoardsFolderPath + "empty_board.json");
      REQUIRE_THROWS(Board::CheckIfBoardEmpty(board_state));
    }

    SECTION("Throws error when board object is not a square") {
      nlohmann::json board_state = Board::ReadJSONFile(kBoardsFolderPath + "non_square_board.json");
      REQUIRE_THROWS(Board::CheckIfBoardSquare(board_state));
    }
  }
}

