#pragma once
#include <sstream>
#include "HighscoreState.hpp"
#include "MainMenuState.hpp"
#include "MainMenuState.cpp"
#include "DEFINITIONS.hpp"
#include <iostream>

namespace Hills
{
	HighscoreState::HighscoreState( GameDataRef data) : _data( data )
	{

	}

	void HighscoreState::Init()
	{
		this->_data->assets.LoadTexture( "Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH );
		this->_background.setTexture( this->_data->assets.GetTexture( "Splash State Background") );
		this->_data->assets.LoadTexture( "Exit Button", EXIT_FILEPATH );
		this->_exitButton.setTexture(this->_data->assets.GetTexture("Exit Button"));

	}

	void HighscoreState::HandleInput( )
	{
		sf::Event event;

		while ( this->_data->window.pollEvent( event ) )
		{
			if ( sf::Event::Closed == event.type )
			{
				this->_data->window.close();
			}

			if ( this->_data->input.IsSpriteClicked( this->_exitButton, sf::Mouse::Left, this->_data->window ) )
			{
				this->_data->machine.AddState( StateRef( new MainMenuState( this->_data ) ), true );
			}


		}
	}

	void HighscoreState::Update( float dt )
	{

	}

	void HighscoreState::Draw( float dt )
	{
		this->_data->window.clear(sf::Color::Red);
		this->_data->window.draw( this->_background );
		this->_data->window.draw(this->_exitButton);
		this->_data->window.display();
	}

}
