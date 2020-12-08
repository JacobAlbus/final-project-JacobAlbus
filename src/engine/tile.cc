#include "engine/tile.h"
#include "cinder/app/App.h"

namespace jjba_strategy {

Tile::Tile(TileType type) : kType(type) {
  switch(type) {
    case kGrass: {
      ci::fs::path path = ci::fs::path("tiles/grass.png");
      image_ = ci::gl::Texture::create(ci::loadImage(cinder::app::loadAsset(path)));
      break;
    } case kDesert: {
      ci::fs::path path = ci::fs::path("tiles/sand.jpg");
      image_ = ci::gl::Texture::create(ci::loadImage(cinder::app::loadAsset(path)));
      break;
    } case kMountain: {
      ci::fs::path path = ci::fs::path("tiles/stone.png");
      image_ = ci::gl::Texture::create(ci::loadImage(cinder::app::loadAsset(path)));
      break;
    } case kWater: {
      ci::fs::path path = ci::fs::path("tiles/water.jpg");
      image_ = ci::gl::Texture::create(ci::loadImage(cinder::app::loadAsset(path)));
      break;
    } case kEmpty: {
      ci::fs::path path = ci::fs::path("tiles/empty.png");
      image_ = ci::gl::Texture::create(ci::loadImage(cinder::app::loadAsset(path)));
      break;
    }
  }
}

void Tile::RenderTile(const ci::Rectf& tile_location) const {
  ci::gl::draw(image_, tile_location);
}

} // namespace jjba_strategy