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
		this->_data->assets.LoadTexture( "Game State Background", GAME_BACKGROUND_FILEPATH, true );
		this->_data->assets.LoadTexture( "Land", LAND_FILEPATH );
		this->_data->assets.LoadTexture( "car body sprite", CAR_BODY_FILEPATH);
		
		//define terrain shape
		//std::vector<float> points = {0.25f, 1.0f, 4.0f, 0.0f, 0.0f, -1.0f, -2.0f, -2.0f, -1.25f, 0.0f};
		
		this->level = new Level( this->_data, 2, 0.5 );
		this->car = new Car( this->_data);
		
		this->_background.setTexture( this->_data->assets.GetTexture( "Game State Background") );
		this->_background.setScale(2,2);
		// make the sprite longer so the texture repeats itself
		this->_background.setTextureRect( sf::IntRect(0, 0, NUM_POINTS * LEVEL_DX * SCALE / 2, SCREEN_HEIGHT) );
		this->_background.move(0,-200);
		
		view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
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
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            if (view.getCenter().x >= 10 + SCREEN_WIDTH / 2)
            {
                view.move(-10, 0);
            }
        }
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
                view.move(10, 0);
        }
        
	}

	void GameState::Update( float dt )
	{

	}

	void GameState::Draw( float dt )
	{
	    this->_data->window.setView(view);
		this->_data->window.clear( );
		this->_data->window.draw( this->_background );
		this->_data->window.draw( *level );
		this->_data->window.display();
		this->car->draw();
	}

}
