#include <iostream>
#include <catch2/catch.hpp>

#include "engine/character.h"

using namespace jjba_strategy;

const std::string kBoardsFolderPath = "../../../assets/boards/";

TEST_CASE("Generate Characters") {
  SECTION("Throws Error when Allied List does not exist") {
    nlohmann::json board_state = Character::ReadJSONFile(kBoardsFolderPath + "board_wo_allies.json");
    REQUIRE_THROWS(Character::CheckIfCharactersExists(board_state));
  }

  SECTION("Throws Error when Enemy List does not exist") {
    nlohmann::json board_state = Character::ReadJSONFile(kBoardsFolderPath + "board_wo_enemies.json");
    REQUIRE_THROWS(Character::CheckIfCharactersExists(board_state));
  }

  SECTION("Throws Error when Allied List is empty") {
    nlohmann::json board_state = Character::ReadJSONFile(kBoardsFolderPath + "board_w_empty_allies.json");
    REQUIRE_THROWS(Character::CheckIfCharactersEmpty(board_state));
  }

  SECTION("Throws Error when Enemy List is empty") {
    nlohmann::json board_state = Character::ReadJSONFile(kBoardsFolderPath + "board_w_empty_enemies.json");
    REQUIRE_THROWS(Character::CheckIfCharactersEmpty(board_state));
  }

  SECTION("Throws Error when JSON is Null") {
    REQUIRE_THROWS(Character::ReadJSONFile(kBoardsFolderPath + "null_board.json"));
  }
}

TEST_CASE("Character Type Initialization") {
  SECTION("Brawler Type is initialized with correct values") {
    Character brawler = Character("brawler", glm::vec2(1, 5), "characters/jotaro.jpg", false, CharacterType::kBrawler, true);
    REQUIRE(brawler.GetHealth() == 200.0f);
    REQUIRE(brawler.GetPosition() == glm::vec2(1, 5));
    REQUIRE(brawler.GetAttacks()[0].kType == AttackType::kStarFinger);
    REQUIRE(brawler.GetName() == "brawler");
  }

  SECTION("Long Range Type is initialized with correct values") {
    Character long_range = Character("long", glm::vec2(1, 5), "characters/jotaro.jpg", false, CharacterType::kLongRange, true);
    REQUIRE(long_range.GetHealth() == 150.0f);
    REQUIRE(long_range.GetPosition() == glm::vec2(1, 5));
    REQUIRE(long_range.GetAttacks()[0].kType == AttackType::kStarFinger);
    REQUIRE(long_range.GetAttacks()[1].kType == AttackType::kEmeraldSplash);
    REQUIRE(long_range.GetName() == "long");
  }

  SECTION("Support Type is initialized with correct values") {
    Character support = Character("support", glm::vec2(-4, 5), "characters/jotaro.jpg", false, CharacterType::kSupport, true);
    REQUIRE(support.GetHealth() == 100.0f);
    REQUIRE(support.GetPosition() == glm::vec2(-4, 5));
    REQUIRE(support.GetAttacks()[0].kType == AttackType::kStarFinger);
    REQUIRE(support.GetAttacks()[1].kType == AttackType::kEmeraldSplash);
    REQUIRE(support.GetAttacks()[2].kType == AttackType::kHermitPurple);
    REQUIRE(support.GetName() == "support");
  }
}