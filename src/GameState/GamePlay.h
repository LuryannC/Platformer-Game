//
// Created by luria on 15/04/2022.
//

#ifndef PLATFORMERSFML_GAMEPLAY_H
#define PLATFORMERSFML_GAMEPLAY_H
#include "../State.h"
#include "../Functions.h"
#include "../GameObject/Player.h"
#include "../GameObject/Maps.h"
#include "../GameObject/Entities/Enemy.h"
#include "../GameObject/GameObjects.h"

class GamePlay : public State
{
 public:
  explicit GamePlay(Data& data);
  ~GamePlay() override;
  bool init() override;
  void update(float dt, GameStates& current_state, sf::Event& event) override;
  void render(sf::Event event) override;
  void mouseClicked(sf::Event event, GameStates& current_state) override;
  void keyPressed(sf::Event event, GameStates& current_state) override;
  void resetState(GameStates& current_state) override;
  void shoot();
  void resetScore();
  int getScore() const;

  /// Public variables
  //Functions* functions;
  Player* player;
  Maps* maps;
  Enemy* enemy[3];
  GameObjects* collectibles[2];
  GameObjects* shoots;

  /// Audio
  sf::Music bg_music;
  // Hit audio
  sf::Sound hit_audio;
  sf::SoundBuffer hit_buffer;
  // Clink
  sf::Sound clink_audio;
  sf::SoundBuffer clink_buffer;

 private:

  /// Private Variables

  sf::Sprite decoration;
  sf::Texture decoration_texture;
  sf::Sprite bg;
  sf::Texture bg_image;

  sf::Vector2f animation_vector[2];
  sf::Event event;

  /// Score
  int score = 0;
  sf::Text score_text;
  sf::Font main_font;

  /// Shots
  sf::Texture shots_texture;
  float shoot_direction;
  sf::Clock shot_clock;
  sf::Clock damage_clock;
  float shot_speed = 180.f;
  bool has_shoot   = false;

  /// Clock
  sf::Clock damage_timer;
  sf::Clock collectibles_clock[2];

  /// Camera
  sf::View fixed_camera;
  sf::View follow_camera;

  sf::Vector2f direction[4];

  /// Enemies settings
  int n_enemies = 3;

  int lives;
  int health_size = 180;
  sf::RectangleShape health_frame;
  sf::RectangleShape health_bar;

  sf::Sprite heart;
  sf::Texture heart_texture;

  /// Potions
  sf::Texture collectibles_texture;
  bool collected = false;
  int potions_collected = 0;

  /// Magic walls
  sf::RectangleShape magic_wall[2][7];
  sf::RectangleShape magic_wall_col[2];

  /// 0 gravity rectangle
  sf::RectangleShape zg_rect;
  bool zero_gravity_on = false;

  /// Potion Hud
  sf::Sprite tiny_potions[2];
  sf::Texture tiny_potion_texture;
};

#endif // PLATFORMERSFML_GAMEPLAY_H
