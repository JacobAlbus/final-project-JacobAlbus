#include <iostream>
#include <catch2/catch.hpp>

#include "nlohmann/json.hpp"
#include "engine/board.h"

using namespace jjba_strategy;

TEST_CASE("A") {
  std::ifstream file("C:\\Users\\asus\\CLionProjects\\cinder_0.9.2_vc2015\\my-projects\\final-project-JacobAlbus\\assets\\boards\\board1.json");
  nlohmann::json board_state;
  file >> board_state;

  for(const auto& characters : board_state["characters"]) {
    for(const auto& character: characters){
      std::string name = character[0];
      size_t x_position = character[1][0];
      size_t y_position = character[1][1];
      glm::vec2 position(x_position, y_position);
      std::string image_path = character[2];
      bool is_player = character[3];
    }
  }
}

