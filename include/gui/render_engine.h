#ifndef JJBA_STRATEGY_RPG_SRC_GUI_RENDER_ENGINE_H_
#define JJBA_STRATEGY_RPG_SRC_GUI_RENDER_ENGINE_H_

#include <engine/board.h>

namespace jjba_strategy {

class RenderEngine {
 public:
  RenderEngine(size_t board_size, float window_size);

  void RenderBoard() const;
 private:
  const float kWindowSize;
  const size_t kBoardSize;
  Board board_;
};

} // namespace jjba_strategy

#endif //JJBA_STRATEGY_RPG_SRC_GUI_RENDER_ENGINE_H_
