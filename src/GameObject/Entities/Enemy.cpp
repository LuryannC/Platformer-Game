//
// Created by luria on 13/04/2022.
//

#include "Enemy.h"
Enemy::Enemy(Data& data, float pos_x, float pos_y) : GameObjects(data, pos_x, pos_y)
{
 x = pos_x;
 y = pos_y;
}

void Enemy::init()
{
  current_state = ENEMY_MOVING;
  Functions::generate(sprite,
                      textureSheet,
                      "Data/Images/enemies/mushroom.png",
                      x,
                      y,
                      scale_value,
                      scale_value);


  current_frame = sf::IntRect(0, 0, 32, 39);
  sprite.setTextureRect(sf::IntRect(current_frame));

  direction = Functions::randomize(-1, 1);
}
void Enemy::update(float dt)
{
  if (current_state == ENEMY_IDLE)
  {
    Functions::updateAnimation(sprite,
                               animation_clock,
                               0.3f,
                               ENEMY_IDLE,
                               current_frame,
                               117,
                               39);
  }
  else if (current_state == ENEMY_MOVING)
  {
    Functions::updateAnimation(sprite,
                               animation_clock,
                               0.2f,
                               ENEMY_MOVING,
                               current_frame,
                               273,
                               39);
  }
  else if (current_state == ENEMY_DAMAGE)
  {
    Functions::updateAnimation(sprite,
                               animation_clock,
                               0.2f,
                               4,
                               current_frame,
                               78,
                               39);
  }

}
void Enemy::render()
{
  data.window.draw(sprite);
}
sf::Sprite& Enemy::getSprite()
{
  return sprite;
}
int Enemy::getLives() const
{
  return lives;
}
void Enemy::setLives(int lives)
{
  Enemy::lives = lives;
}
