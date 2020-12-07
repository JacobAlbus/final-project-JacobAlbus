#include <gui/jjba_strategy_app.h>
#include "cinder/audio/Source.h"
#include "cinder/audio/Voice.h"

namespace jjba_strategy {

namespace visualizer {

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
  ci::audio::SourceFileRef sourceFile = ci::audio::load(ci::app::loadAsset("audio/johnathan_theme.wav"));
  ci::audio::VoiceRef mVoice = ci::audio::Voice::create(sourceFile);
  mVoice->start();
}

}  // namespace visualizer

}  // namespace jjba_strategy
