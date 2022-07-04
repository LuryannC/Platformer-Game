#include "Tutorial.h"
Tutorial::Tutorial(Data& data) : State(data) {}

bool Tutorial::init()
{
  if (!tutorial_texture.loadFromFile("Data/Images/Platformer-Instructions.png"))
  {
    std::cout << "TUTORIAL failed to load" << std::endl;
  }
  tutorial_sprite.setTexture(tutorial_texture);
  return State::init();
}
void Tutorial::render(sf::Event event)
{
  data.window.draw(tutorial_sprite);
  State::render(event);
}
void Tutorial::keyPressed(sf::Event event, GameStates& current_state)
{
  if (event.key.code == sf::Keyboard::Enter && current_state == GameStates::TUTORIAL)
  {
    current_state = GameStates::IN_GAME;
  }
  State::keyPressed(event, current_state);
}

