#include "MainMenu.h"

MainMenu::MainMenu(Data& data) : State(data)
{
}

MainMenu::~MainMenu() = default;

bool MainMenu::init()
{
  main_font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf");
  sun_font.loadFromFile("Data/Fonts/SunFlower.ttf");

 /// Init Title
  Functions::generate(
    game_title,
   "Natureza",
    sun_font,
    sf::Color::White,
    600,
    100,
    140);

  /// Init shadow
  Functions::generate(
    game_title_shadow,
    "Natureza",
    sun_font,
    sf::Color::White,
    610,
    110,
    140);

  game_title.setStyle(sf::Text::Bold);
  game_title_shadow.setStyle(sf::Text::Bold);
  game_title_shadow.setFillColor(sf::Color(0,0,0, 145));

  /// Menu options
  Functions::generate(play_text,
                      "Play",
                      main_font,
                      sf::Color::White,
                      830,
                      360,
                      60);


  Functions::generate(exit_text,
                      "Exit",
                      main_font,
                      sf::Color::White,
                      837,
                      500,
                      60);





  if (!background_texture.loadFromFile("Data/Images/MainMenuBG.jpg"))
  {
    std::cout << "background did not load" << std::endl;
  }
  if (!background_texture_blocks.loadFromFile("Data/Images/Platformer-MainMenu.png"))
  {
    std::cout << "background_blocks did not load" << std::endl;
  }
  if (!background_texture_deco.loadFromFile("Data/Images/Platformer-MainMenu-decoration.png"))
  {
    std::cout << "background_deco did not load" << std::endl;
  }

  /// Setting background textures
  background_blocks.setTexture(background_texture_blocks);
  background_deco.setTexture(background_texture_deco);
  background.setTexture(background_texture);

  /// BG Audio
  if (!bg_audio.openFromFile("Data/Audio/main_menu_song.ogg"))
  {
    std::cout << "bg_audio did not load" << std::endl;
  }
  bg_audio.setLoop(true);
  bg_audio.setVolume(35.f);

  if (!select_buffer.loadFromFile("Data/Audio/Effects/hover.wav"))
  {
    std::cout << "select_buffer did not load" << std::endl;
  }
  select_audio.setBuffer(select_buffer);
  select_audio.setVolume(50);

  if (!jump_buffer.loadFromFile("Data/Audio/Effects/jump.ogg"))
  {
    std::cout << "jump_buffer did not load" << std::endl;
  }
  jump_audio.setBuffer(jump_buffer);
  jump_audio.setVolume(10);


  /// Init fake player
  Functions::generate(player,
                      player_sheet,
                      "Data/Images/Blue_witch/all.png",
                      245,
                      270,
                      scale_value,
                      scale_value);

  current_frame = sf::IntRect(0, 0, 32, 48);
  player.setTextureRect(sf::IntRect(current_frame));

  anim_state = FakeState::fake_idle;

  clicked_play = false;
  clicked_exit = false;

  return State::init();
}
void MainMenu::update(float dt, GameStates& current_state, sf::Event& event)
{
  /// Animations
  if (anim_state == FakeState::fake_idle)
  {
    Functions::updateAnimation(player,
                               animation_clock,
                               0.15f,
                               0,
                               current_frame,
                               240,
                               48);
  }
  else if (anim_state == FakeState::fake_moving)
  {
    Functions::updateAnimation(player,
                               animation_clock,
                               0.15f,
                               1,
                               current_frame,
                               338,
                               48);
  }

  if (clicked_play)
  {
    if (delay.getElapsedTime().asSeconds() < 1.0f)
    {
      jump_audio.play();
    }
    player.move(3,0);
    anim_state = FakeState::fake_moving;
    float moveDown = (0.00095f * (player.getPosition().x * player.getPosition().x) / 100);
    if (delay.getElapsedTime().asSeconds() > 1.1)
    {
      player.move(0, (moveDown * 2.2f) * -3.2f);
    }
    if (delay.getElapsedTime().asSeconds() > 1.23f)
    {
      player.move(0, moveDown * 10.2f);
    }
  }
  if (clicked_play && delay.getElapsedTime().asSeconds() > 2.2f) // 2.2
  {
    resetState(current_state);
    current_state = GameStates::TUTORIAL;
  }

  /// Having the selected sound to play only once
  if (times_played > 0.9f){times_played = 1.0f;}
  if (times_played < 1.0f && times_played != 0 && !clicked_play)
  {
    select_audio.play();
  }

  if (Functions::insideText(event, exit_text) && !clicked_play)
  {
    times_played += 0.9f;
    inside_exit = true;
    exit_text.setCharacterSize(80);
    exit_text.setPosition(819, 486);
    exit_text.setFillColor(sf::Color(83, 113, 219, 255));
  }
  else
  {
    inside_exit = false;
    exit_text.setCharacterSize(60);
    exit_text.setPosition(837, 500);
    exit_text.setFillColor(sf::Color::White);
  }

  if (Functions::insideText(event, play_text)  || clicked_play)
  {
    times_played += 0.9f;
    inside_play = true;
    play_text.setCharacterSize(80);
    play_text.setPosition(813, 347);
    play_text.setFillColor(sf::Color(83, 113, 219, 255));
  }
  else
  {
    inside_play = false;
    play_text.setCharacterSize(60);
    play_text.setPosition(830, 360);
    play_text.setFillColor(sf::Color::White);
  }

  if (!Functions::insideText(event, exit_text) && !Functions::insideText(event, play_text))
  {
    times_played = 0;
  }



  State::update(dt, current_state, event);
}

void MainMenu::render(sf::Event event)
{
  data.window.draw(background);
  data.window.draw(background_deco);
  data.window.draw(background_blocks);
  data.window.draw(player);
  data.window.draw(game_title_shadow);
  data.window.draw(game_title);
  data.window.draw(play_text);
  data.window.draw(exit_text);
  State::render(event);
}
void MainMenu::mouseClicked(sf::Event event, GameStates& current_state)
{
  if (inside_play)
  {
    if (!clicked_play)
    {
      delay.restart();
    }
    clicked_play = true;
  }
  else if (inside_exit && !clicked_play)
  {
    data.window.close();
  }
  State::mouseClicked(event, current_state);
}
void MainMenu::keyPressed(sf::Event event, GameStates& current_state)
{
  State::keyPressed(event, current_state);
}

void MainMenu::resetState(GameStates& current_state)
{
  clicked_play = false;
  player.setPosition(sf::Vector2f(245, 270));
  anim_state = FakeState::fake_idle;
  State::resetState(current_state);
}

