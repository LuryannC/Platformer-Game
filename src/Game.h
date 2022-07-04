#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H


#include "GameState/MainMenu.h"
#include <vector>
#include "Functions.h"
#include "GameState/GamePlay.h"
#include "GameState/LeveLSelector.h"
#include "GameState/GameOver.h"
#include "GameState/GameWin.h"
#include "GameState/Tutorial.h"
#include "StateEnum.h"
#include <SFML/Audio.hpp>


class Game
{
 public:
  explicit Game(Data& data);
  ~Game();
  bool init();
  void update(float dt, sf::Event event);
  void render(sf::Event event) const;
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);

  /// Classes
  MainMenu* menu;
  LeveLSelector* level_selector;
  GamePlay* game_play;
  GameOver* game_over;
  GameWin* game_win;
  Functions* functions;
  Tutorial* tutorial;
  State* state;


  /// Enums


  /// Public Variables
  GameStates current_state;


 private:
  Data& data;

  sf::Music bg_audio;
  sf::Music bg_music;

  int playing_music = 0;
  bool song_started;
  bool new_state = true;

};

#endif // PLATFORMER_GAME_H
