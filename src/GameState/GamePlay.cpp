#include "GamePlay.h"
#include <iostream>

GamePlay::GamePlay(Data& data) : State(data)
{
  player = new Player(data);
  maps = new Maps(data);
  collectibles[0] = new GameObjects(data, 0, 0);
  collectibles[1] = new GameObjects(data, 0, 0);
  shoots = new GameObjects(data, 0, 0);
  enemy[0] = new Enemy(data, 625, 246);
  enemy[1] = new Enemy(data, 424, 469);
  enemy[2] = new Enemy(data, 1545, 340);
  for (auto & i : direction)
  {
    i = {1,0};
  }
  for (auto & i : animation_vector)
  {
    i = {1,1};
  }
}

GamePlay::~GamePlay()
{
  delete player;
  delete maps;
  delete enemy[0];
  delete enemy[1];
  delete enemy[2];

}

bool GamePlay::init()
{
  /// Audio
  if (!bg_music.openFromFile("Data/Audio/bg_music.ogg"))
  {
    std::cout << "bg_music did not load" << std::endl;
  }
  bg_music.setLoop(true);
  bg_music.setVolume(35.f);

  if (!hit_buffer.loadFromFile("Data/Audio/Effects/hit.wav"))
  {
    std::cout << "hit_buffer did not load" << std::endl;
  }
  hit_audio.setBuffer(hit_buffer);
  hit_audio.setVolume(20);

  if (!clink_buffer.loadFromFile("Data/Audio/Effects/clink.wav"))
  {
    std::cout << "clink_buffer did not load" << std::endl;
  }
  clink_audio.setBuffer(clink_buffer);
  clink_audio.setVolume(10);

  lives = 3;

  Functions::generate(*collectibles[0]->getSprite(), collectibles_texture, "Data/Images/66.png", 236, 60, 0.08, 0.08);
  Functions::generate(*collectibles[1]->getSprite(), collectibles_texture, "Data/Images/66.png", 1535, 370, 0.08, 0.08);

  /// Zero Gravity rectangle
  zg_rect.setSize(sf::Vector2f (90, 228));
  zg_rect.setPosition(63, 20);


  /// Magic wall
  magic_wall[0][0].setSize(sf::Vector2f(280, 20));
  magic_wall[0][0].setPosition(sf::Vector2f(1300, 245));

  magic_wall[1][0].setSize(sf::Vector2f(20, 263));
  magic_wall[1][0].setPosition(sf::Vector2f(1973, 220));

  for(auto & wall : magic_wall_col)
  {
    wall.setFillColor(sf::Color::White);
  }

  magic_wall_col[0].setPosition(sf::Vector2f(1300, 262));
  magic_wall_col[0].setSize(sf::Vector2f(280, 40));

  magic_wall_col[1].setPosition(sf::Vector2f(1973, 220));
  magic_wall_col[1].setSize(sf::Vector2f(40, 263));


  for (auto & i : magic_wall)
  {
    for (auto & walls : i)
    {
      i[0].setFillColor(sf::Color(148, 0, 211, 100));
      i[1].setFillColor(sf::Color(75, 0, 130, 100));
      i[2].setFillColor(sf::Color(0, 0, 255, 100));
      i[3].setFillColor(sf::Color(0, 255, 0, 100));
      i[4].setFillColor(sf::Color(255, 255, 0, 100));
      i[5].setFillColor(sf::Color(255, 127, 0, 100));
      i[6].setFillColor(sf::Color(255, 0, 0, 100));
    }
  }

  for (int i = 1; i < 7; ++i)
  {
    magic_wall[0][i].setSize(sf::Vector2f(280, 20));
    magic_wall[0][i].setPosition(sf::Vector2f(1300, magic_wall[0][0].getPosition().y + i * 5));
    magic_wall[1][i].setSize(sf::Vector2f(20, 268));
    magic_wall[1][i].setPosition(sf::Vector2f(magic_wall[1][0].getPosition().x + i * 5, 220));
  }


  /// Health bar & Frame

  health_frame.setSize(sf::Vector2f(180, 40));
  health_frame.setPosition(sf::Vector2f(data.window.getSize().x - health_frame.getGlobalBounds().width - 20.f, 20));
  health_frame.setOutlineThickness(5);
  health_frame.setOutlineColor(sf::Color::White);
  health_frame.setFillColor(sf::Color(255,255,255,0));

  health_bar.setSize(sf::Vector2f(health_size, 40));
  health_bar.setPosition(sf::Vector2f(data.window.getSize().x - health_bar.getGlobalBounds().width - 20.f, 20));
  health_bar.setFillColor(sf::Color::Green);

  Functions::generate(heart, heart_texture, "Data/Images/heart.png", health_frame.getPosition().x - heart.getGlobalBounds().width - 34.f, 14, 0.36f, 0.36f);

  /// Cameras
  follow_camera.setSize(data.window.getSize().x, data.window.getSize().y);
  follow_camera.setCenter(sf::Vector2f(data.window.getSize().x / 2, data.window.getSize().y / 2));
  fixed_camera.setSize(data.window.getSize().x, data.window.getSize().y);
  fixed_camera.setCenter(data.window.getSize().x / 2, data.window.getSize().y / 2);

  /// Init other files
  maps->init();
  player->init();


  for (int i = 0; i < n_enemies; ++i)
  {
    enemy[i]->init();
  }

  if (!decoration_texture.loadFromFile("Data/Images/Platformer_decoratives.png"))
  {
    std::cout << "Background didn't load \n";
  }
  if (!bg_image.loadFromFile("Data/Images/bg.png"))
  {
    std::cout << "Background didn't load \n";
  }
  decoration.setTexture(decoration_texture);
  bg.setTexture(bg_image);



  /// Init shots (0% alcohol)
    shoots->initialiseSprite(shots_texture, "Data/Images/laserRed.png");
    shoots->setVisibility(false);

  /// Initialise score
    main_font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf");
    Functions::generate(score_text,
                        "Score: " + std::to_string(score),
                        main_font,
                        sf::Color::White,
                        0,
                        0,
                        40);
    score_text.setPosition(sf::Vector2f(data.window.getSize().x - health_frame.getGlobalBounds().width - 20.f, 60));


  /// Tiny potion
    for (auto & potion : tiny_potions)
    {
      Functions::generate(potion,
                          collectibles_texture,
                          "Data/Images/66.png",
                          0,
                          0,
                          0.08f,
                          0.08f);
    }
    tiny_potions[0].setPosition(sf::Vector2f(1200, 120));
    tiny_potions[1].setPosition(sf::Vector2f(tiny_potions[0].getPosition().x - tiny_potions[0].getGlobalBounds().width - 5.f, 120));

  return State::init();
}
void GamePlay::update(float dt, GameStates& current_state, sf::Event& event)
{
  Functions::cameraSystem(follow_camera,data, dt, player->getSprite());
  player->update(dt);

  /// Walls Collision
  if(Functions::wallsCollision(player->getSprite(), 2208.f, 28.f))
  {
    float get_direction = 1 * ((player->getSprite().getPosition().x < 0.0f) ? 1.0f : -1.0f);
    player->getSprite().move(get_direction * 260 * dt, 0);
  }

  /// Potions animation
  Functions::collectiblesAnim(*collectibles[0]->getSprite(), collectibles_clock[0], 1.2f, collectibles[0]->velocity, dt);
  Functions::collectiblesAnim(*collectibles[1]->getSprite(), collectibles_clock[1], 1.2f, collectibles[1]->velocity, dt);

  for (auto & collectible: collectibles)
  {
    if (Functions::collisionCheck(player->getSprite(), *collectible->getSprite(), 28.f, 20.f))
    {
      if (collectible->isVisible())
      {
        clink_audio.play();
        potions_collected+=1;
        score += 50;
        score_text.setString("Score: " + std::to_string(score));
      }
      collectible->setVisibility(false);
    }
  }

  /// Updating enemies and setting their movements in the platform
  for (int i = 0; i < n_enemies; ++i)
  {
    enemy[i]->update(dt);
  }
  Functions::moveEnemy(enemy[1]->getSprite(), maps->rectangle[1], dt, 24.0f, direction[0], enemy[1]->enemy_speed);
  Functions::moveEnemy(enemy[0]->getSprite(), maps->rectangle[5], dt, 24.0f, direction[1], enemy[0]->enemy_speed);
  Functions::moveEnemy(enemy[2]->getSprite(), maps->rectangle[12], dt, 24.0f, direction[2], enemy[2]->enemy_speed);

  
  /// Collision with enemies
  int damage_check = 0;
  for (int i = 0; i < n_enemies; i++)
  {
    if (Functions::enemyCollision(enemy[i]->getSprite(), player->getSprite(), 38.0f / 2.4, 42.f / 2.4) && enemy[i]->isVisible())
    {
      damage_check++;
      hit_audio.play();
      player->setAnimState(PlayerAnimState::damage);
    }
  }
  if (damage_check >= 1)
  {
    if (damage_timer.getElapsedTime().asSeconds() > 1.2f)
    {
      lives -=1;
      damage_timer.restart();
      health_size -= 60;
      if (health_size < 0){health_size = 0;}
      health_bar.setSize(sf::Vector2f(health_size, 40));
    }
  }

  /// Magic wall collision
  if (potions_collected > 0)
  {
    if (Functions::platformCollision(player->getSprite(), magic_wall_col[0], 28.f))
    {
      player->setGravity(0);
      Functions::resetVectorY(player->velocity);
    }
  }
  if (potions_collected < 2)
  {
    if (Functions::collisionCheck(player->getSprite(), magic_wall_col[1], 28.f, 0))
    {
      float get_direction = 1 * ((player->getSprite().getPosition().x < 0.0f) ? 1.0f : -1.0f);
      player->getSprite().move(get_direction * 260 * dt, 0);
    }
  }


  /// "Ladders"
  if (Functions::collisionCheck(player->getSprite(), zg_rect, 28.f, 0))
  {
    zero_gravity_on = true;
    player->setGravity(0);
    player->setOnGround(false);
    Functions::resetVectorY(player->velocity);
  }
  else
  {
    zero_gravity_on = false;
  }
  /// Can go up
  if (zero_gravity_on)
  {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) /// Top
    {
      player->getSprite().move(0, -145.f * dt);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && player->getSprite().getPosition().y <= 239.f)
    {
      player->getSprite().move(0, 145.f * dt);
    }
  }

  /// Shoot
  if (shot_clock.getElapsedTime().asSeconds() > 1.1f)
  {
      shoots->setVisibility(false);
      has_shoot = false;
  }
    if (shoots->isVisible())
    {
      if (shoot_direction < 0)
      {
        shoots->getSprite()->setOrigin(0,0);
        shoots->getSprite()->setScale(-1,1);
      }
      else
      {
        shoots->getSprite()->setOrigin(shoots->getSprite()->getGlobalBounds().width,0);
        shoots->getSprite()->setScale(1,1);
      }
      shoots->getSprite()->move(shot_speed * shoot_direction * dt, 0);
    }

    for (auto & enemies : enemy)
    {
      if (shoots->isVisible() && Functions::collisionCheck(*shoots->getSprite(), enemies->getSprite(), 0, 50.f))
      {
        enemies->setCurrentState(ENEMY_DAMAGE);
        shoots->setVisibility(false);
        enemies->lives -= 1;
        damage_clock.restart();
        if (enemies->getLives() < 0)
        {
          enemies->setVisibility(false);
          score += 200;
          score_text.setString("Score: " + std::to_string(score));
        }
      }
      if (damage_clock.getElapsedTime().asSeconds() > 0.6f)
      {
        enemies->setCurrentState(ENEMY_MOVING);
      }
    }


  /// Call game win
    if (potions_collected == 2 &&
        player->getSprite().getPosition().x >= 2095 &&
        player->getSprite().getPosition().y >= 330)
    {
      resetState(current_state);
      current_state = GameStates::GAME_WIN;
    }

  /// Call game over
  if (Functions::windowBottom(player->getSprite(), data.window.getSize().y, 10.f) || lives <= 0)
  {
    resetState(current_state);
    current_state = GameStates::GAME_OVER;
  }

  State::update(dt, current_state, event);
}
void GamePlay::render(sf::Event event)
{
  data.window.setView(follow_camera);
  data.window.draw(bg);
  data.window.draw(decoration);
  maps->render();



  for (int i = 0; i < n_enemies; ++i)
  {
    if (enemy[i]->isVisible())
    {
      enemy[i]->render();
    }
  }
  for (auto & collectible: collectibles)
  {
    if (collectible->isVisible())
    {
      data.window.draw(*collectible->getSprite());
    }
  }
  player->render();
  for (auto & i : magic_wall)
  {
    for (auto & walls : i)
    {
      data.window.draw(walls);
    }
  }
  if (shoots->isVisible())
    {
      data.window.draw(*shoots->getSprite());
    }
  data.window.setView(fixed_camera);
  data.window.draw(health_bar);
  data.window.draw(health_frame);
  data.window.draw(heart);
  data.window.draw(score_text);
  if (potions_collected > 0)
  {
    data.window.draw(tiny_potions[0]);
  }
  if (potions_collected == 2)
  {
    data.window.draw(tiny_potions[1]);
  }

  State::render(event);
}

