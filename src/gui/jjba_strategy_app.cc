#include <gui/jjba_strategy_app.h>

namespace jjba_strategy {

namespace visualizer {

JJBAStrategyApp::JJBAStrategyApp() {
  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
}

void JJBAStrategyApp::update() {
}

void JJBAStrategyApp::draw() {
  ci::Color8u background_color(0, 0, 0);
  ci::gl::clear(background_color);

  ci::gl::drawStringCentered(
      "balls",
      glm::vec2(kWindowSize / 2, kMargin / 2), ci::Color("white"));
  ci::gl::drawStringCentered(
      "nuts",
      glm::vec2(kWindowSize / 2, kMargin/ 0.75), ci::Color("white"));
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
