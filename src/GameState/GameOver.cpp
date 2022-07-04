#include "GameOver.h"

GameOver::GameOver(Data& data, GamePlay& game_play) : State(data), game_play(game_play)
{
}

GameOver::~GameOver() = default;

bool GameOver::init()
{
  /// Background
  if (!background_texture.loadFromFile("Data/Images/game_over_bg2.jpg"))
  {
    std::cout << "background did not load" << std::endl;
  }
  background.setTexture(background_texture);
  background.setScale(1.4, 1.4);
  background.setPosition(0, -300.f);

  /// Font
  sun_font.loadFromFile("Data/Fonts/SunFlower.ttf");
  main_font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf");


  /// Init GameOver
  Functions::generate(
    game_title,
    "Game Over",
    sun_font,
    sf::Color::White,
    300,
    30,
    170);

  /// Init shadow
  Functions::generate(
    game_title_shadow,
    "Game Over",
    sun_font,
    sf::Color::White,
    310,
    40,
    170);

  game_title.setStyle(sf::Text::Bold);
  game_title_shadow.setStyle(sf::Text::Bold);
  game_title_shadow.setFillColor(sf::Color(0,0,0, 145));

  /// Audio
  if (!select_buffer.loadFromFile("Data/Audio/Effects/hover.wav"))
  {
    std::cout << "select_buffer did not load" << std::endl;
  }
  select_audio.setBuffer(select_buffer);
  select_audio.setVolume(50);

  /// Menu options
  Functions::generate(play_text,
                      "Play Again",
                      main_font,
                      sf::Color::White,
                      100,
                      360,
                      60);


  Functions::generate(exit_text,
                      "Exit",
                      main_font,
                      sf::Color::White,
                      107,
                      500,
                      60);

  /// Score
  Functions::generate(score_text,
                      "Score: " + std::to_string(game_play.getScore()),
                      main_font,
                      sf::Color::White,
                      730,
                      360,
                      80);

  return State::init();
}
void GameOver::update(float dt, GameStates& current_state, sf::Event& event){

  score_text.setString("Score: " + std::to_string(game_play.getScore()));
  if (times_played > 0.9f){times_played = 1.0f;}
  if (times_played < 1.0f && times_played != 0)
  {
    select_audio.play();
  }
  if (Functions::insideText(event, exit_text))
  {
    times_played += 0.9f;
    inside_exit = true;
    exit_text.setCharacterSize(80);
    exit_text.setPosition(98, 490);
    exit_text.setFillColor(sf::Color(83, 113, 219, 255));
  }
  else
  {
    inside_exit = false;
    exit_text.setCharacterSize(60);
    exit_text.setPosition(107, 500);
    exit_text.setFillColor(sf::Color::White);
  }

  if (Functions::insideText(event, play_text))
  {
    times_played += 0.9f;
    inside_play = true;
    play_text.setCharacterSize(80);
    play_text.setPosition(98, 350);
    play_text.setFillColor(sf::Color(83, 113, 219, 255));
  }
  else
  {
    inside_play = false;
    play_text.setCharacterSize(60);
    play_text.setPosition(107, 360);
    play_text.setFillColor(sf::Color::White);
  }
  if (!Functions::insideText(event, exit_text) && !Functions::insideText(event, play_text))
  {
    times_played = 0;
  }
  State::update(dt, current_state, event);
}
void GameOver::render(sf::Event event)
{
  data.window.draw(background);
  data.window.draw(game_title_shadow);
  data.window.draw(game_title);
  data.window.draw(play_text);
  data.window.draw(exit_text);
  data.window.draw(score_text);
  State::render(event);
}
void GameOver::mouseClicked(sf::Event event, GameStates& current_state)
{
  if (inside_play)
  {
    current_state = GameStates::MAIN_MENU;
  }
  else if (inside_exit)
  {
    data.window.close();
  }
  State::mouseClicked(event, current_state);
}
void GameOver::keyPressed(sf::Event event, GameStates& current_state)
{
  State::keyPressed(event, current_state);
}
void GameOver::resetState(GameStates& current_state)
{
  State::resetState(current_state);
}

