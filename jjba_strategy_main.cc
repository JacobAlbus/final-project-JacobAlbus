#include "gui/jjba_strategy_app.h"

using ideal_gas::visualizer::IdealGasApp;

void prepareSettings(IdealGasApp::Settings* settings) {
  settings->setResizable(false);
}

CINDER_APP(IdealGasApp, ci::app::RendererGl, prepareSettings);
