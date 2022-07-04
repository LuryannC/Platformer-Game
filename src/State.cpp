#include "State.h"


State::State(Data& data) : data(data) {}
bool State::init()
{
  return false;
}
void State::update(float dt, GameStates& current_state, sf::Event& event) {}
void State::render(sf::Event event) {}
void State::mouseClicked(sf::Event event, GameStates& current_state) {}
void State::keyPressed(sf::Event event, GameStates& current_state) {}
void State::resetState(GameStates& current_state) {}
