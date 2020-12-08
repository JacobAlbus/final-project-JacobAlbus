#ifndef JJBA_STRATEGY_RPG_SRC_ENGINE_CHARACTER_H_
#define JJBA_STRATEGY_RPG_SRC_ENGINE_CHARACTER_H_

#include <string>
#include "cinder/gl/gl.h"
#include "engine/attack.h"
#include <nlohmann/json.hpp>

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
   * @param index in CharacterType enum
   */
  Character(const std::string& name,
            const glm::vec2& position,
            const std::string& image_path,
            bool is_player,
            size_t character_type_index);

  /**
   * Copies values of passed character into a different character object
   * @param character object to be copied
   * @return copy of character object
   */
  inline Character& operator=(const Character& rhs) = default;

  /**
   * Renders character at their position
   */
  void RenderCharacter(size_t board_size, float window_size) const;

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
                                                              const std::string& characters_type);

  inline const glm::vec2& GetPosition() const { return position_; };
  inline bool IsPlayer() const { return is_player_; }
  inline float GetHealth() const { return health_; }
  inline const std::vector<Attack>& GetAttacks() const { return attacks_; }
  inline AttackType GetCurrentAttackType() const { return current_attack_type_; }
  inline void UpdateCurrentAttackType(AttackType new_type) { current_attack_type_ = new_type; }

  inline void ToggleIsPlayer() { is_player_ = !is_player_; }
  inline void ToggleIsTarget() { is_targeted_ = !is_targeted_; }
  inline void SetPosition(const glm::vec2 &updated_position) { position_ = updated_position; }

 private:
  /**
   * Calculates window/box where character should be rendered
   * @return box where character should be rendered
   */
  ci::Rectf CalculatePixelBoundingBox(size_t board_size, float window_size) const;

  /**
   * Health of character
   */
  float health_;
  /**
   * Whether or not character is being controlled
   */
  bool is_player_;
  /**
   * Whether or not character is currently being targeted
   */
  bool is_targeted_;
  /**
   * How many squares character can move in single turn
   */
  int movement_range_;
  /**
   * Position of character
   */
  glm::vec2 position_;
  /**
   * Name of Character
   */
  std::string name_;
  /**
   * Image object of character
   */
  ci::gl::TextureRef image_;
  /**
   * Vector containing all attacks character can perform
   */
  std::vector<Attack> attacks_;
  /**
   * Type of character. Determines health, movement range, and attack options
   */
  CharacterType character_type;
  /**
   * Currently selected attack type
   */
  AttackType current_attack_type_;
};

} // namespace jjba_strategy

#endif //JJBA_STRATEGY_RPG_SRC_ENGINE_CHARACTER_H_
