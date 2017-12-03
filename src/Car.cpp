#pragma once

#include "Car.hpp"

namespace Hills
{
    Car::Car(GameDataRef data) : _data(data){
        _bodySprite.setTexture(_data->assets.GetTexture("car body sprite"));
    }

    void Car::draw(){
        _data->window.draw( _bodySprite);
    }
}
// Tänne dynaaminen objekti Car, joka likkuu 

/*



https://www.sfml-dev.org/documentation/2.0/classsf_1_1Keyboard.php


Liikuttaa vasemmalle
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
{
    // left key is pressed: move our character
    character.move(-1, 0);
}



Liikuttaa oikealle
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
{
    // left key is pressed: move our character
    character.move(1, 0);
}


*/
