#pragma once
#include <sstream>
#include "GameOverState.hpp"
#include "GameState.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>
#include <fstream>
#include <string>

namespace Hills
{
	GameOverState::GameOverState( GameDataRef data) : _data( data )
	{

	}

	void GameOverState::Init()
	{
        this->_data->window.setView(view); // sets the view to the start
        std::cout<< "Game Over" << std::endl;
		this->_data->assets.LoadTexture( "Game State Background", GAME_BACKGROUND_FILEPATH );
		this->_background.setTexture( this->_data->assets.GetTexture( "Game State Background") );
		this->_background.setScale(2,2);

		if(!textFont.loadFromFile("Resources/dpcomic.ttf"))
		{
						std::cerr << "No font file found!" << std::endl;
		}
		//
		std::string scorestring;
		std::ifstream recentscore;
		recentscore.open("recentscore.txt");
		std::getline(recentscore,scorestring);
		recentscore.close();
		//std::string scorestring = "80";
		int scoreint = std::stoi(scorestring); // store the points for possible later comparions

		score.setFont(textFont);
		score.setCharacterSize(25);
		score.setString("Your score this game was: "+scorestring);
		score.setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);

		exitText.setFont(textFont);
		exitText.setCharacterSize(25);
		exitText.setString("You can return to the main menu by pressing the Esc key");
		exitText.setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/2 + 300);

		gameOver.setFont(textFont);
		gameOver.setCharacterSize(100);
		gameOver.setString("GAME OVER!");
		gameOver.setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/2 - 300);
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
                this->_data->machine.AddState( StateRef( new MainMenuState( this->_data ) ), true );
        }
	}

	void GameOverState::Update( float dt )
	{

	}

	void GameOverState::Draw( float dt )
	{
		this->_data->window.clear(sf::Color::Red);
		this->_data->window.draw( this->_background );
		this->_data->window.draw(score);
		this->_data->window.draw(exitText);
		this->_data->window.draw(gameOver);
		this->_data->window.display();

        //sf::Text points = getPoints();

	}

}
