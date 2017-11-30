#include "Game.hpp"
#include "SplashState.hpp"

//GameState. Täällä tapahtuu itse pelin pyöritys.
namespace Hills
{
	Game::Game( int width, int height, std::string title )
	{
		//Game-constructor, jossa luodaan aluksi peli-ikkuna ja lisätään uusi tila SplashState (eka tila joka näkyy kun pelin buildaa)
		this->_data->window.create( sf::VideoMode( width, height ), title, sf::Style::Close | sf::Style::Titlebar );
		this->_data->machine.AddState(StateRef(new SplashState(this->_data)));
		//Constructor kutsuu myös saman luokan Run-funktiota, eli kun Game-olio luodaan mainissa
		//se aloittaa saman tien Game-loopin
		this->Run();
	}

	//Tähän pitää pureutua vielä vähän tarkemmin
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

			interpolation = accumulator / dt;
			this->_data->machine.GetActiveState()->Draw(interpolation);
		}
	}
}
