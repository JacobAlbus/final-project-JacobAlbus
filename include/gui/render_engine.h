#ifndef JJBA_STRATEGY_RPG_INCLUDE_GUI_RENDER_ENGINE_H_
#define JJBA_STRATEGY_RPG_INCLUDE_GUI_RENDER_ENGINE_H_

#include "engine/game_engine.h"
#include "cinder/audio/Voice.h"

namespace jjba_strategy {

class RenderEngine {
 public:
  /**
   * Instantiates a RenderEngine Object
   * @param size of window
   * @param path to json file containing board
   */
  RenderEngine(float window_size_, const std::string& boards_folder_path);

  /**
   * Renders the board and other UI components
   */
  void RenderGame() const;

  /**
   * Handles user inputs
   */
  void HandleInput(const ci::app::KeyEvent& event);

  /**
   * Updates Game State
   */
  void UpdateGameState();

  /**
   * Plays music at specified path
   * @param path to audio file
   */
  void PlayMusic(const std::string& file_path);
 private:
  /**
   * Renders player input options
   * @param inputs to be rendered
   */
  void RenderInputOptions(const std::vector<std::string>& inputs) const;

  /**
   * Renders All face plates
   */
  void RenderAllFacePlates() const;

  /**
   * Sets the color of the face plates
   * @param whether or not the player is allied
   */
  void SetAlliesFacePlateColor(bool is_player_allied) const;

  /**
   * Sets the color of the face plates
   * @param whether or not the player is allied
   */
  void SetEnemyFacePlateColor(bool is_player_allied) const;

  /**
   * Renders the main menu
   */
  void RenderMainMenu() const;

  /**
   * Renders board and UI elements
   */
  void RenderGameState() const;

  GameEngine game_engine_;
  const float kWindowSize;
  ci::audio::VoiceRef audio_player_;
};

} //namespace jjba_strategy

#endif //JJBA_STRATEGY_RPG_INCLUDE_GUI_RENDER_ENGINE_H_