void GamePlay::mouseClicked(sf::Event event, GameStates& current_state)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(data.window);
  State::mouseClicked(event, current_state);
}

void GamePlay::keyPressed(sf::Event event, GameStates& current_state)
{
  if (event.key.code == sf::Keyboard::E && !has_shoot)
  {
    shoot();
    shoot_direction = 1.0f;
    has_shoot = true;
  }
  if (event.key.code == sf::Keyboard::Q && !has_shoot)
  {
    shoot();
    shoots->getSprite()->setPosition(player->getSprite().getPosition().x + 30.f, player->getSprite().getPosition().y + 65.f);
    shoot_direction = -1.0f;
    has_shoot = true;
  }

  if (event.key.code == sf::Keyboard::Escape)
  {
    resetState(current_state);
    current_state = GameStates::MAIN_MENU;
  }

//  /// DEV reset player
//  if (event.key.code == sf::Keyboard::R)
//  {
//    resetScore();
//    resetState(current_state);
//  }
  State::keyPressed(event, current_state);
}

void GamePlay::resetState(GameStates& current_state)
{
  lives = 3;
  health_size = 180;
  health_bar.setSize(sf::Vector2f(float(health_size), 40));
  for (auto & potion : collectibles)
  {
    potion->setVisibility(true);
  }
  shoots->setVisibility(false);
  has_shoot   = false;
  n_enemies = 3;
  collected = false;
  potions_collected = 0;
  for (auto & enemies : enemy)
  {
    enemies->setLives(3);
    enemies->setVisibility(true);
  }
  player->getSprite().setPosition(0, 540);
  follow_camera.setCenter(sf::Vector2f(data.window.getSize().x / 2, data.window.getSize().y / 2));
  State::resetState(current_state);
}

void GamePlay::shoot()
{
  if (!has_shoot)
  {
    shoots->setVisibility(true);
    shoots->getSprite()->setPosition(player->getSprite().getPosition().x + 65.f, player->getSprite().getPosition().y + 65.f);
    shot_clock.restart();
  }
}
void GamePlay::resetScore()
{
  score = 0;
  score_text.setString("Score: " + std::to_string(score));
}
int GamePlay::getScore() const
{
  return score;
}
