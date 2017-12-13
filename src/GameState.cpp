#pragma once
#include "GameState.hpp"
#include "Level.cpp"
#include "b2GLDraw.h"
#include "b2GLDraw.cpp"
#include "DEFINITIONS.hpp"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>

namespace Hills
{
        GameState::GameState( GameDataRef data) : _data( data ), world(b2World(b2Vec2(0.0f, -9.8f)))
	{

	}

	void GameState::Init()
	{

                /*====================== LOADING TEXTURES ================================================*/
		this->_data->assets.LoadTexture( "Game State Background", GAME_BACKGROUND_FILEPATH, true );
		this->_data->assets.LoadTexture( "Land", LAND_FILEPATH );
		this->_data->assets.LoadTexture( "Chassis", CHASSIS_FILEPATH );
        this->_data->assets.LoadTexture( "Wheel", WHEEL_FILEPATH );

        // TODO: choose filename according to level selection
        std::string filename = "level1.txt";
		level = new Level( this->_data, world, filename );
		car = new Car( this->_data, world );

                /*====================== SETUP THE BACKGROUND AND VIEW ============================================*/
		this->_background.setTexture( this->_data->assets.GetTexture( "Game State Background") );
		this->_background.setScale(2,2);
		// make the sprite longer so the texture repeats itself
		this->_background.setTextureRect( sf::IntRect(0, 0, level->getLevelLength() / 2, SCREEN_HEIGHT) );
		this->_background.move(0,-200);

		view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

        sf::Sprite chassissprite;
        chassissprite.setTexture( this->_data->assets.GetTexture( "Chassis") );
        sf::Sprite wheelsprite1;
        wheelsprite1.setTexture( this->_data->assets.GetTexture( "Wheel" ) );
        sf::Sprite wheelsprite2;
        wheelsprite2.setTexture( this->_data->assets.GetTexture( "Wheel" ) );

		if(!timerFont.loadFromFile("Resources/KhmerOS.ttf"))
		{
			std::cerr << "No font file found!" << std::endl;
		}

		//sf::Clock clock; // starts the clock

 		// This is gonna be the printed time
		timerText.setFont(timerFont); // The font is the one loaded above
		//timerText.setString(std::to_string(0)); // Setting it 0 when the game starts
		timerText.setCharacterSize(40); // Font size is 40 px I guess?

		velocityText.setFont(timerFont); // The font is the one loaded above
		//timerText.setString(std::to_string(0)); // Setting it 0 when the game starts
		//timerText.setPosition(40,300); // Position is somewhere
		velocityText.setCharacterSize(40); // Font size is 40 px I guess?


		//this->_data->window.draw(timerText);
		// sf::Text text;
		// text.setFont(timerFont);
		// text.setString("haha");
		// text.setPosition(0,0);
		// text.setCharacterSize(200);
		// this->_data->window.draw(text);

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
                car->Reverse();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
                car->Accelerate();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
                car->TiltDown();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
                car->TiltUp();
        }

	}

	void GameState::Update( float dt )
	{

	}

	void GameState::Draw( float dt )
	{
        /*====================== DEBUG DRAWING MODE  ============================================*/
        b2GLDraw debugDrawInstance(this->_data->window);
        world.SetDebugDraw( &debugDrawInstance );
        uint32 flags = 0;
        flags += b2Draw::e_shapeBit;
        flags += b2Draw::e_jointBit;
        flags += b2Draw::e_pairBit;
        flags += b2Draw::e_centerOfMassBit;
        flags += b2Draw::e_aabbBit;
        debugDrawInstance.SetFlags( flags );

        world.Step( 1.0f/60.0f, 8, 3 );
        this->_data->window.setView( view );
        this->_data->window.clear( );
        this->_data->window.draw( this->_background );
        sf::RectangleShape finishFlag = level->getFinishSprite();
	    this->_data->window.draw( finishFlag );
        this->_data->window.draw( *level );
        sf::Sprite chassis = car->getChassisSprite();
        sf::Sprite wheel1 = car->getWheelSprite1();
        sf::Sprite wheel2 = car->getWheelSprite2();
        this->_data->window.draw( chassis );
        this->_data->window.draw( wheel1 );
        this->_data->window.draw( wheel2 );
        
        sf::Vector2f prevPos2 = getPrevPos();
        sf::Vector2f pos = car->getChassisSprite().getPosition();
        if (pos.x > SCREEN_WIDTH/2 && pos.x < level->getLevelLength() - SCREEN_WIDTH/2)
        {
            if (pos.y <= SCREEN_HEIGHT - 10.0f*SCALE)
            {
                view.setCenter(pos.x, SCREEN_HEIGHT - 10.0f*SCALE);
            }
            else if (pos.y >=  SCREEN_HEIGHT)
            {
                view.setCenter(pos.x, SCREEN_HEIGHT);
            }
            else
            {
                view.setCenter(pos);
            }
        }
        
        for (unsigned int i = 0; i < level->getTokens().size(); i++)
        {
            if (car->getChassisSprite().getGlobalBounds().intersects(level->getTokens().at(i).getGlobalBounds()))
            {
                level->deleteToken(i);
            }
        }

        sf::Time elapsed = clock.getElapsedTime();
        timerText.setPosition(-500+view.getCenter().x,-500+view.getCenter().y);
        int minutes = floor(elapsed.asSeconds() / 60); // counts how many mins have gone
        int seconds = (int) elapsed.asSeconds(); // counts the elapsed time in seconds
        timerText.setString("Time: " +std::to_string(minutes)+ ":" + std::to_string(seconds - minutes*60));
        this->_data->window.draw(timerText);

        float velocity = abs(round(((float) pos.x - (float) prevPos2.x)*30));
        velocityText.setString("Speed: " + std::to_string((int) velocity)+" KM/H");
        velocityText.setPosition(-500+view.getCenter().x,-450+view.getCenter().y);
        this->_data->window.draw(velocityText);
        world.DrawDebugData();//comment out if you dont need debug drawing
        this->_data->window.display();
        prevPos = pos;
	}

	sf::Vector2f GameState::getPrevPos ()
	{
		return prevPos;
	}
}
