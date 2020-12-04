#ifndef JJBA_STRATEGY_RPG_SRC_ENGINE_ATTACK_H_
#define JJBA_STRATEGY_RPG_SRC_ENGINE_ATTACK_H_

#include <string>

namespace jjba_strategy {

enum AttackType {
  kStarFinger,
  kEmeraldSplash,
  kHermitPurple
};

struct Attack {
 public:
  explicit Attack(AttackType type) : kType(type) {
    switch(kType) {
      case AttackType::kStarFinger :
        name_ = "Star Finger";
        base_power = 20.0f;
        break;
      case AttackType::kEmeraldSplash :
        name_ = "EmeraldSplash";
        base_power = 15.0f;
        break;
      case AttackType::kHermitPurple :
        name_ = "Hermit Purple";
        base_power = 10.0f;
        break;
    }
  };

  /**
   * Name of attack
   */
  std::string name_;

  /**
   * Base power of attack, used to calculate actual damage dealt
   */
  float base_power;

  /**
   * Enum representing type of attack
   */
  AttackType kType;
};

}

#endif //JJBA_STRATEGY_RPG_SRC_ENGINE_ATTACK_H_
