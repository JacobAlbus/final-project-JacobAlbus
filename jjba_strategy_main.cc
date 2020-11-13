#include "gui/jjba_strategy_app.h"

using jjba_strategy::visualizer::JJBAStrategyApp;

void prepareSettings(JJBAStrategyApp::Settings* settings) {
  settings->setResizable(false);
}

CINDER_APP(JJBAStrategyApp, ci::app::RendererGl, prepareSettings);
