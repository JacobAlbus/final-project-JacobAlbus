#ifndef JJBA_STRATEGY_RPG_SRC_GUI_RENDER_ENGINE_H_
#define JJBA_STRATEGY_RPG_SRC_GUI_RENDER_ENGINE_H_

#include <engine/board.h>
#include <engine/game_engine.h>
#include "cinder/app/App.h"

namespace jjba_strategy {

class RenderEngine {
 public:
  RenderEngine(size_t board_size, float window_size);

  void HandleInput(const ci::app::KeyEvent& event);

  void RenderBoard() const;
 private:
  const float kWindowSize;
  const size_t kBoardSize;
  GameEngine engine_;
};

} // namespace jjba_strategy

#endif //JJBA_STRATEGY_RPG_SRC_GUI_RENDER_ENGINE_H_
