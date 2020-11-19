#include "gui/render_engine.h"

namespace jjba_strategy {

RenderEngine::RenderEngine(float window_size,
                           const std::string& json_file_path) :
                           engine_(window_size, json_file_path) {}

void RenderEngine::RenderBoard() const {
  engine_.RenderBoardState();
}

void RenderEngine::HandleInput(const ci::app::KeyEvent& event) {
  engine_.HandleInput(event);
}

} // namespace jjba_strategy