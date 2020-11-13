#include <gui/jjba_strategy_app.h>

namespace jjba_strategy {

namespace visualizer {

JJBAStrategyApp::JJBAStrategyApp() : simulation_ui_(),
                             particle_type_(ParticleType::kRed),
                             particle_count_message_("Particle Count: 0"),
                             particle_type_message_("Brush Particle Type: Red"),
                             gas_window_(ci::Rectf(kWindowSize / 4 - kGasWindowWidth,
                                                   kWindowSize / 2 - kGasWindowHeight,
                                                   kWindowSize / 4 + kGasWindowWidth,
                                                   kWindowSize / 2 + kGasWindowHeight)) {
  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
}

void JJBAStrategyApp::update() {
  simulation_ui_.UpdateSimulation(gas_window_);
}

void JJBAStrategyApp::draw() {
  ci::Color8u background_color(0, 0, 0);
  ci::gl::clear(background_color);

  simulation_ui_.RenderDynamicObjects();

  ci::gl::drawStringCentered(
      particle_count_message_,
      glm::vec2(kWindowSize / 2, kMargin / 2), ci::Color("white"));
  ci::gl::drawStringCentered(
      particle_type_message_,
      glm::vec2(kWindowSize / 2, kMargin/ 0.75), ci::Color("white"));

  ci::gl::color(255, 255, 255);
  ci::gl::drawStrokedRect(gas_window_);

  ci::gl::color(1, 0, 0);
  const float kHorizontalWindowRatio = 1.25f;

  ci::gl::drawStrokedRect(ci::Rectf(kWindowSize / kHorizontalWindowRatio - kHistogramWindowSize,
                                    kWindowSize / 6.0f - kHistogramWindowSize,
                                    kWindowSize / kHorizontalWindowRatio + kHistogramWindowSize,
                                    kWindowSize / 6.0f + kHistogramWindowSize));

  ci::gl::color(0, 0, 1);
  ci::gl::drawStrokedRect(ci::Rectf(kWindowSize / kHorizontalWindowRatio - kHistogramWindowSize,
                                    kWindowSize / 2.1f - kHistogramWindowSize,
                                    kWindowSize / kHorizontalWindowRatio + kHistogramWindowSize,
                                    kWindowSize / 2.1f + kHistogramWindowSize));

  ci::gl::color(0, 1, 0);
  ci::gl::drawStrokedRect(ci::Rectf(kWindowSize / kHorizontalWindowRatio - kHistogramWindowSize,
                                    kWindowSize / 1.25f - kHistogramWindowSize,
                                    kWindowSize / kHorizontalWindowRatio + kHistogramWindowSize,
                                    kWindowSize / 1.25f + kHistogramWindowSize));
}

void JJBAStrategyApp::mouseDown(ci::app::MouseEvent event) {
  size_t particle_count = simulation_ui_.GetSimulationParticles().size();
  particle_count_message_ = "Particle Count: " + std::to_string(particle_count);

  simulation_ui_.HandleParticleBrush(event.getPos(),
                                     gas_window_,
                                     particle_type_);
}

void JJBAStrategyApp::mouseDrag(ci::app::MouseEvent event) {
  mouseDown(event);
}

void JJBAStrategyApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_DELETE: {
      simulation_ui_.ClearSimulation();
      particle_count_message_ = "Particle Count: 0";
      break;
    }
    case ci::app::KeyEvent::KEY_ESCAPE: {
      exit(0);
      break;
    }
    case ci::app::KeyEvent::KEY_SPACE: {
      SwitchParticleType();
    }
  }
}


}  // namespace visualizer

}  // namespace jjba_strategy
