#include "gui/render_engine.h"

namespace jjba_strategy {

RenderEngine::RenderEngine(size_t board_size,
                           float window_size) :
                           kBoardSize(board_size),
                           kWindowSize(window_size),
                           board_(board_size) {}

void RenderEngine::RenderBoard() const {
  const auto kTileSize = static_cast<float>(kWindowSize / kBoardSize);

  for (size_t row = 0; row < kBoardSize; ++row) {
    for (size_t col = 0; col < kBoardSize; ++col) {

      const auto& tile = board_.GetBoard()[row][col];
      ci::gl::color(tile.GetColor());

      glm::vec2 pixel_top_left = glm::vec2(col * kTileSize, row * kTileSize);
      glm::vec2 pixel_bottom_right = pixel_top_left +
                                     glm::vec2(kTileSize, kTileSize);

      ci::Rectf pixel_bounding_box(pixel_top_left, pixel_bottom_right);

      ci::gl::drawSolidRect(pixel_bounding_box);

      ci::gl::color(ci::Color("black"));
      ci::gl::drawStrokedRect(pixel_bounding_box);
    }
  }
}

} // namespace jjba_strategy