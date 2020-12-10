#include "engine/board.h"
#include <nlohmann/json.hpp>

namespace jjba_strategy {

Board::Board(const std::string& json_file_path, bool is_unit_test) {
  if(is_unit_test) {
    std::vector<Tile> empty_row;

    board_.push_back(empty_row);
    board_[0].push_back(Tile(TileType::kGrass, is_unit_test));
    board_[0].push_back(Tile(TileType::kGrass, is_unit_test));
    board_[0].push_back(Tile(TileType::kGrass, is_unit_test));
    board_[0].push_back(Tile(TileType::kGrass, is_unit_test));

    board_.push_back(empty_row);
    board_[1].push_back(Tile(TileType::kDesert, is_unit_test));
    board_[1].push_back(Tile(TileType::kDesert, is_unit_test));
    board_[1].push_back(Tile(TileType::kDesert, is_unit_test));
    board_[1].push_back(Tile(TileType::kDesert, is_unit_test));

    board_.push_back(empty_row);
    board_[2].push_back(Tile(TileType::kWater, is_unit_test));
    board_[2].push_back(Tile(TileType::kWater, is_unit_test));
    board_[2].push_back(Tile(TileType::kWater, is_unit_test));
    board_[2].push_back(Tile(TileType::kWater, is_unit_test));

    board_.push_back(empty_row);
    board_[3].push_back(Tile(TileType::kMountain, is_unit_test));
    board_[3].push_back(Tile(TileType::kMountain, is_unit_test));
    board_[3].push_back(Tile(TileType::kMountain, is_unit_test));
    board_[3].push_back(Tile(TileType::kMountain, is_unit_test));
  } else {
    GenerateBoard(json_file_path);
    board_size_ = board_.size();
  }
}

void Board::GenerateBoard(const std::string& json_file_path) {
  board_.clear();

  nlohmann::json board_state = ReadJSONFile(json_file_path);
  CheckIfBoardExists(board_state);
  CheckIfBoardEmpty(board_state);
  CheckIfBoardSquare(board_state);

  for(const auto& file_row : board_state["board"]) {
    std::vector<Tile> board_row;
    for(const auto& file_tile : file_row) {
      bool is_unit_test = false;
      Tile board_tile = Tile(static_cast<TileType>(*file_tile.begin()), is_unit_test);
      board_row.push_back(board_tile);
    }
    board_.push_back(board_row);
  }

  board_size_ = board_.size();
}

void Board::RenderBoard(float window_size,
                        bool is_player_moving,
                        const glm::vec2& selected_movement_option,
                        const std::vector<glm::vec2>& player_movement_options) const {
  const auto kTileSize = static_cast<float>(window_size / board_size_);

  for (size_t row = 0; row < board_size_; ++row) {
    for (size_t col = 0; col < board_size_; ++col) {

      glm::vec2 current_tile(row, col);
      UpdateCharacterColor(is_player_moving, selected_movement_option,
                           current_tile, player_movement_options);

      glm::vec2 pixel_top_left = glm::vec2(col * kTileSize, row * kTileSize);
      glm::vec2 pixel_bottom_right = pixel_top_left +
                                     glm::vec2(kTileSize, kTileSize);

      ci::Rectf pixel_bounding_box(pixel_top_left, pixel_bottom_right);

      const auto& tile = board_[row][col];
      tile.RenderTile(pixel_bounding_box);
    }
  }
}

nlohmann::json Board::ReadJSONFile(const std::string& json_file_path) {
  std::ifstream file(json_file_path);
  nlohmann::json board_state;

  try {
    file >> board_state;
  }
  catch (nlohmann::detail::parse_error& ex) {
    std::cerr << "Passed JSON is Null" << ex.byte << std::endl;
    throw std::invalid_argument("");
  }

  return board_state;
}

void Board::CheckIfBoardSquare(const nlohmann::json& board_state) {
  for(const auto& row : board_state["board"]) {
    if(board_state["board"].size() != row.size()) {
      std::cerr << "The board object in the passed JSON is not a square" << std::endl;
      throw std::exception("");
    }
  }
}

void Board::CheckIfBoardEmpty(const nlohmann::json &board_state) {
  if(board_state["board"].empty()) {
    std::cerr << "The board object in the passed JSON is empty" << std::endl;
    throw std::exception("");
  }
}

void Board::CheckIfBoardExists(const nlohmann::json& board_state) {
  bool board_exists = false;

  for (auto it = board_state.begin(); it != board_state.end(); it++){
    const auto& key = it.key();
    if(key == "board") {
      board_exists = true;
    }
  }

  if(!board_exists) {
    std::cerr << "The board object does not exist in the passed JSON file" << std::endl;
    throw std::exception("");
  }
}

void Board::UpdateCharacterColor(bool is_player_moving,
                                 const glm::vec2& selected_movement_option,
                                 const glm::vec2& current_tile,
                                 const std::vector<glm::vec2>& player_movement_options)
                                 const {
  if(is_player_moving) {
    for(const auto& position : player_movement_options) {
      if(current_tile == selected_movement_option) {
        ci::gl::color(ci::Color("red"));
        break;
      } else if(current_tile == position) {
        ci::gl::color(ci::Color("green"));
        break;
      } else {
        ci::gl::color(ci::Color("white"));
      }
    }
  } else {
    ci::gl::color(ci::Color("white"));
  }
}

} // namespace jjba_strategy