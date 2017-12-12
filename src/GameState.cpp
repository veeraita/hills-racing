#pragma once
#include "GameState.hpp"
#include "Level.cpp"
#include "DEFINITIONS.hpp"
#include <vector>
#include <iostream>
#include <sstream>

namespace Hills
{
	GameState::GameState( GameDataRef data) : _data( data ), world(b2World(b2Vec2(0.0f, -9.8f)))
	{

	}

	void GameState::Init()
	{
		this->_data->assets.LoadTexture( "Game State Background", GAME_BACKGROUND_FILEPATH, true );
		this->_data->assets.LoadTexture( "Land", LAND_FILEPATH );
		this->_data->assets.LoadTexture( "Chassis", CHASSIS_FILEPATH );
        this->_data->assets.LoadTexture( "Wheel", WHEEL_FILEPATH );
		
		//define terrain shape
		//std::vector<float> points = {0.25f, 1.0f, 4.0f, 0.0f, 0.0f, -1.0f, -2.0f, -2.0f, -1.25f, 0.0f};
		
		//create world with gravity
        //b2Vec2 gravity(0.0f, -9.8f);
        //world.SetGravity(gravity);
		
		level = new Level( this->_data, world, 2, 0.4 );
		car = new Car( this->_data, world );
		
		this->_background.setTexture( this->_data->assets.GetTexture( "Game State Background") );
		this->_background.setScale(2,2);
		// make the sprite longer so the texture repeats itself
		this->_background.setTextureRect( sf::IntRect(0, 0, NUM_POINTS * LEVEL_DX * SCALE / 2, SCREEN_HEIGHT) );
		this->_background.move(0,-200);
		
		view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
		
        sf::Sprite chassissprite;
        chassissprite.setTexture( this->_data->assets.GetTexture( "Chassis") );
        sf::Sprite wheelsprite1;
        wheelsprite1.setTexture( this->_data->assets.GetTexture( "Wheel" ) );
        sf::Sprite wheelsprite2;
        wheelsprite2.setTexture( this->_data->assets.GetTexture( "Wheel" ) );
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
                car->Reverse();
            }
        }
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
                car->Accelerate();
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
                car->Brake();
        }
        
	}

	void GameState::Update( float dt )
	{

	}

	void GameState::Draw( float dt )
	{
	    world.Step( 1.0f/60.0f, 8, 3 );
	    this->_data->window.setView( view );
		this->_data->window.clear( );
		this->_data->window.draw( this->_background );
		this->_data->window.draw( *level );
		sf::Sprite chassis = car->getChassisSprite();
		sf::Sprite wheel1 = car->getWheelSprite1();
		sf::Sprite wheel2 = car->getWheelSprite2();
		this->_data->window.draw( chassis );
		this->_data->window.draw( wheel1 );
		this->_data->window.draw( wheel2 );
		sf::Vector2f pos = car->getChassisSprite().getPosition();
        view.setCenter(pos);
		this->_data->window.display( );
	}

}
