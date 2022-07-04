//
// Created by luria on 24/03/2022.
//

#ifndef PLATFORMERSFML_MAPS_H
#define PLATFORMERSFML_MAPS_H
#include <SFML/Graphics.hpp>
#include "../Functions.h"


class Maps
{
 public:
  Maps(Data& data);
  virtual ~Maps();
  void init();
  void update();
  void render();
  void rectangles();


  sf::RectangleShape rectangle[17];

 private:


  sf::Sprite background;
  sf::Texture background_image;
  int array_width;
  int array_height;

  Data& data;

};

#endif // PLATFORMERSFML_MAPS_H
