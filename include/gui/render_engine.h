#ifndef JJBA_STRATEGY_RPG_INCLUDE_GUI_RENDER_ENGINE_H_
#define JJBA_STRATEGY_RPG_INCLUDE_GUI_RENDER_ENGINE_H_

#include "engine/game_engine.h"

namespace jjba_strategy {

class RenderEngine {
 public:
  /**
   * Instantiates a RenderEngine Object
   * @param size of window
   * @param path to json file containing board
   */
  RenderEngine(float kWindowSize, const std::string& json_file_path);

  /**
   * Renders the board and other UI components
   */
  void RenderGame() const;

  /**
   * Handles user inputs
   */
  void HandleInput(ci::app::KeyEvent event);
 private:
  GameEngine game_engine_;
};

} //namespace jjba_strategy

#endif //JJBA_STRATEGY_RPG_INCLUDE_GUI_RENDER_ENGINE_H_