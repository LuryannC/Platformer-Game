#ifndef PLATFORMERSFML_FUNCTIONS_H
#define PLATFORMERSFML_FUNCTIONS_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "StateEnum.h"

struct Data
{
  sf::RenderWindow& window;
};

class Functions
{
 public:


  static void generate(sf::Text& variable_name, const std::string& string, sf::Font& font, const sf::Color& colour, float pos_x, float pos_y, int character_size);
  static void generate(sf::Sprite& sprite, sf::Texture& texture, const std::string& filename, float pos_x, float pos_y, float scale_x, float scale_y);
  static bool collisionCheck(sf::Sprite& object_1, sf::Sprite& object_2, float player_offset, float item_offset);
  static bool collisionCheck(sf::Sprite& object_1, sf::RectangleShape& object_2, float player_offset, float item_offset);
  static bool enemyCollision(sf::Sprite& player, sf::Sprite& enemy, float player_offset, float enemy_offset);
  static bool platformCollision(sf::Sprite& object_1, sf::RectangleShape& object_2, float offset);
  static bool collisionXBox(sf::Sprite& object_1, sf::RectangleShape& object_2);
  static bool floorCheck(sf::Sprite* object_1, sf::Sprite* object_2);
  static void updateAnimation(sf::Sprite& sprite, sf::Clock& timer, float update_rate, int state, sf::IntRect& current_frame, int top_max, int size);
  static bool wallsCollision(sf::Sprite& object, sf::RenderWindow& window);
  static bool wallsCollision(sf::Sprite& object, float max_window_size, float player_offset);
  static bool windowBottom(sf::Sprite& player, float window_y, float offset);
  static float resetVectorY(sf::Vector2f& velocity);
  static void cameraSystem(sf::View &camera, Data& data, float dt, const sf::Sprite& player);
  static int randomize(int min, int max);
  static void moveEnemy(sf::Sprite& enemy, sf::RectangleShape& platform, float dt, float offset, sf::Vector2f& direction, float speed);
  static void collectiblesAnim(sf::Sprite& collectible, sf::Clock& timer, float elapsed_time, sf::Vector2f& direction , float dt);
  static bool insideText(sf::Event& event, sf::Text& text);



 public:
  //int current_state;

};



#endif // PLATFORMERSFML_FUNCTIONS_H
