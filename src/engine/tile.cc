#include "engine/tile.h"

namespace jjba_strategy {


Tile::Tile(TileType type) {
  switch(type) {
    case kGrass:
      kTileColor = ci::Color(0, 1, 0);
      break;
    case kDesert:
      kTileColor = ci::Color(1, 1, 0);
      break;
    case kMountain:
      kTileColor = ci::Color(1, 1, 1);
      break;
    case kWater:
      kTileColor = ci::Color(0, 0, 1);
      break;
  }
}

}