#include "gui/render_engine.h"

namespace jjba_strategy {

RenderEngine::RenderEngine(float kWindowSize,
                           const std::string& json_file_path) :
                           game_engine_(kWindowSize, json_file_path) {}

void RenderEngine::RenderGame() const {
  game_engine_.RenderBoardState();
}

void RenderEngine::HandleInput(ci::app::KeyEvent event) {
  game_engine_.HandleInput(event);
}

} //namespace jjba_strategy
