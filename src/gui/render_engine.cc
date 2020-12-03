#include "gui/render_engine.h"

namespace jjba_strategy {

RenderEngine::RenderEngine(float window_size,
                           const std::string& boards_folder_path) :
                           kWindowSize(window_size),
                           game_engine_(window_size, boards_folder_path) {}

void RenderEngine::RenderGame() const {
  game_engine_.RenderBoardState();
  RenderInputOptions();
  RenderAllFacePlates();
  ci::gl::drawStringCentered(game_engine_.GetMessage(), glm::vec2(kWindowSize / 2, kWindowSize / 10),
                             ci::Color("white"));
}

void RenderEngine::HandleInput(const ci::app::KeyEvent& event) {
  game_engine_.HandleInput(event);
}

void RenderEngine::UpdateGameState() {
  game_engine_.UpdateGameState();
}

void RenderEngine::RenderAllFacePlates() const {
  const characters_t& allied_characters = game_engine_.GetAlliedCharacters();
  const characters_t& enemy_characters = game_engine_.GetEnemyCharacters();
  bool is_player_allied = game_engine_.GetCharacterIndex() < allied_characters.size();

  SetAlliesFacePlateColor(is_player_allied);
  for(size_t index = 0; index < allied_characters.size(); index++) {
    bool is_character_enemy = false;
    allied_characters[index].RenderCharacterFacePlate(is_character_enemy,
                                                      game_engine_.GetBoardSize(),
                                                      index,
                                                      kWindowSize);
  }

  SetEnemyFacePlateColor(is_player_allied);
  for(size_t index = 0; index < enemy_characters.size(); index++) {
    bool is_character_enemy = true;
    enemy_characters[index].RenderCharacterFacePlate(is_character_enemy,
                                                     game_engine_.GetBoardSize(),
                                                     index,
                                                     kWindowSize);
  }
}

void RenderEngine::RenderInputOptions() const {
  glm::vec2 bottom_right_corner(0, kWindowSize);

  switch(game_engine_.GetInputType()) {
    case InputType::kAttack :
      ci::gl::drawStringCentered("Attack",
                                 bottom_right_corner - glm::vec2(-(kWindowSize / 20), kWindowSize / 20),
                                 ci::Color("blue"));
      ci::gl::drawStringCentered("Move Player",
                                 bottom_right_corner - glm::vec2(-(kWindowSize / 8), kWindowSize / 20),
                                 ci::Color("white"));
      break;
    case InputType::kMovementInput :
      ci::gl::drawStringCentered("Attack",
                                 bottom_right_corner - glm::vec2(-(kWindowSize / 20), kWindowSize / 20),
                                 ci::Color("white"));
      ci::gl::drawStringCentered("Move Player",
                                 bottom_right_corner - glm::vec2(-(kWindowSize / 8), kWindowSize / 20),
                                 ci::Color("blue"));
      break;
    case InputType::kGameOver :
      break;
  }
}

void RenderEngine::SetAlliesFacePlateColor(bool is_player_allied) const {
  if(is_player_allied) {
    ci::gl::color(ci::Color("white"));
  } else {
    ci::gl::color(ci::Color("gray"));
  }
}

void RenderEngine::SetEnemyFacePlateColor(bool is_player_allied) const {
  if(!is_player_allied) {
    ci::gl::color(ci::Color("white"));
  } else {
    ci::gl::color(ci::Color("gray"));
  }
}

} //namespace jjba_strategy
