#include "engine/board.h"
#include "nlohmann/json.hpp"

namespace jjba_strategy {

Board::Board(float window_size, const std::string& json_file_path) {
  GenerateBoard(json_file_path);
  board_size_ = board_.size();
}

void Board::GenerateBoard(const std::string& json_file_path) {
  board_.clear();
  std::ifstream file(json_file_path);
  nlohmann::json board_state;
  file >> board_state;

  for(const auto& file_row : board_state["board"]) {
    std::vector<Tile> board_row;
    for(const auto& file_tile : file_row) {
      Tile board_tile = Tile(static_cast<TileType>(*file_tile.begin()));
      board_row.push_back(board_tile);
    }
    board_.push_back(board_row);
  }

  board_size_ = board_.size();
}

void Board::RenderBoard(float window_size, const std::vector<glm::vec2>& player_movement_options) const {
  const auto kTileSize = static_cast<float>(window_size / board_size_);

  for (size_t row = 0; row < board_size_; ++row) {
    for (size_t col = 0; col < board_size_; ++col) {

      for(const auto& position : player_movement_options) {
        if(glm::vec2(row, col) == position) {
          ci::gl::color(ci::Color("green"));
          break;
        } else {
          ci::gl::color(ci::Color("white"));
        }
      }

      glm::vec2 pixel_top_left = glm::vec2(col * kTileSize, row * kTileSize);
      glm::vec2 pixel_bottom_right = pixel_top_left +
                                     glm::vec2(kTileSize, kTileSize);

      ci::Rectf pixel_bounding_box(pixel_top_left, pixel_bottom_right);

      const auto& tile = board_[row][col];
      tile.RenderTile(pixel_bounding_box);
    }
  }
}

} // namespace jjba_strategy