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
  RenderEngine(float window_size_, const std::string& boards_folder_path);

  /**
   * Renders the board and other UI components
   */
  void RenderGame() const;

  /**
   * Handles user inputs
   */
  void HandleInput(const ci::app::KeyEvent& event);

  /**
   * Updates Game State
   */
  void UpdateGameState();
 private:
  /**
   * Sets the color of the face plates
   * @param whether or not the player is allied
   */
  void SetFacePlateColor(bool is_player_allied) const;
  /**
   * Renders player input options
   */
  void RenderInputOptions() const;

  GameEngine game_engine_;
  const float kWindowSize;
};

} //namespace jjba_strategy

#endif //JJBA_STRATEGY_RPG_INCLUDE_GUI_RENDER_ENGINE_H_
