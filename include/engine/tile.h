#ifndef JJBA_STRATEGY_RPG_SRC_ENGINE_TILE_H_
#define JJBA_STRATEGY_RPG_SRC_ENGINE_TILE_H_

#include "cinder/gl/gl.h"
#include "engine/character.h"

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


  inline const ci::gl::TextureRef& GetImage() const { return kImage; }

 private:
  ci::gl::TextureRef kImage;
};

} // namespace jjba_strategy

#endif //JJBA_STRATEGY_RPG_SRC_ENGINE_TILE_H_
