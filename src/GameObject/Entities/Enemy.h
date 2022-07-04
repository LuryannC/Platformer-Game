//
// Created by luria on 13/04/2022.
//

#ifndef PLATFORMERSFML_ENEMY_H
#define PLATFORMERSFML_ENEMY_H
#include "../GameObjects.h"
#include "../Maps.h"

class Enemy : public GameObjects
{
 public:
  explicit Enemy(Data& data, float pos_x, float pos_y);

  void init() override;
  void update(float dt) override;
  void render() override;
  sf::Sprite& getSprite();
  int getLives() const;
  void setLives(int lives);


  float enemy_speed = 50.0f;

  /// Lives
  int lives = 3;

 private:
  sf::Texture textureSheet;
  sf::Sprite sprite;

  sf::Clock animation_clock;
  sf::IntRect current_frame;




 private:
  /// Movement
  short anim_state{};

  float scale_value = 2.4;

  //Data& data;
  float x;
  float y;

  Maps* maps;
  int direction;
};

#endif // PLATFORMERSFML_ENEMY_H
