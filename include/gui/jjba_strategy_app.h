#pragma once
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "engine/game_engine.h"

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

  //TODO make seperate file for constants
  const float kWindowSize = 900;
  const std::string initial_board_file_path = "C:\\Users\\asus\\CLionProjects\\cinder_0.9.2_vc2015\\my-projects\\final-project-JacobAlbus\\assets\\boards\\board1.json";

 private:
  GameEngine game_engine_;
};

}  // namespace visualizer

}  // namespace jjba_strategy

