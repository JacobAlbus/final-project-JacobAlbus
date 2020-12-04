#include <iostream>
#include <catch2/catch.hpp>

#include "engine/character.h"

using namespace jjba_strategy;

const std::string kBoardsFolderPath = "C:\\Users\\asus\\CLionProjects\\cinder_0.9.2_vc2015\\my-projects\\final-project-JacobAlbus\\assets\\boards\\";

//TODO get paths to work w/o error
TEST_CASE("Generate Characters") {
  SECTION("Throws Error when Allied List is Empty") {

  }

  SECTION("Throws Error when Enemy List is Empty") {

  }

  SECTION("Throws Error when unrecognized team name is passed") {

  }

  SECTION("Throws Error when JSON is Null") {

  }

  SECTION("Works Properly") {
    std::vector<Character> allies = Character::GenerateCharacters(kBoardsFolderPath + "board1.json", "allied characters");
  }
}

TEST_CASE("Character Type Initialization") {
  SECTION("Brawler Type is initialized with correct values") {

  }

  SECTION("Long Range Type is initialized with correct values") {

  }

  SECTION("Support Type is initialized with correct values") {

  }
}