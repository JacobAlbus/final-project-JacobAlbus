#ifndef JJBA_STRATEGY_RPG_SRC_ENGINE_CHARACTER_H_
#define JJBA_STRATEGY_RPG_SRC_ENGINE_CHARACTER_H_

#include <string>
#include "cinder/gl/gl.h"

namespace jjba_strategy {

class Character {
 public:
  Character(const std::string& name,
            const glm::vec2& position,
            const std::string& image_path,
            bool is_player);

  //TODO do I need big 5?
  inline Character& operator=(const Character& rhs) = default;

  void UpdatePosition(const glm::vec2& updated_position);

  void UpdateIsPlayer();

  inline const std::string& GetName() const { return kName; };
  inline const glm::vec2& GetPosition() const { return position_; };
  inline const ci::gl::TextureRef& GetImage() const { return kImage; }
  inline bool IsPlayer() const { return is_player_; }

 private:
  bool is_player_;
  glm::vec2 position_;
  //TODO make const
  std::string kName;
  ci::gl::TextureRef kImage;
};

} // namespace jjba_strategy

#endif //JJBA_STRATEGY_RPG_SRC_ENGINE_CHARACTER_H_
