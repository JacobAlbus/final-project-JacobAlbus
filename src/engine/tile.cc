#include "engine/tile.h"
#include "cinder/app/App.h"

namespace jjba_strategy {

Tile::Tile(TileType type) : kType(type) {
  const std::string kPath1 = "C:\\Users\\Jamon\\CLionProjects\\cinder_0.9.2_vc2015\\my-projects\\final-project-JacobAlbus\\assets\\tiles\\";
  const std::string kPath2 = "../../../assets/tiles/";

  switch(type) {
    case kGrass: {
      ci::fs::path path = ci::fs::path("tiles/grass.png");
      //ci::fs::path path = ci::fs::path(kPath1 + "grass.png");
//      ci::fs::path path = ci::fs::path(kPath1 + "grass.png");
      image_ = ci::gl::Texture::create(ci::loadImage(cinder::app::loadAsset(path)));
      break;
    } case kDesert: {
      ci::fs::path path = ci::fs::path("tiles/sand.jpg");
//      ci::fs::path path = ci::fs::path(kPath1 +"sand.jpg");
//      ci::fs::path path = ci::fs::path(kPath1 + "sand.jpg");

      image_ = ci::gl::Texture::create(ci::loadImage(cinder::app::loadAsset(path)));
      break;
    } case kMountain: {
      ci::fs::path path = ci::fs::path("tiles/stone.png");
//      ci::fs::path path = ci::fs::path(kPath1 + "stone.png");
//      ci::fs::path path = ci::fs::path(kPath1 + "stone.png");

      image_ = ci::gl::Texture::create(ci::loadImage(cinder::app::loadAsset(path)));
      break;
    } case kWater: {
      ci::fs::path path = ci::fs::path("tiles/water.jpg");
//      ci::fs::path path = ci::fs::path(kPath1 + "water.jpg");
//      ci::fs::path path = ci::fs::path(kPath1 + "water.jpg");

      image_ = ci::gl::Texture::create(ci::loadImage(cinder::app::loadAsset(path)));
      break;
    } case kEmpty: {
      ci::fs::path path = ci::fs::path("tiles/empty.png");
//      ci::fs::path path = ci::fs::path(kPath1 + "empty.png");
//      ci::fs::path path = ci::fs::path(kPath2 + "empty.png");
      image_ = ci::gl::Texture::create(ci::loadImage(cinder::app::loadAsset(path)));
      break;
    }
  }
}

void Tile::RenderTile(const ci::Rectf& tile_location) const {
  ci::gl::draw(image_, tile_location);
}

} // namespace jjba_strategy