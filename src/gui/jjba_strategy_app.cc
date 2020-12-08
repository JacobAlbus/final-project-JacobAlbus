#include <gui/jjba_strategy_app.h>
#include "cinder/audio/Source.h"
#include "cinder/audio/Voice.h"

namespace jjba_strategy {

namespace visualizer {

ci::audio::VoiceRef mVoice;

JJBAStrategyApp::JJBAStrategyApp() : render_engine_(kWindowSize, kBoardsFolderPath) {
  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
}

void JJBAStrategyApp::update() {
  render_engine_.UpdateGameState();
}

void JJBAStrategyApp::draw() {
  render_engine_.RenderGame();
}

void JJBAStrategyApp::keyDown(ci::app::KeyEvent event) {
  render_engine_.HandleInput(event);
}

void JJBAStrategyApp::setup() {
  render_engine_.PlayMusic("audio/pillar_men_theme.mp3");
}

}  // namespace visualizer

}  // namespace jjba_strategy
