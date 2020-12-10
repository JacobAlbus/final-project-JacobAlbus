#include <iostream>
#include <catch2/catch.hpp>

#include "engine/game_engine.h"

using namespace jjba_strategy;

const std::string kBoardsFolderPath = "../../../assets/boards/";

TEST_CASE("Update Playable Character") {
  GameEngine engine = GameEngine(900.0f, kBoardsFolderPath, true);
  REQUIRE(engine.GetAlliedCharacters()[0].IsPlayer());

  engine.UpdatePlayableCharacter();
  REQUIRE(engine.GetEnemyCharacters()[0].IsPlayer());
}

TEST_CASE("IsCharacterAtTile") {
  GameEngine engine = GameEngine(900.0f, kBoardsFolderPath, true);
  REQUIRE(engine.IsCharacterAtTile(glm::vec2(6, 6)));
  REQUIRE_FALSE(engine.IsCharacterAtTile(glm::vec2(9, 5)));
}

TEST_CASE("Is Tile Off Screen") {
  GameEngine engine = GameEngine(900.0f, kBoardsFolderPath, true);
  REQUIRE_FALSE(engine.IsTileOffScreen(glm::vec2(5, 5)));
  REQUIRE(engine.IsTileOffScreen(glm::vec2(9, 5)));
}

TEST_CASE("Is Movement In Range") {
  GameEngine engine = GameEngine(900.0f, kBoardsFolderPath, true);
  std::vector<glm::vec2> options = engine.GetAlliedCharacters()[0].CalculateCharacterMovementOptions();
  REQUIRE(engine.IsMovementInRange(options, glm::vec2(4, 4)));
  REQUIRE_FALSE(engine.IsMovementInRange(options, glm::vec2(1, 1)));
}

TEST_CASE("Calculate Player Movmement") {
  GameEngine engine = GameEngine(900.0f, kBoardsFolderPath, true);
  std::vector<glm::vec2> options = engine.CalculatePlayerMovement();

  REQUIRE(options[0] == glm::vec2(4, 4));
  REQUIRE(options[1] == glm::vec2(4, 5));
  REQUIRE(options[2] == glm::vec2(4, 6));
  REQUIRE(options[3] == glm::vec2(5, 4));
  REQUIRE(options[4] == glm::vec2(5, 5));
  REQUIRE(options[5] == glm::vec2(5, 6));
  REQUIRE(options[6] == glm::vec2(6, 4));
  REQUIRE(options[7] == glm::vec2(6, 5));
  REQUIRE(options[8] == glm::vec2(6, 6));
}