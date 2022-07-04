//
// Created by l2-augustocerv on 18/03/2022.
//

#ifndef PLATFORMERSFML_MAINMENU_H
#define PLATFORMERSFML_MAINMENU_H
#include "../GameObject/Player.h"
#include "../State.h"

enum FakeState
{
  fake_idle = 0,
  fake_moving,
};

class MainMenu : public State
{
 public:
  explicit MainMenu(Data& data);
  ~MainMenu() override;
  bool init() override;
  void update(float dt, GameStates& current_state, sf::Event& event) override;
  void render(sf::Event event) override;
  void mouseClicked(sf::Event event, GameStates& current_state) override;
  void keyPressed(sf::Event event, GameStates& current_state) override;
  void resetState(GameStates& current_state) override;

  /// Start game
  bool clicked_play = false;
  bool clicked_exit = false;

  /// Audio
  sf::Music bg_audio;
  sf::SoundBuffer select_buffer;
  sf::Sound select_audio;
 private:
  sf::Event event;

  /// audio cap
    float times_played = 1;
    bool play_now;
  /// Text
  sf::Text game_title;
  sf::Text game_title_shadow;

  sf::Sprite background;
  sf::Sprite background_blocks;
  sf::Sprite background_deco;
  sf::Texture background_texture;
  sf::Texture background_texture_blocks;
  sf::Texture background_texture_deco;

  /// Fonts
  sf::Font main_font;
  sf::Font sun_font;

  /// Menu options
  sf::Text play_text;
  sf::Text exit_text;
  bool inside_play;
  bool inside_exit;

  sf::Clock delay;

  /// fake Player
  sf::Sprite player;
  sf::Texture player_sheet;
  // Animations
  sf::Clock animation_clock;
  sf::IntRect current_frame;
  float scale_value = 2.4f;
  short anim_state{};
  sf::Sound jump_audio;
  sf::SoundBuffer jump_buffer;
};

#endif // PLATFORMERSFML_MAINMENU_H
