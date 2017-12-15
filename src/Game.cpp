#include "Game.hpp"
#include "SplashState.hpp"

namespace Hills
{
	Game::Game( int width, int height, std::string title )
	{
		//Create the game window and add splash state
		this->_data->window.create( sf::VideoMode( width, height ), title, sf::Style::Close | sf::Style::Titlebar );
		this->_data->machine.AddState(StateRef(new SplashState(this->_data)));
        //Start the game
		this->Run();
	}


	void Game::Run()
	{
		float newTime, frameTime, interpolation;
		float currentTime = this->_clock.getElapsedTime().asSeconds();
		float accumulator = 0.0f;

		while ( this->_data->window.isOpen() )
		{
			this->_data->machine.ProcessStateChanges();

			newTime = this->_clock.getElapsedTime().asSeconds();
			frameTime = newTime - currentTime;

			if ( frameTime > 0.25f )
			{
				frameTime = 0.25f;
			}

			currentTime = newTime;
			accumulator += frameTime;

			while( accumulator >= dt )
			{
				this->_data->machine.GetActiveState()->HandleInput();
				this->_data->machine.GetActiveState()->Update( dt );

				accumulator -= dt;
			}
            
            //using time accumulator and interpolation allows the game to render at
            //different frame rates
			interpolation = accumulator / dt;
			this->_data->machine.GetActiveState()->Draw(interpolation);
		}
	}
}


