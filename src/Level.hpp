#pragma once

#include "DEFINITIONS.hpp"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>

namespace Hills
{
    class Level : public sf::Drawable, public sf::Transformable
    {
        public:
            Level( GameDataRef data, b2World& world, float factor, float roughness );
        private:
            GameDataRef _data;
            b2World& world;
            sf::Texture _leveltexture;
            //std::vector<float> _points;
            sf::VertexArray _vertices;
            std::vector<float> GenerateTerrain( float factor, float roughness );
            virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;
    };
}
