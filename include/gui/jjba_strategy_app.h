#pragma once
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "gui/render_engine.h"

namespace jjba_strategy {

namespace visualizer {

/**
 * Allows a user to visualize particle collisions in an ideal system
 */
class JJBAStrategyApp : public ci::app::App {
 public:
  /**
   * Instantiates App
   */
  JJBAStrategyApp();

  /**
   * Draws the state of the board
   */
  void draw() override;

  /**
   * Updates the state of the board
   */
  void update() override;

  /**
   * Calls methods depending on which key is pressed
   * @param event object containing pressed key
   */
  void keyDown(ci::app::KeyEvent event) override;

  const float kWindowSize = 900;
  const std::string kBoardsFolderPath = "C:\\Users\\Jamon\\CLionProjects\\cinder_0.9.2_vc2015\\my-projects\\final-project-JacobAlbus\\assets\\boards\\";

 private:
  RenderEngine render_engine_;
};

}  // namespace visualizer

}  // namespace jjba_strategy

