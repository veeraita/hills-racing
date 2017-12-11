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
          void Draw( b2World& world, sf::Sprite _chassissprite, sf::Sprite _wheelsprite1, sf::Sprite _wheelsprite2, GameDataRef _data );
      private:
          GameDataRef _data;
          b2World& world;
          sf::Texture _chassistexture;
          sf::Texture _wheeltexture;
          sf::Sprite _wheelsprite1;
          sf::Sprite _wheelsprite2;
          sf::Sprite _chassissprite;
          //virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;
  };
}
