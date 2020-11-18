#include "gui/render_engine.h"

namespace jjba_strategy {

RenderEngine::RenderEngine(size_t board_size,
                           float window_size) :
                           board_size_(board_size),
                           kWindowSize(window_size),
                           engine_(board_size) {}

void RenderEngine::RenderBoard() const {
  const auto kTileSize = static_cast<float>(kWindowSize / board_size_);

  for (size_t row = 0; row < board_size_; ++row) {
    for (size_t col = 0; col < board_size_; ++col) {

      glm::vec2 pixel_top_left = glm::vec2(col * kTileSize, row * kTileSize);
      glm::vec2 pixel_bottom_right = pixel_top_left +
          glm::vec2(kTileSize, kTileSize);

      ci::Rectf pixel_bounding_box(pixel_top_left, pixel_bottom_right);
      ci::gl::color(ci::Color("white"));

      //TODO should have a character objects attached to tiles?
      const glm::vec2 kPosition = glm::vec2(row, col);
      if(engine_.IsCharacterAtTile(kPosition)) {
        const auto& character = engine_.FindCharacterAtPosition(kPosition);
        character->RenderCharacter(pixel_bounding_box);

      } else {
        const auto& tile = engine_.GetBoard()[row][col];
        tile.RenderTile(pixel_bounding_box);
      }
    }
  }
}

void RenderEngine::HandleInput(const ci::app::KeyEvent& event) {
  engine_.HandleInput(event);
}

} // namespace jjba_strategy