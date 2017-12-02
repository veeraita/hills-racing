#pragma once

#include "DEFINITIONS.hpp"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

namespace Hills 
{
    class Level : public sf::Drawable, public sf::Transformable
    {
        public:
            Level( GameDataRef data );
            void MoveLevel( );
        private:
            GameDataRef _data;
            sf::Texture _leveltexture;
            sf::VertexArray _vertices;
            virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;
    };
}
