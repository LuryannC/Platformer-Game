//
// Created by luria on 26/04/2022.
//

#ifndef PLATFORMERSFML_TUTORIAL_H
#define PLATFORMERSFML_TUTORIAL_H
#include "../State.h"

class Tutorial : public State
{
 public:
  explicit Tutorial(Data& data);
  bool init() override;
  void render(sf::Event event) override;
  void keyPressed(sf::Event event, GameStates& current_state) override;

 private:
  sf::Texture tutorial_texture;
  sf::Sprite tutorial_sprite;
};

#endif // PLATFORMERSFML_TUTORIAL_H
