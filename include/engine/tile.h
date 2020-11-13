#ifndef JJBA_STRATEGY_RPG_SRC_ENGINE_TILE_H_
#define JJBA_STRATEGY_RPG_SRC_ENGINE_TILE_H_

#include "cinder/gl/gl.h"

namespace jjba_strategy {

enum TileType {
  kGrass,
  kDesert,
  kMountain,
  kWater,
};

class Tile {
 public:
  Tile(TileType type);

  inline const ci::Color& GetColor() const { return kTileColor; }

 private:
  ci::Color kTileColor;
};

} // namespace jjba_strategy
#endif //JJBA_STRATEGY_RPG_SRC_ENGINE_TILE_H_
