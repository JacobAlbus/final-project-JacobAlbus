#ifndef JJBA_STRATEGY_RPG_SRC_ENGINE_CHARACTER_H_
#define JJBA_STRATEGY_RPG_SRC_ENGINE_CHARACTER_H_

#include <string>
#include "cinder/gl/gl.h"
#include "engine/attack.h"
#include "nlohmann/json.hpp"

namespace jjba_strategy {

enum CharacterType {
  kBrawler,
  kLongRange,
  kSupport,
};

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
            bool is_player,
            bool is_targeted,
            size_t character_type_index);

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

  /**
   * Renders character face plate at top of the screen
   * @param whether or not the character is an anemy
   * @param size of board
   * @param index in order of face plates
   * @param size of window
   */
  void RenderCharacterFacePlate(bool is_enemy, size_t board_size,
                                size_t index, float window_size) const;

  /**
   * Updates health with passed value
   * @param passed value
   */
  void UpdateHealth(float new_health);

  /**
   * Calculates character movement options
   * @return vector containing all the tiles within character movement range
   */
  std::vector<glm::vec2> CalculateCharacterMovementOptions() const;

  /**
   * Calculates attack damage on other character then updates health
   * @param character object being attacked
   */
  void AttackCharacter(Character* character);

  /**
   * Reads characters from JSON file
   * @param path to json file containing characters
   * @param type of characters being read (enemy or allied)
   * @return vector of characters from JSON file
   */
  static std::vector<Character> Character::GenerateCharacters(const std::string& json_file_path,
                                                              const std::string& characters_type) {
    std::ifstream file(json_file_path);
    nlohmann::json board_state;
    file >> board_state;
    std::vector<Character> characters;

    for(const auto& json_characters : board_state[characters_type]) {
      for(const auto& character: json_characters){
        std::string name = character[0];
        size_t x_position = character[1][0];
        size_t y_position = character[1][1];
        glm::vec2 position(x_position, y_position);
        std::string image_path = character[2];
        bool is_player = character[3];
        size_t character_type_index = character[4];
        characters.emplace_back(name, position, image_path,
                                is_player, false, character_type_index);
      }
    }

    return characters;
  }

  inline const glm::vec2& GetPosition() const { return position_; };
  inline bool IsPlayer() const { return is_player_; }
  inline float GetHealth() const { return health_; }
  inline void UpdateIsTarget() { is_targeted_ = !is_targeted_; }
  inline const std::vector<Attack>& GetAttacks() const { return attacks_; }
  inline AttackType GetCurrentAttackType() const { return current_attack_type_; }
  inline void UpdateCurrentAttackType(AttackType new_type) { current_attack_type_ = new_type; }

 private:
  /**
   * Calculates window/box where character should be rendered
   * @return box where character should be rendered
   */
  ci::Rectf CalculatePixelBoundingBox(size_t board_size, float window_size) const;

  float health_;
  bool is_player_;
  bool is_targeted_;
  int movement_range_;
  glm::vec2 position_;
  std::string kName;
  ci::gl::TextureRef kImage;
  std::vector<Attack> attacks_;
  CharacterType character_type;
  AttackType current_attack_type_;
};

} // namespace jjba_strategy

#endif //JJBA_STRATEGY_RPG_SRC_ENGINE_CHARACTER_H_
