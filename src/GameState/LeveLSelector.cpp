#include "LeveLSelector.h"


LeveLSelector::LeveLSelector(Data& data) : State(data)
{

}
bool LeveLSelector::init()
{
  return State::init();
}
void LeveLSelector::update(float dt, GameStates& current_state, sf::Event& event)
{
  State::update(dt, current_state, event);
}
void LeveLSelector::render(sf::Event event)
{
  State::render(event);
}
void LeveLSelector::mouseClicked(sf::Event event, GameStates& current_state)
{
  State::mouseClicked(event, current_state);
}
void LeveLSelector::keyPressed(sf::Event event, GameStates& current_state)
{
  State::keyPressed(event, current_state);
}
void LeveLSelector::resetState(GameStates& current_state)
{
  State::resetState(current_state);
}

