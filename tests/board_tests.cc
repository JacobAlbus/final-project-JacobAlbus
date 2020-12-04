#include <iostream>
#include <catch2/catch.hpp>

#include "engine/board.h"
#include "engine/game_engine.h"
using namespace jjba_strategy;

const std::string kBoardsFolderPath = "C:\\Users\\asus\\CLionProjects\\cinder_0.9.2_vc2015\\my-projects\\final-project-JacobAlbus\\assets\\boards\\";

//TODO fix error handling
TEST_CASE("Generate Board") {
  SECTION("Throws error when json is empty") {
    GameEngine engine = GameEngine(900.0f, kBoardsFolderPath);
  }

  SECTION("Throws error when board object in json is empty") {

  }

  SECTION("Throws error when board object is not a square") {

  }
}

