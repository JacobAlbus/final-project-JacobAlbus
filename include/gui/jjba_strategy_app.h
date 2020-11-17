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
   * Draws the particles and various UI elements
   */
  void draw() override;

  /**
   * Updates the positions and velocities of particles
   */
  void update() override;

  /**
   * Calls methods when mouse is clicked on screen
   * @param event object containing mouse coords
   */
  void mouseDown(ci::app::MouseEvent event) override;

  /**
   * Calls methods when mouse is dragged across screen
   * @param event object containing mouse coords
   */
  void mouseDrag(ci::app::MouseEvent event) override;

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

