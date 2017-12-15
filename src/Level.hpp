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
            Level( GameDataRef data, b2World& world, std::string _filename );
            sf::RectangleShape getFinishSprite();
            std::vector<sf::Sprite> getTokens();
            int getLevelLength();
            void deleteToken(unsigned int i);
        private:
            GameDataRef _data;
            b2World& world;
            std::string _filename;
            sf::Texture _leveltexture;
            sf::VertexArray _vertices;
            std::vector<std::pair<float, float>> _points;
            std::vector<sf::Sprite> _tokens;
            sf::RectangleShape _finishLine;
            void LoadTerrain(std::string& filename);
            void CreateTerrain();
            void CreateTokens();
            virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;
    };
}
