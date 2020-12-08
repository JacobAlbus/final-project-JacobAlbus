#include "engine/tile.h"
#include "cinder/app/App.h"

namespace jjba_strategy {

Tile::Tile(TileType type) : kType(type) {
  switch(type) {
    case kGrass: {
      ci::fs::path path = ci::fs::path("tiles/grass.png");
      kImage = ci::gl::Texture::create(ci::loadImage(cinder::app::loadAsset(path)));
      break;
    } case kDesert: {
      ci::fs::path path = ci::fs::path("tiles/sand.jpg");
      kImage = ci::gl::Texture::create(ci::loadImage(cinder::app::loadAsset(path)));
      break;
    } case kMountain: {
      ci::fs::path path = ci::fs::path("tiles/stone.png");
      kImage = ci::gl::Texture::create(ci::loadImage(cinder::app::loadAsset(path)));
      break;
    } case kWater: {
      ci::fs::path path = ci::fs::path("tiles/water.jpg");
      kImage = ci::gl::Texture::create(ci::loadImage(cinder::app::loadAsset(path)));
      break;
    } case kEmpty: {
      ci::fs::path path = ci::fs::path("tiles/empty.png");
      kImage = ci::gl::Texture::create(ci::loadImage(cinder::app::loadAsset(path)));
      break;
    }
  }
}

void Tile::RenderTile(const ci::Rectf& tile_location) const {
  ci::gl::draw(kImage, tile_location);
}

} // namespace jjba_strategy