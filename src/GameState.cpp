#pragma once
#include "GameState.hpp"
#include "Land.cpp"
#include "DEFINITIONS.hpp"
#include <iostream>
#include <sstream>

namespace Hills
{
	GameState::GameState( GameDataRef data) : _data( data )
	{

	}

	void GameState::Init()
	{
		this->_data->assets.LoadTexture( "Game State Background", GAME_BACKGROUND_FILEPATH );
		this->_data->assets.LoadTexture( "Land", LAND_FILEPATH );
		
		land = new Land( this->_data );
		
		this->_background.setTexture( this->_data->assets.GetTexture( "Game State Background") );
		this->_background.setScale(2,2);
	}

	void GameState::HandleInput( )
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

	void GameState::Update( float dt )
	{
        land->MoveLand( dt );
	}

	void GameState::Draw( float dt )
	{
		this->_data->window.clear(sf::Color::Red);
		this->_data->window.draw( this->_background );
		land->DrawLand( );
		this->_data->window.display();
	}

}
