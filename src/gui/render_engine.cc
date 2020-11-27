#include "gui/render_engine.h"

namespace jjba_strategy {

RenderEngine::RenderEngine(float window_size,
                           const std::string& json_file_path) :
                           kWindowSize(window_size),
                           game_engine_(window_size, json_file_path) {}

void RenderEngine::RenderGame() const {
  game_engine_.RenderBoardState();

  const characters_t& allied_characters = game_engine_.GetAlliedCharacters();
  bool is_player_allied = game_engine_.GetCharacterIndex() < allied_characters.size();
  if(is_player_allied) {
    ci::gl::color(ci::Color("white"));
  } else {
    ci::gl::color(ci::Color("gray"));
  }
  for(size_t index = 0; index < allied_characters.size(); index++) {
    allied_characters[index].RenderCharacterFacePlate(false,
                                                      game_engine_.GetBoardSize(),
                                                      index,
                                                      kWindowSize);
  }

  if(is_player_allied) {
    ci::gl::color(ci::Color("gray"));
  } else {
    ci::gl::color(ci::Color("white"));
  }
  const characters_t& enemy_characters = game_engine_.GetEnemyCharacters();
  for(size_t index = 0; index < enemy_characters.size(); index++) {
    enemy_characters[index].RenderCharacterFacePlate(true,
                                                     game_engine_.GetBoardSize(),
                                                     index,
                                                     kWindowSize);
  }

  RenderInputOptions();
}

void RenderEngine::HandleInput(const ci::app::KeyEvent& event) {
  game_engine_.HandleInput(event);
}

//TODO is fine that I "hard-code" each input option
void RenderEngine::RenderInputOptions() const {
  glm::vec2 nib(0, kWindowSize);

  switch(game_engine_.GetInputType()) {
    case InputType::kAttack :
      ci::gl::drawStringCentered("Attack", nib - glm::vec2(-(kWindowSize / 20), kWindowSize / 20),
                                 ci::Color("blue"));
      ci::gl::drawStringCentered("Move Player", nib - glm::vec2(-(kWindowSize / 8), kWindowSize / 20),
                                 ci::Color("white"));
      break;
    case InputType::kMovementInput :
      ci::gl::drawStringCentered("Attack", nib - glm::vec2(-(kWindowSize / 20), kWindowSize / 20),
                                 ci::Color("white"));
      ci::gl::drawStringCentered("Move Player", nib - glm::vec2(-(kWindowSize / 8), kWindowSize / 20),
                                 ci::Color("blue"));
      break;
  }
}

} //namespace jjba_strategy
