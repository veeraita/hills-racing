#pragma once
#include "GameState.hpp"
#include "MainMenuState.hpp"
#include "HighscoreState.cpp"
#include "GameOverState.hpp"
#include "GameOverState.cpp"
#include "Level.cpp"
#include "b2GLDraw.h"
#include "b2GLDraw.cpp"
#include "DEFINITIONS.hpp"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <fstream>

namespace Hills
{
        GameState::GameState( GameDataRef data, std::string level_filename) : _data( data ), world(b2World(b2Vec2(0.0f, -9.8f))), _filename(level_filename)
	{

	}

	void GameState::Init()
	{

        /*====================== LOADING TEXTURES ================================================*/
                this->_data->assets.LoadTexture( "Game State Background", GAME_BACKGROUND_FILEPATH_1, true );
		//this->_data->assets.LoadTexture( "Land", LAND_FILEPATH_1 );

                if("Levels/level2.txt" == _filename){
                        this->_data->assets.LoadTexture( "Game State Background", GAME_BACKGROUND_FILEPATH_2, true );
		        //this->_data->assets.LoadTexture( "Land", LAND_FILEPATH_2 );
                }
                else if("Levels/level3.txt" == _filename){
                        this->_data->assets.LoadTexture( "Game State Background", GAME_BACKGROUND_FILEPATH_3, true );
		        //this->_data->assets.LoadTexture( "Land", LAND_FILEPATH_3 );
                }
		
		this->_data->assets.LoadTexture( "Chassis", CHASSIS_FILEPATH );
                this->_data->assets.LoadTexture( "Wheel", WHEEL_FILEPATH );
                this->_data->assets.LoadFont( "Game font", FONT_FILEPATH );

		level = new Level( this->_data, world, _filename );
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

        // This is gonna be the printed time
        timerText.setFont(this->_data->assets.GetFont( "Game font" ));
        timerText.setCharacterSize(40);
        timerText.setPosition(-500+view.getCenter().x,-500+view.getCenter().y);

        velocityText.setFont(this->_data->assets.GetFont( "Game font" ));
        velocityText.setCharacterSize(40);
        velocityText.setPosition(-500+view.getCenter().x,-450+view.getCenter().y);
        
        pointsText.setFont(this->_data->assets.GetFont( "Game font" ));
        pointsText.setCharacterSize(40);
        pointsText.setPosition(-500+view.getCenter().x,-400+view.getCenter().y);

        pointsNumber.setFont(this->_data->assets.GetFont( "Game font" ));
        pointsNumber.setCharacterSize(40);
        pointsNumber.setPosition(-375+view.getCenter().x,-400+view.getCenter().y);

        angleText.setFont(this->_data->assets.GetFont( "Game font" ));
        angleText.setCharacterSize(40);
        angleText.setPosition(-500+view.getCenter().x, -350 + view.getCenter().y);

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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
                car->Reverse();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
                car->Accelerate();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
                car->TiltDown();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
                car->TiltUp();
        }

	}

	void GameState::Update( float dt )
	{
        world.Step( dt, 8, 3 );
        
        /*====================== GAME OVER WHEN STUCK UPSIDE DOWN  ============================================*/
        sf::Vector2f pos = car->getChassisSprite().getPosition();
        float angle = car->GetAngle();
        angle = (angle / 3.14) * 180;
        
        while(angle <= 0)
        {
            angle += 360;
        }
        
        while(angle > 360)
        {
            angle -= 360;
        }
        
        if (!(angle < 120 || angle >240))
        {
            if((abs(round(((float) pos.x - (float) prevPos.x)*30)) == 0) && (abs(round(((float) pos.y - (float) prevPos.y)*30)) == 0))
            {
                    this->_data->machine.AddState( StateRef( new GameOverState( this->_data ) ), true );
            }
        }
        
        /*====================== TIMER, VELOCITY, ANGLE  ============================================*/
        sf::Time elapsed = clock.getElapsedTime();
        int minutes = floor(elapsed.asSeconds() / 60); // counts how many mins have gone
        int seconds = (int) elapsed.asSeconds(); // counts the elapsed time in seconds
        std::string sec;
        if ((seconds - minutes*60) < 10)
        {
                sec = '0' + std::to_string(seconds - minutes*60);
        }
        else
        {
                sec = std::to_string(seconds - minutes*60);
        }
        timerText.setString("Time: " +std::to_string(minutes)+ ":" + sec);
        
        float velocity = abs(round(((float) pos.x - (float) prevPos.x)*30));
        velocityText.setString("Speed: " + std::to_string((int) velocity)+" KM/H");
        
        angleText.setString("Angle: " + std::to_string( (int) angle) + " deg");
        
        pointsText.setString("Points: ");
        pointsNumber.setString(std::to_string(intPoints));
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

        /*====================== DRAW BACKGROUND, LEVEL AND CAR  ============================================*/
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

        /*====================== MAKE CAMERA FOLLOW THE CAR  ============================================*/
        //sf::Vector2f prevPos2 = getPrevPos();
        sf::Vector2f pos = car->getChassisSprite().getPosition();
        if (pos.x > SCREEN_WIDTH/2 && pos.x < level->getLevelLength() - SCREEN_WIDTH/2)
        {
            if (pos.y <= SCREEN_HEIGHT - 15.0f*SCALE)
            {
                view.setCenter(pos.x, SCREEN_HEIGHT - 15.0f*SCALE);
            }
            else if (pos.y >=  SCREEN_HEIGHT - 10.0f*SCALE)
            {
                view.setCenter(pos.x, SCREEN_HEIGHT - 10.0f*SCALE);
                
                if (pos.y >=  SCREEN_HEIGHT)
                {
                    this->_data->machine.AddState( StateRef( new GameOverState( this->_data ) ), true );
                }
            }
            else
            {
                view.setCenter(pos);
            }
        }

        /*====================== SCORING  ============================================*/
        for (unsigned int i = 0; i < level->getTokens().size(); i++) 
        // if the car collides with a star, the following will happen
        {
            if (car->getChassisSprite().getGlobalBounds().intersects(level->getTokens().at(i).getGlobalBounds()))
            {
                level->deleteToken(i);  //deletes the token
                intPoints += 10; //  we get points
            }
        }

        if (car->getChassisSprite().getGlobalBounds().intersects(level->getFinishSprite().getGlobalBounds())) 
        // if the car collides with the finish line, the following will happen
        {

          std::string p = pointsNumber.getString();

          std::ofstream allscores;
          allscores.open("allscores.txt",std::ios::out |std::ios::app);
          if (!allscores)
          {
            std::cerr << "Error opening the file" << std::endl;
          }

          allscores << p << std::endl;
          allscores.close();

          std::ofstream recentscore;
          recentscore.open("recentscore.txt");
          if (!recentscore)
          {
            std::cerr << "Error opening the file" << std::endl;
          }
          recentscore << p << std::endl;
          recentscore.close();

          this->_data->machine.AddState( StateRef( new GameOverState( this->_data ) ), true );
        }


        /*====================== DRAW INFO TEXTS  ============================================*/
        this->_data->window.draw(timerText);
        this->_data->window.draw(velocityText);
        this->_data->window.draw(angleText);
        this->_data->window.draw(pointsText);
        this->_data->window.draw(pointsNumber);

        //world.DrawDebugData(); //comment out if you dont need debug drawing
        this->_data->window.display();
        prevPos = pos;
	}

	sf::Vector2f GameState::getPrevPos ()
	{
		return prevPos;
	}
}
