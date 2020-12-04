#include "gui/render_engine.h"

namespace jjba_strategy {

RenderEngine::RenderEngine(float window_size,
                           const std::string& boards_folder_path) :
                           kWindowSize(window_size),
                           game_engine_(window_size, boards_folder_path) {}

void RenderEngine::RenderGame() const {
  game_engine_.RenderBoardState();

  std::vector<std::string> inputs;
  inputs.emplace_back("Attack");
  inputs.emplace_back("Move Player");

  RenderInputOptions(inputs);
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

void RenderEngine::RenderInputOptions(const std::vector<std::string>& inputs ) const {
  glm::vec2 bottom_right_corner(0, kWindowSize);
  ci::Color color;

  for(size_t index = 0; index < inputs.size(); index++) {
    const float kBottomMargin = kWindowSize / 20.0f;
    const float kSideSpacing = kBottomMargin * (index + 1.0f);

    if(static_cast<size_t>(game_engine_.GetInputType()) == index) {
      color = ci::Color("blue");
    } else {
      color = ci::Color("white");
    }

    ci::gl::drawStringCentered(inputs[index],
                               bottom_right_corner - glm::vec2(-kSideSpacing, kBottomMargin),
                               color);
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
