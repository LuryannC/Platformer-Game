//
// Created by luria on 18/03/2022.
//

#ifndef PLATFORMERSFML_PLAYER_H
#define PLATFORMERSFML_PLAYER_H
#include <SFML/Audio.hpp>
#include "../Functions.h"
#include "../GameObject/Maps.h"


enum PlayerAnimState
{
  idle = 0,
  moving_left,
  moving_right,
  jump,
  fall,
  charging,
  attack,
  damage,
};

class Player
{
 public:
  explicit Player(Data& data);
  ~Player();
  void init();
  void update(float dt);
  void render();
  void movePlayer(float dt);
  void move(float x, float y, float dt, float max_velocity, float min_velocity, float acceleration, float deceleration);
  void jump(float dt);
  sf::Sprite& getSprite();

  bool on_ground;
  void setOnGround(bool onGround);
  float jump_height = 20.0;

  sf::Vector2f velocity; /// Create a vector class later (provisional)


 private:
  Data& data;
  sf::Sprite sprite;
  bool can_control = true;
 public:
  sf::Sound jump_audio;
  sf::SoundBuffer jump_buffer;

 private:
  sf::Texture textureSheet;

  Maps *maps;


  int sheet_value{};

  /// Physics
  float player_speed = 120.;

    float gravity;

 public:
  void setGravity(float gravity);

 private:
  float gravity_y = 505.f;


  /// Animations
  sf::Clock animation_clock;
  sf::IntRect current_frame;

  /// Movement
  short anim_state{};

 public:
  void setAnimState(short animState);

 private:
  sf::Clock air_timer;


  /// Core
  float scale_value = 2.4;
  float height_fix = 20;



};

#endif // PLATFORMERSFML_PLAYER_H
