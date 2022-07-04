
#include "Game.h"
#include <iostream>


Game::Game(Data& data) : data(data)
{
  srand(time(NULL));
  menu = new MainMenu(data);
  level_selector = new LeveLSelector(data);
  functions = new Functions();
  game_play = new GamePlay(data);
  game_over = new GameOver(data, *game_play);
  game_win = new GameWin(data, *game_play);
  tutorial = new Tutorial(data);
 
}

Game::~Game()
{
  delete menu;
  delete level_selector;
  delete functions;
  delete game_play;
  delete game_over;
  delete game_win;
  delete tutorial;
}

bool Game::init()
{
  current_state = GameStates::MAIN_MENU;
  /// BG Audio
  if (!bg_audio.openFromFile("Data/Audio/main_menu_song.ogg"))
  {
    std::cout << "bg_audio did not load" << std::endl;
  }
  bg_audio.setLoop(true);
  bg_audio.setVolume(25.f);

  /// Audio
  if (!bg_music.openFromFile("Data/Audio/bg_music.ogg"))
  {
    std::cout << "bg_music did not load" << std::endl;
  }
  bg_music.setLoop(true);
  bg_music.setVolume(15.f);
  bg_music.play();

  menu->init();
  game_play->init();
  game_over->init();
  game_win->init();
  tutorial->init();

  return true;
}

void Game::update(float dt, sf::Event event)
{
  new_state = false;

  switch (current_state)
  {
    case GameStates::MAIN_MENU:
      state = menu;
      game_play->resetScore();
      break;
    case GameStates::LEVEL_SELECTOR:
      state = level_selector;
      break;
    case GameStates::IN_GAME:
      state = game_play;
      break;
    case GameStates::GAME_OVER:
      state = game_over;
      break;
    case GameStates::GAME_WIN:
      state = game_win;
      break;
    case GameStates::TUTORIAL:
      state = tutorial;
      break;
  }
  state->update(dt, current_state, event);

}

void Game::render(sf::Event event) const
{
  state->render(event);
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(data.window);
  state->mouseClicked(event, current_state);
}

void Game::keyPressed(sf::Event event)
{
  if (event.key.code == sf::Keyboard::Escape)
  {
    state->resetState(current_state);
    current_state = GameStates::MAIN_MENU;
  }
  state->keyPressed(event, current_state);
}

