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
            Level( GameDataRef data, b2World& world, std::string& filename );
        private:
            GameDataRef _data;
            b2World& world;
            std::string& filename;
            sf::Texture _leveltexture;
            sf::VertexArray _vertices;
            //std::vector<float> GenerateTerrain( float factor, float roughness );
            std::vector<std::pair<float, float>> LoadTerrain(std::string& filename);
            void CreateTerrain(std::vector<std::pair<float, float>> points);
            virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;
    };
}
