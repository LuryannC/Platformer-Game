#include "Player.h"
#include <cmath>
#include <iostream>

Player::Player(Data& data) : data(data)
{
  maps = new Maps(data);
}

Player::~Player()
= default;

void Player::init()
{
  /// Sounds
  if (!jump_buffer.loadFromFile("Data/Audio/Effects/jump.ogg"))
  {
    std::cout << "jump_buffer did not load" << std::endl;
  }
  jump_audio.setBuffer(jump_buffer);
  jump_audio.setVolume(10);


  anim_state = idle;

  Functions::generate(sprite,
                      textureSheet,
                      "Data/Images/Blue_witch/all.png",
                      0,
                      540,
                      scale_value,
                      scale_value);

  current_frame = sf::IntRect(0, 0, 32, 48);
  sprite.setTextureRect(sf::IntRect(current_frame));


}
void Player::update(float dt)
{
  /// Animations
  if (anim_state == PlayerAnimState::idle)
  {
    Functions::updateAnimation(sprite,
                               animation_clock,
                               0.15f,
                               0,
                               current_frame,
                               240,
                               48);
  }
  else if (anim_state == PlayerAnimState::moving_right || anim_state == PlayerAnimState::moving_left)
  {
    Functions::updateAnimation(sprite,
                               animation_clock,
                               0.15f,
                               1,
                               current_frame,
                               338,
                               48);

  }
  else if (anim_state == PlayerAnimState::charging)
  {
    Functions::updateAnimation(sprite,
                               animation_clock,
                               0.15f,
                               5,
                               current_frame,
                               96,
                               48);
  }
  else if (anim_state == PlayerAnimState::damage)
  {
    Functions::updateAnimation(sprite,
                               animation_clock,
                               0.18f,
                               4,
                               current_frame,
                               96,
                               48);
  }

  /// Gravity

    velocity.y += 1.f * gravity;
    if ((velocity.y) > gravity_y)
    {
      velocity.y = gravity_y * ((velocity.y < 0.f) ? -1.f : 1.f);
    }


  movePlayer(dt);
  int collision_count = 0;
  for (auto & i : maps->rectangle)
  {
    if (Functions::platformCollision(sprite, i, 28.f))
    {
      on_ground = true;
      gravity = 0.f;
      Functions::resetVectorY(velocity);
    }
    else
    {
      collision_count++;
    }
  }
  if (collision_count == 17)
  {
    gravity += 88.f * dt;
  }
}

void Player::movePlayer(float dt)
{

  anim_state = PlayerAnimState::idle;
  move(0,0,dt,145.f,1.f,3.f, .93f);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) /// Left
  {
    move(-120, 0, dt, 145.f, 1.f, 3.f, .93f);
    sprite.setScale(-scale_value, scale_value);
    sprite.setOrigin(sprite.getGlobalBounds().width / scale_value, 0);
    anim_state = PlayerAnimState::moving_left;
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) /// Right
  {
    //move(1, 0);
    move(120, 0, dt, 145.f, 1.f, 3.f, .93f);
    sprite.setScale(scale_value, scale_value);
    sprite.setOrigin(0, 0);
    anim_state = PlayerAnimState::moving_right;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && on_ground) /// Charging
  {
    jump_audio.play();
    jump(dt);
    sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - 4);
    on_ground = false;
  }
//  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I)){
//    sprite.move(0, -10.f);
//  }
//  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)) /// It can go through platforms !!!!!!!!11 IMPORTANT
//  {
//    sprite.move(0, 5.f);
//  }
}


void Player::move(float x, float y, float dt, float max_velocity, float min_velocity, float acceleration, float deceleration)
{

  velocity.x *= deceleration;
  if (std::abs(velocity.x) < min_velocity)
  {
    velocity.x = 0.f;
  }
  sprite.move(velocity * dt);

  velocity.x += x * acceleration;

   if (std::abs(velocity.x) > max_velocity)
    {
      velocity.x = max_velocity * ((velocity.x < 0.f) ? -1.f : 1.f);
    }
}

void Player::jump(float dt)
{
  velocity.y = -295.f;
}

void Player::render()
{
  data.window.draw(sprite);
}

sf::Sprite& Player::getSprite()
{
  return sprite;
}
void Player::setAnimState(short animState)
{
  anim_state = animState;
}
void Player::setGravity(float gravity)
{
  Player::gravity = gravity;
}
void Player::setOnGround(bool onGround)
{
  on_ground = onGround;
}

