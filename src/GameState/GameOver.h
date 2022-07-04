#ifndef PLATFORMERSFML_GAMEOVER_H
#define PLATFORMERSFML_GAMEOVER_H
#include "../State.h"
#include "../GameState/GamePlay.h"

class GameOver : public State
{
 public:
  explicit GameOver(Data& data, GamePlay& game_play);
  ~GameOver() override;
  bool init() override;
  void update(float dt, GameStates& current_state, sf::Event& event) override;
  void render(sf::Event event) override;
  void mouseClicked(sf::Event event, GameStates& current_state) override;
  void keyPressed(sf::Event event, GameStates& current_state) override;
  void resetState(GameStates& current_state) override;

 private:

  GamePlay&  game_play;

  /// Font
  sf::Font main_font;
  sf::Font sun_font;

  /// Audio cap
  sf::SoundBuffer select_buffer;
  sf::Sound select_audio;
  float times_played = 1;

  /// Text
  sf::Text game_title;
  sf::Text game_title_shadow;

  /// Menu options
  sf::Text play_text;
  sf::Text exit_text;
  bool clicked_play = false;
  bool inside_play;
  bool inside_exit;

  /// Background
  sf::Sprite background;
  sf::Texture background_texture;

  /// Score
  sf::Text score_text;

};

#endif // PLATFORMERSFML_GAMEOVER_H
