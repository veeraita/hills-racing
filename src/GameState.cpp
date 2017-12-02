#pragma once
#include "GameState.hpp"
#include "Level.cpp"
#include "DEFINITIONS.hpp"
#include <vector>
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
		
		std::vector<float> points = {0.25f, 1.0f, 4.0f, 0.0f, 0.0f, -1.0f, -2.0f, -2.0f, -1.25f, 0.0f};
		
		this->level = new Level( this->_data, points );
		
		this->_background.setTexture( this->_data->assets.GetTexture( "Game State Background") );
		this->_background.setScale(2,2);
		
		view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	    this->_data->window.setView(view);
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
        level->MoveLevel( );
	}

	void GameState::Draw( float dt )
	{
		this->_data->window.clear(sf::Color::Red);
		this->_data->window.draw( this->_background );
		this->_data->window.draw( *level );
		//level->DrawLevel( );
		this->_data->window.display();
	}

}
