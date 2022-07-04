//
// Created by l2-augustocerv on 18/03/2022.
//

#ifndef PLATFORMERSFML_STATE_H
#define PLATFORMERSFML_STATE_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Functions.h"
#include <iostream>


class State
{
 public:
  explicit State(Data& data);
  virtual ~State()                           = default;
  virtual bool init()                        ;
  virtual void update(float dt, GameStates& current_state, sf::Event& event)              ;
  virtual void render(sf::Event event)                      ;
  virtual void mouseClicked(sf::Event event, GameStates& current_state) ;
  virtual void keyPressed(sf::Event event, GameStates& current_state)   ;
  virtual void resetState(GameStates& current_state);


 protected:
  Data& data;
};

#endif // PLATFORMERSFML_STATE_H
