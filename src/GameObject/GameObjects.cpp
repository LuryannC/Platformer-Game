//
// Created by luria on 09/04/2022.
//

#include "GameObjects.h"
#include <iostream>
GameObjects::GameObjects(Data& data, float pos_x, float pos_y) : data(data)
{
  x = pos_y;
  y = pos_y;
  sprite = new sf::Sprite;
}
sf::Sprite* GameObjects::getSprite()
{
  return sprite;
}
bool GameObjects::initialiseSprite(sf::Texture& texture, std::string filename)
{
  if (!texture.loadFromFile(filename)){
    std::cout << "Failed to load: " + filename << std::endl;
    return false;
  }
  sprite->setTexture(texture);
  return true;
}
void GameObjects::init() {}
void GameObjects::update(float dt) {}
void GameObjects::render() {}

float GameObjects::getCenter() const
{
  float center = (sprite->getPosition().x + sprite->getGlobalBounds().width / 2) + (sprite->getPosition().y + sprite->getGlobalBounds().height / 2);
  return center;
}

bool GameObjects::isVisible() const
{
  return visibility;
}

bool GameObjects::isAlive() const
{
  return alive;
}

void GameObjects::setVisibility(bool visibility)
{
  GameObjects::visibility = visibility;
}

void GameObjects::setAlive(bool alive)
{
  GameObjects::alive = alive;
}
float GameObjects::getX() const
{
  return x;
}
float GameObjects::getY() const
{
  return y;
}
short GameObjects::getCurrentState() const
{
  return current_state;
}
void GameObjects::setCurrentState(short currentState)
{
  current_state = currentState;
}
