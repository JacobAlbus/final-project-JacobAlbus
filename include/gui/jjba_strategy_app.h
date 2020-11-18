#pragma once
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "render_engine.h"

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

  //TODO make seperate file for constants/integrate JSON
  const float kWindowSize = 900;
  const size_t kBoardSize = 10;

 private:
  RenderEngine render_engine_;
};

}  // namespace visualizer

}  // namespace jjba_strategy

