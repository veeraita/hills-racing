#pragma once

#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "Game.hpp"

namespace Hills
{
    class Car
    {
    public:
        Car(GameDataRef data);
        void draw();

    private:
        GameDataRef _data;
        sf::Sprite _bodySprite;
    };
}