#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "DEFINITIONS.hpp"
#include "Game.hpp"

namespace Hills
{
  class Car
  {
      public:
          Car( GameDataRef data, b2World& world );
          //void Draw( b2Body* car, b2Body* wheel1, b2Body* wheel2, sf::Sprite _chassissprite, sf::Sprite _wheelsprite1, sf::Sprite _wheelsprite2, GameDataRef _data );
          sf::Sprite& getChassisSprite();
          sf::Sprite& getWheelSprite1();
          sf::Sprite& getWheelSprite2();
      private:
          GameDataRef _data;
          b2World& world;
          //sf::Texture _chassistexture;
          //sf::Texture _wheeltexture;
          sf::Sprite _wheelsprite1;
          sf::Sprite _wheelsprite2;
          sf::Sprite _chassissprite;
          b2Body* car;
          b2Body* wheel1;
          b2Body* wheel2;
          b2WheelJoint* spring1;
	      b2WheelJoint* spring2;
  };
}
