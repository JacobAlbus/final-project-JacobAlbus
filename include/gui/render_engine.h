#ifndef JJBA_STRATEGY_RPG_SRC_GUI_RENDER_ENGINE_H_
#define JJBA_STRATEGY_RPG_SRC_GUI_RENDER_ENGINE_H_

#include <engine/board.h>
#include <engine/game_engine.h>
#include "cinder/app/App.h"

namespace jjba_strategy {

class RenderEngine {
 public:
  /**
   * Instantiates engine renderer
   * @param size of initial board
   * @param size of window
   */
  RenderEngine(size_t board_size, float window_size);

  /**
   * Performs character action based on input of player
   * @param event object containing input
   */
  void HandleInput(const ci::app::KeyEvent& event);

  void RenderBoard() const;
 private:
  const float kWindowSize;
  const size_t board_size_;
  GameEngine engine_;
};

} // namespace jjba_strategy

#endif //JJBA_STRATEGY_RPG_SRC_GUI_RENDER_ENGINE_H_
