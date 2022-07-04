//
// Created by luria on 24/03/2022.
//

#include "Maps.h"
#include <iostream>

Maps::Maps(Data& data) : data(data) {



  init();
}
Maps::~Maps() {}

void Maps::init()
{
  if (!background_image.loadFromFile("Data/Images/Platformer.png"))
  {
    std::cout << "Background didn't load \n";
  }
  background.setTexture(background_image);



  array_height = 12;
  array_width = 24;

  rectangles();

  for (int i = 0; i < 17; ++i)
  {
    rectangle[i].setFillColor(sf::Color(255, 0,0, 0));
  }
}

void Maps::update()
{

}

void Maps::render()
{
  data.window.draw(background);

  /// turn on when editing position.
//  for (int i = 0; i < 17; ++i)
//  {
//    data.window.draw(rectangle[i]);
//  }
}
void Maps::rectangles()
{
  rectangle[0].setSize(sf::Vector2f(382, 64));
  rectangle[0].setPosition(0, data.window.getSize().y - rectangle[0].getGlobalBounds().height);

  rectangle[1].setSize(sf::Vector2f(272, 64));
  rectangle[1].setPosition(424, 570);

  rectangle[2].setSize(sf::Vector2f(120, 64));
  rectangle[2].setPosition(740, 670);

  rectangle[3].setSize(sf::Vector2f(120, 64));
  rectangle[3].setPosition(965, 670);

  rectangle[4].setSize(sf::Vector2f(272, 64));
  rectangle[4].setPosition(870, 445);

  rectangle[5].setSize(sf::Vector2f(272, 64));
  rectangle[5].setPosition(521, 350);

  rectangle[6].setSize(sf::Vector2f(415, 64));
  rectangle[6].setPosition(0, 350);

  rectangle[7].setSize(sf::Vector2f(170, 64));
  rectangle[7].setPosition(908, 248);

  rectangle[8].setSize(sf::Vector2f(60, 64));
  rectangle[8].setPosition(0, 155);

  rectangle[9].setSize(sf::Vector2f(160, 64));
  rectangle[9].setPosition(155, 155);

  rectangle[10].setSize(sf::Vector2f(120, 64));
  rectangle[10].setPosition(1187, 248);

  rectangle[11].setSize(sf::Vector2f(120, 64));
  rectangle[11].setPosition(1187, 570);

  rectangle[12].setSize(sf::Vector2f(180, 64));
  rectangle[12].setPosition(1545, 445);

  rectangle[13].setSize(sf::Vector2f(90, 64));
  rectangle[13].setPosition(1580, 265);

  rectangle[14].setSize(sf::Vector2f(185, 64));
  rectangle[14].setPosition(1672, 540);

  rectangle[15].setSize(sf::Vector2f(190, 64));
  rectangle[15].setPosition(1910, 490);

  rectangle[16].setSize(sf::Vector2f(90, 64));
  rectangle[16].setPosition(2122, 450);
}
