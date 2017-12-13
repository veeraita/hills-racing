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
		}
	}

	void HighscoreState::Update( float dt )
	{

	}

	void HighscoreState::Draw( float dt )
	{
		this->_data->window.clear(sf::Color::Red);
		this->_data->window.draw( this->_background );
		this->_data->window.display();
	}

}
