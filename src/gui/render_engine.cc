#include "gui/render_engine.h"

namespace jjba_strategy {

RenderEngine::RenderEngine(float window_size,
                           const std::string& boards_folder_path) :
                           kWindowSize_(window_size),
                           game_engine_(window_size, boards_folder_path) {}

void RenderEngine::RenderGame() const {
  if(game_engine_.InMainMenu()) {
    RenderMainMenu();
  } else {
    RenderGameState();
  }
}

void RenderEngine::HandleInput(const ci::app::KeyEvent& event) {
  bool in_main_menu_before_input = game_engine_.InMainMenu();
  game_engine_.HandleInput(event);

  if(game_engine_.InMainMenu()) {
    PlayMusic("audio/kira_theme.mp3");
  } else if(in_main_menu_before_input){
    PlayMusic("audio/main_theme.mp3");
  }

}

void RenderEngine::PlayMusic(const std::string& file_path) {
  ci::audio::SourceFileRef source = ci::audio::load(ci::app::loadAsset(file_path));
  audio_player_ = ci::audio::Voice::create(source);
  audio_player_->start();
}

void RenderEngine::UpdateGameState() {
  game_engine_.UpdateGameState();
}

void RenderEngine::RenderMainMenu() const {
  ci::fs::path path = ci::fs::path("tiles/main_menu.jpg");
  ci::gl::TextureRef kImage = ci::gl::Texture::create(ci::loadImage(cinder::app::loadAsset(path)));
  ci::gl::color(ci::Color("gray"));
  ci::gl::draw(kImage, ci::Rectf(0, 0, kWindowSize_, kWindowSize_));

  const float kInitialPosition = kWindowSize_ / 40.0f;
  const float kSpacing = kWindowSize_ / 15.0f;

  ci::gl::drawStringCentered("Jojo's Bizzare Strategy Game", glm::vec2(kWindowSize_ / 2, kInitialPosition),
                             ci::Color("white"), ci::Font("Impact", 80));

  const float kControlSpacing = 4.0f;
  const float kHowToPlaySpacing = 1.35f;
  const float kNormalFontSize = 25.0f;
  const float kHeaderFontSize = 40.0f;

  ci::gl::drawStringCentered("Controls", glm::vec2(kWindowSize_ / kControlSpacing, kInitialPosition + (kSpacing * 2)),
                             ci::Color("white"), ci::Font("Impact", kHeaderFontSize));
  ci::gl::drawStringCentered("Use WASD keys to navigate menus", glm::vec2(kWindowSize_ / kControlSpacing, kInitialPosition + (kSpacing * 3)),
                             ci::Color("white"), ci::Font("Impact", kNormalFontSize));
  ci::gl::drawStringCentered("Use Enter to confirm and Backspace to decline", glm::vec2(kWindowSize_ / kControlSpacing, kInitialPosition + (kSpacing * 4)),
                             ci::Color("white"), ci::Font("Impact", kNormalFontSize));
  ci::gl::drawStringCentered("Use ESC to go to main menu or exit game if already there", glm::vec2(kWindowSize_ / kControlSpacing, kInitialPosition + (kSpacing * 5)),
                             ci::Color("white"), ci::Font("Impact", kNormalFontSize));

  ci::gl::drawStringCentered("How to Play", glm::vec2(kWindowSize_ / kHowToPlaySpacing , kInitialPosition + (kSpacing * 2)),
                             ci::Color("white"), ci::Font("Impact", kHeaderFontSize));
  ci::gl::drawStringCentered("The goal is to move characters around the board", glm::vec2(kWindowSize_ / kHowToPlaySpacing , kInitialPosition + (kSpacing * 3)),
                             ci::Color("white"), ci::Font("Impact", kNormalFontSize));
  ci::gl::drawStringCentered("and kill the other team", glm::vec2(kWindowSize_ / kHowToPlaySpacing , kInitialPosition + (kSpacing * 3.3)),
                             ci::Color("white"), ci::Font("Impact", kNormalFontSize));
  ci::gl::drawStringCentered("Your characters move in a set order and can", glm::vec2(kWindowSize_ / kHowToPlaySpacing , kInitialPosition + (kSpacing * 4)),
                             ci::Color("white"), ci::Font("Impact", kNormalFontSize));
  ci::gl::drawStringCentered("only attack OR move each turn", glm::vec2(kWindowSize_ / kHowToPlaySpacing, kInitialPosition + (kSpacing * 4.3)),
                             ci::Color("white"), ci::Font("Impact", kNormalFontSize));

  ci::gl::drawStringCentered("Press any key to start playing!", glm::vec2(kWindowSize_ / 2, kInitialPosition + (kSpacing * 6)),
                             ci::Color("white"), ci::Font("Impact", kHeaderFontSize));
}

void RenderEngine::RenderGameState() const {
  game_engine_.RenderBoardState();

  std::vector<std::string> inputs;
  if(game_engine_.InInputMenu()) {
    inputs.emplace_back("Attack");
    inputs.emplace_back("Move Player");
    inputs.emplace_back("Skip");
  } else if(game_engine_.InAttackMenu()) {
    const std::vector<Attack> player_attacks = game_engine_.GetPlayer()->GetAttacks();
    for(const auto& attack : player_attacks) {
      inputs.emplace_back(attack.name_);
    }
  }

  RenderInputOptions(inputs);
  RenderAllFacePlates();

  ci::gl::drawStringCentered(game_engine_.GetMessage(), glm::vec2(kWindowSize_ / 2, kWindowSize_ / 10),
                             ci::Color("white"), ci::Font("Impact", 20));
}

void RenderEngine::RenderAllFacePlates() const {
  const characters_t& allied_characters = game_engine_.GetAlliedCharacters();
  const characters_t& enemy_characters = game_engine_.GetEnemyCharacters();
  bool is_player_allied = game_engine_.GetCharacterIndex() < allied_characters.size();

  SetAlliesFacePlateColor(is_player_allied);
  for(size_t index = 0; index < allied_characters.size(); index++) {
    bool is_character_enemy = false;
    allied_characters[index].RenderCharacterFacePlate(is_character_enemy,
                                                      game_engine_.GetBoardSize(),
                                                      index,
                                                      kWindowSize_);
  }

  SetEnemyFacePlateColor(is_player_allied);
  for(size_t index = 0; index < enemy_characters.size(); index++) {
    bool is_character_enemy = true;
    enemy_characters[index].RenderCharacterFacePlate(is_character_enemy,
                                                     game_engine_.GetBoardSize(),
                                                     index,
                                                     kWindowSize_);
  }
}

void RenderEngine::RenderInputOptions(const std::vector<std::string>& inputs) const {
  glm::vec2 bottom_right_corner(0, kWindowSize_);
  ci::Color color;

  for(size_t index = 0; index < inputs.size(); index++) {
    const float kBottomMargin = kWindowSize_ / 20.0f;
    const float kSideSpacing = (kWindowSize_ / 8.0f) * (index + 1.0f);

    if(game_engine_.GetInputType() == index) {
      color = ci::Color("blue");
    } else {
      color = ci::Color("white");
    }

    ci::gl::drawStringCentered(inputs[index],
                               bottom_right_corner - glm::vec2(-kSideSpacing, kBottomMargin),
                               color, ci::Font("Impact", 20));
  }
}

void RenderEngine::SetAlliesFacePlateColor(bool is_player_allied) const {
  if(is_player_allied) {
    ci::gl::color(ci::Color("white"));
  } else {
    ci::gl::color(ci::Color("gray"));
  }
}

void RenderEngine::SetEnemyFacePlateColor(bool is_player_allied) const {
  if(!is_player_allied) {
    ci::gl::color(ci::Color("white"));
  } else {
    ci::gl::color(ci::Color("gray"));
  }
}

} //namespace jjba_strategy
