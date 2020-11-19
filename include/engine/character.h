#ifndef JJBA_STRATEGY_RPG_SRC_ENGINE_CHARACTER_H_
#define JJBA_STRATEGY_RPG_SRC_ENGINE_CHARACTER_H_

#include <string>
#include "cinder/gl/gl.h"
#include "nlohmann/json.hpp"

namespace jjba_strategy {

class Character {
 public:
  /**
   * Instantiates character
   * @param name of character
   * @param position of character
   * @param path to image file
   * @param whether or not character is initial player
   */
  Character(const std::string& name,
            const glm::vec2& position,
            const std::string& image_path,
            bool is_player);

  //TODO do I need big 5?
  inline Character& operator=(const Character& rhs) = default;

  /**
   * Updates position of player
   * @param new position of player
   */
  void UpdatePosition(const glm::vec2& updated_position);

  /**
   * Renders character at their position
   */
  void RenderCharacter(size_t board_size, float window_size) const;

  /**
   * Changes whether or not character is current player
   */
  void UpdateIsPlayer();

  static std::vector<Character> Character::GenerateCharacters(const std::string& json_file_path) {
    std::ifstream file(json_file_path);
    nlohmann::json board_state;
    file >> board_state;
    std::vector<Character> characters;

    for(const auto& json_characters : board_state["characters"]) {
      for(const auto& character: json_characters){
        std::string name = character[0];
        size_t x_position = character[1][0];
        size_t y_position = character[1][1];
        glm::vec2 position(x_position, y_position);
        std::string image_path = character[2];
        bool is_player = character[3];
        characters.emplace_back(name, position, image_path, is_player);
      }
    }

    return characters;
  }

  inline const std::string& GetName() const { return kName; };
  inline const glm::vec2& GetPosition() const { return position_; };
  inline const ci::gl::TextureRef& GetImage() const { return kImage; }
  inline bool IsPlayer() const { return is_player_; }

 private:
  /**
   * Calculates window/box where character should be rendered
   * @return box where character should be rendered
   */
  ci::Rectf CalculatePixelBoundingBox(size_t board_size, float window_size) const;

  bool is_player_;
  glm::vec2 position_;
  //TODO make const
  std::string kName;
  ci::gl::TextureRef kImage;
};

} // namespace jjba_strategy

#endif //JJBA_STRATEGY_RPG_SRC_ENGINE_CHARACTER_H_
