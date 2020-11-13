#include <gui/jjba_strategy_app.h>

namespace jjba_strategy {

namespace visualizer {

JJBAStrategyApp::JJBAStrategyApp() : render_engine_(kBoardSize) {
  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
}

void JJBAStrategyApp::update() {
}

void JJBAStrategyApp::draw() {
  render_engine_.RenderBoard();
}

void JJBAStrategyApp::mouseDown(ci::app::MouseEvent event) {
}

void JJBAStrategyApp::mouseDrag(ci::app::MouseEvent event) {
  mouseDown(event);
}

void JJBAStrategyApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_ESCAPE: {
      exit(0);
      break;
    }
  }
}


}  // namespace visualizer

}  // namespace jjba_strategy
