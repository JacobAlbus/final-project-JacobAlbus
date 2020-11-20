#include "gui/render_engine.h"

namespace jjba_strategy {

RenderEngine::RenderEngine(float window_size,
                           const std::string& json_file_path) :
                           kWindowSize(window_size),
                           game_engine_(window_size, json_file_path) {}

void RenderEngine::RenderGame() const {
  game_engine_.RenderBoardState();

  const characters_t& allied_characters = game_engine_.GetAlliedCharacters();
  for(size_t index = 0; index < allied_characters.size(); index++) {
    allied_characters[index].RenderCharacterFacePlate(false,
                                                      game_engine_.GetBoardSize(),
                                                      index,
                                                      kWindowSize);
  }

  const characters_t& enemy_characters = game_engine_.GetEnemyCharacters();
  for(size_t index = 0; index < enemy_characters.size(); index++) {
    enemy_characters[index].RenderCharacterFacePlate(true,
                                                     game_engine_.GetBoardSize(),
                                                     index,
                                                     kWindowSize);
  }
}

void RenderEngine::HandleInput(const ci::app::KeyEvent& event) {
  game_engine_.HandleInput(event);
}

} //namespace jjba_strategy
