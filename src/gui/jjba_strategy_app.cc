#include <gui/jjba_strategy_app.h>

namespace jjba_strategy {

namespace visualizer {

JJBAStrategyApp::JJBAStrategyApp() : game_engine_(kWindowSize, initial_board_file_path) {

  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
}

void JJBAStrategyApp::update() {
}

void JJBAStrategyApp::draw() {
  game_engine_.RenderBoardState();
}

void JJBAStrategyApp::keyDown(ci::app::KeyEvent event) {
  game_engine_.HandleInput(event);
}


}  // namespace visualizer

}  // namespace jjba_strategy
