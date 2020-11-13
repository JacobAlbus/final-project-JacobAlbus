#ifndef JJBA_STRATEGY_RPG_SRC_ENGINE_CHARACTER_H_
#define JJBA_STRATEGY_RPG_SRC_ENGINE_CHARACTER_H_

#include <string>
#include "cinder/gl/gl.h"

namespace jjba_strategy {

class Character {
 public:
  Character(const std::string& name, bool is_player);

  inline const std::string& GetName() const { return kName; };
  inline bool IsPlayer() const { return is_player_; };
  inline const ci::Color& GetColor() const { return character_color; };
 private:
  //TODO replace with image
  ci::Color character_color;
  const std::string& kName;
  bool is_player_;
};

} // namespace jjba_strategy

#endif //JJBA_STRATEGY_RPG_SRC_ENGINE_CHARACTER_H_
