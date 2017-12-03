#include "Game.hpp"
#include "Game.cpp"
#include "AssetManager.hpp"
#include "AssetManager.cpp"
#include "InputManager.hpp"
#include "InputManager.cpp"
#include "StateMachine.hpp"
#include "StateMachine.cpp"
#include "State.hpp"
#include "SplashState.hpp"
#include "SplashState.cpp"
#include "DEFINITIONS.hpp"
#include "Car.cpp"
#include "Car.hpp"

int main()
{
    Hills::Game( SCREEN_WIDTH, SCREEN_HEIGHT, "Hills Racing" );
    return 0;
}
