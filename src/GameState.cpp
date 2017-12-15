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

    GameState::~GameState()
    {
        delete level;
        delete car;
    }

	void GameState::Init()
	{
        /*====================== LOADING AUDIO ===================================================*/
        if( !applauseBuffer.loadFromFile( APPLAUSE_SOUND_FILEPATH ) )
        {
            std::cout << "Error loading applause sound effect" << std::endl;
        }
        // if( !driveBuffer.loadFromFile( DRIVE_SOUND_FILEPATH ) )
        // {
        //     std::cout << "Error loading drive sound effect" << std::endl;
        // }
        if( !buttonBuffer.loadFromFile( BUTTON_SOUND_FILEPATH ) )
        {
            std::cout << "Error loading button sound effect" << std::endl;
        }
        if( !engineBuffer.loadFromFile( ENGINE_SOUND_FILEPATH ) )
        {
            std::cout << "Error loading rngine sound effect" << std::endl;
        }
        if( !gameoverBuffer.loadFromFile( GAMEOVER_SOUND_FILEPATH ) )
        {
            std::cout << "Error loading gameover sound effect" << std::endl;
        }
        if( !musicBuffer.loadFromFile( MUSIC_FILEPATH ) )
        {
            std::cout << "Error loading gameover sound effect" << std::endl;
        }
        applauseSound.setBuffer( applauseBuffer );
        driveSound.setBuffer( driveBuffer );
        buttonSound.setBuffer( buttonBuffer );
        engineSound.setBuffer( engineBuffer );
        gameoverSound.setBuffer( gameoverBuffer );
        music.setBuffer( musicBuffer );

        music.setVolume(50);
        music.setLoop(true);
        music.play();


        /*====================== LOADING TEXTURES ================================================*/
        this->_data->assets.LoadTexture( "Game State Background", GAME_BACKGROUND_FILEPATH_1, true );
		//this->_data->assets.LoadTexture( "Land", LAND_FILEPATH_1 );

        if("Levels/level2.txt" == _filename)
        {
            this->_data->assets.LoadTexture( "Game State Background", GAME_BACKGROUND_FILEPATH_2, true );
            //this->_data->assets.LoadTexture( "Land", LAND_FILEPATH_2 );
        }
        else if("Levels/level3.txt" == _filename)
        {
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

        velocityText.setFont(this->_data->assets.GetFont( "Game font" ));
        velocityText.setCharacterSize(40);

        pointsText.setFont(this->_data->assets.GetFont( "Game font" ));
        pointsText.setCharacterSize(40);

        pointsNumber.setFont(this->_data->assets.GetFont( "Game font" ));
        pointsNumber.setCharacterSize(40);

        angleText.setFont(this->_data->assets.GetFont( "Game font" ));
        angleText.setCharacterSize(40);

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

        if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down ) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::W ) || sf::Keyboard::isKeyPressed(sf::Keyboard::S )))
        {
                car->Brake();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
                this->_data->machine.AddState( StateRef( new GameState( this->_data, _filename ) ), true );
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
                this->_data->machine.AddState( StateRef( new MainMenuState( this->_data ) ), true );
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) )
        {
            //this->engineSound.play();
            car->Reverse();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            //this->engineSound.play();
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
                music.stop();
                gameoverSound.play();
                this->_data->machine.AddState( StateRef( new GameOverState( this->_data, this->_filename ) ), true );

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
        std::ifstream recentlevel;
        std::string levelstring;
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
                    std::ifstream recentlevel;
                    std::string levelstring;
                    recentlevel.open("recentlevel.txt");
                    std::getline(recentlevel,levelstring);
                    recentlevel.close();

                    std::string p = std::to_string(intPoints);
                    std::ofstream allscores;
                    allscores.open("allscoreslevel"+levelstring+".txt",std::ios::out |std::ios::app);
                    
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

                    music.stop();
                    gameoverSound.play();
                    this->_data->machine.AddState( StateRef( new GameOverState( this->_data, this->_filename ) ), true );
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
                buttonSound.play();
                level->deleteToken(i);  //deletes the token
                intPoints += 10; //  we get points
            }
        }

        if (car->getChassisSprite().getGlobalBounds().intersects(level->getFinishSprite().getGlobalBounds()))
        // if the car collides with the finish line, the following will happen
        {
            int elapsed = clock.getElapsedTime().asSeconds();

            intPoints += 1000 - elapsed*5;
            if (intPoints < 0)
            {
                intPoints = 0;
            }
            std::string p = std::to_string(intPoints);

            std::ofstream allscores;
            allscores.open("allscoreslevel"+levelstring+".txt",std::ios::out |std::ios::app);
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
            
            music.stop();
            applauseSound.play();
            this->_data->machine.AddState( StateRef( new GameOverState( this->_data, this->_filename ) ), true );
        }


        /*====================== DRAW INFO TEXTS  ============================================*/
        timerText.setPosition(-500+view.getCenter().x,-500+view.getCenter().y);
        this->_data->window.draw(timerText);
        velocityText.setPosition(-500+view.getCenter().x,-450+view.getCenter().y);
        this->_data->window.draw(velocityText);
        pointsText.setPosition(-500+view.getCenter().x,-400+view.getCenter().y);
        this->_data->window.draw(pointsText);
        pointsNumber.setPosition(-375+view.getCenter().x,-400+view.getCenter().y);
        this->_data->window.draw(pointsNumber);
        angleText.setPosition(-500+view.getCenter().x, -350 + view.getCenter().y);
        this->_data->window.draw(angleText);
        this->_data->window.draw(pointsNumber);
        angleText.setPosition(-500+view.getCenter().x, -350 + view.getCenter().y);
        this->_data->window.draw(angleText);

        sf::Text controlsText;
        controlsText.setFont(this->_data->assets.GetFont( "Game font" ));
        controlsText.setCharacterSize(30);
        controlsText.setString("UP/W Accelerate\nDOWN/S Brake\nLEFT/A Tilt Up\nRIGHT/D Tilt Down\n\nR Restart\nESC Main Menu");
        controlsText.setPosition(250+view.getCenter().x, -500 + view.getCenter().y);
        this->_data->window.draw(controlsText);


        //world.DrawDebugData(); //comment out if you dont need debug drawing
        this->_data->window.display();
        prevPos = pos;
	}

	sf::Vector2f GameState::getPrevPos ()
	{
		return prevPos;
	}
}
