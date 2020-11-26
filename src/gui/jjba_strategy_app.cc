#include <gui/jjba_strategy_app.h>

namespace jjba_strategy {

namespace visualizer {

JJBAStrategyApp::JJBAStrategyApp() : render_engine_(kWindowSize, initial_board_file_path) {
  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
}

void JJBAStrategyApp::update() {
}

void JJBAStrategyApp::draw() {
  render_engine_.RenderGame();
}

void JJBAStrategyApp::keyDown(ci::app::KeyEvent event) {
  render_engine_.HandleInput(event);
}

}  // namespace visualizer

}  // namespace jjba_strategy
