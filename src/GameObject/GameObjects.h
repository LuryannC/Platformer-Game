//
// Created by luria on 09/04/2022.
//

#ifndef PLATFORMERSFML_GAMEOBJECTS_H
#define PLATFORMERSFML_GAMEOBJECTS_H

#include <SFML/Graphics.hpp>
#include "../Functions.h"

enum GoAnimState
{
  ENEMY_IDLE,
  ENEMY_MOVING,
  ENEMY_ATTACK,
  ENEMY_DAMAGE,
};

class GameObjects
{
 public:
  explicit GameObjects(Data& data, float pos_x, float pos_y);
  virtual ~GameObjects()                           = default;
  virtual void init();
  bool initialiseSprite(sf::Texture &texture, std::string filename);
  virtual void update(float dt)              ;
  virtual void render()                      ;
  sf::Sprite* getSprite();
  float getCenter() const;
  bool isVisible() const;
  bool isAlive() const;
  void setVisibility(bool visibility);
  void setAlive(bool alive);
  short getCurrentState() const;
  void setCurrentState(short currentState);

  sf::Vector2f velocity = {1,1};



 private:
  bool visibility = true;
  bool alive = true;

  float x;
  float y;

 public:
  float getX() const;
  float getY() const;

 protected:
  sf::Sprite* sprite = nullptr;
  short current_state{};

  Data& data;
};

#endif // PLATFORMERSFML_GAMEOBJECTS_H
