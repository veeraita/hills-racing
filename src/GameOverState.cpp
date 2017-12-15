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
	GameOverState::GameOverState( GameDataRef data, std::string level_filename) : _data( data ), _filename(level_filename)
	{

	}

	void GameOverState::Init()
	{
        this->_data->window.setView(view); // sets the view to the start
        std::cout<< "Game Over" << std::endl;
		this->_data->assets.LoadTexture( "Game State Background", GAME_BACKGROUND_FILEPATH_1 );
		this->_background.setTexture( this->_data->assets.GetTexture( "Game State Background") );
		this->_background.setScale(2,2);

		std::string scorestring;
		std::ifstream recentscore;
		recentscore.open("recentscore.txt");
		std::getline(recentscore,scorestring);
		recentscore.close();
		
		gameOver.setFont(this->_data->assets.GetFont( "Game font" ));
		gameOver.setCharacterSize(100);
		gameOver.setString("GAME OVER!");
		gameOver.setPosition((SCREEN_WIDTH - gameOver.getGlobalBounds().width) / 2, 100);

		score.setFont(this->_data->assets.GetFont( "Game font" ));
		score.setCharacterSize(50);
		score.setString("Your score for this game was: "+scorestring);
		score.setPosition((SCREEN_WIDTH - score.getGlobalBounds().width) / 2, 300);

		exitText.setFont(this->_data->assets.GetFont( "Game font" ));
		exitText.setCharacterSize(50);
		exitText.setString("\tPress R to restart.\n\nYou can return to the main \nmenu by pressing the Esc key");
		exitText.setPosition((SCREEN_WIDTH - exitText.getGlobalBounds().width) / 2, 400);
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
                this->_data->machine.AddState( StateRef( new GameState( this->_data, _filename ) ), true );
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
	}

}


