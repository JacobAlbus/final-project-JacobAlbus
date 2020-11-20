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
  kEmpty,
};

class Tile {
 public:
  /**
   * Instantiates tile based on TileType passed
   * @param given TileType enum
   */
  Tile(TileType type);

  /**
   * Renders tile at given location
   * @param location of tile
   */
  void RenderTile(const ci::Rectf& tile_location) const;

 private:
  ci::gl::TextureRef kImage;
};

} // namespace jjba_strategy

#endif //JJBA_STRATEGY_RPG_SRC_ENGINE_TILE_H_
