#pragma once
#include <sstream>
#include "GameOverState.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

namespace Hills
{
	GameOverState::GameOverState( GameDataRef data) : _data( data )
	{

	}

	void GameOverState::Init()
	{
    std::cout<< "Game Over" << std::endl;
		this->_data->assets.LoadTexture( "Game Over State Background", GAME_OVER_BACKGROUND_FILEPATH );
		this->_background.setTexture( this->_data->assets.GetTexture( "Game Over State Background") );
	}

	void GameOverState::HandleInput( )
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

	void GameOverState::Update( float dt )
	{

	}

	void GameOverState::Draw( float dt )
	{
		this->_data->window.clear(sf::Color::Red);
		this->_data->window.draw( this->_background );
		this->_data->window.display();
	}

}
