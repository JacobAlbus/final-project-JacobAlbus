#include <iostream>
#include <catch2/catch.hpp>

#include "engine/game_engine.h"

using namespace jjba_strategy;

bool IsEqual(const glm::vec2& pos1, const glm::vec2& pos2) {
  return pos1 == pos2;
}

TEST_CASE("A") {
  const std::string initial_board_file_path = "C:\\Users\\asus\\CLionProjects\\cinder_0.9.2_vc2015\\my-projects\\final-project-JacobAlbus\\assets\\boards\\board1.json";
  GameEngine engine = GameEngine(900.0f, initial_board_file_path);

  glm::vec2 nib(2, 2);
  std::vector<glm::vec2> positions = Character::GetCharactersPositions(engine.GetAlliedCharacters());
  if(std::any_of(engine.GetAlliedCharacters().begin(),
                 engine.GetAlliedCharacters().end(),
                 IsEqual)) {
    std::cout << "nib";
  } else {
    std::cout << "nig";
  }
}

