#ifndef PLATFORMERSFML_LEVELSELECTOR_H
#define PLATFORMERSFML_LEVELSELECTOR_H

#include "../State.h"

class LeveLSelector : public State
{
 public:
  explicit LeveLSelector(Data& data);
  ~LeveLSelector() override = default;
  bool init() override;
  void update(float dt, GameStates& current_state, sf::Event& event) override;
  void render(sf::Event event) override;
  void mouseClicked(sf::Event event, GameStates& current_state) override;
  void keyPressed(sf::Event event, GameStates& current_state) override;
  void resetState(GameStates& current_state) override;
};

#endif // PLATFORMERSFML_LEVELSELECTOR_H
