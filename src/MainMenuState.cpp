#pragma once
#include <sstream>
#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "GameState.cpp"
#include "DEFINITIONS.hpp"
#include <iostream>


namespace Hills
{
	MainMenuState::MainMenuState( GameDataRef data ) : _data( data )
	{

	}

	void MainMenuState::Init()
	{
		this->_data->assets.LoadTexture( "Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH );
    //this->_data->assets.LoadTexture( "Game Title", GAME_TITLE_FILEPATH );
    this->_data->assets.LoadTexture( "Play Button", PLAY_BUTTON_FILEPATH );
		this->_data->assets.LoadTexture( "Highscore Button", HIGHSCORE_FILEPATH );
		this->_background.setTexture( this->_data->assets.GetTexture( "Main Menu Background") );
    //this->_title.setTexture( this->_data->assets.GetTexture( "Game Title") );
    this->_playButton.setTexture( this->_data->assets.GetTexture( "Play Button") );
		this->_hsButton.setTexture( this->_data->assets.GetTexture("Highscore Button"));
		this->_hsButton.setScale(0.5,0.5);

    //this->_title.setPosition( (SCREEN_WIDTH / 2)- ( this->_title.getGlobalBounds().width / 2 ), this->_title.getGlobalBounds().height / 2 );
    this->_playButton.setPosition( ( SCREEN_WIDTH / 2 ) - ( this->_playButton.getGlobalBounds().width / 2 ), ( SCREEN_HEIGHT / 2 ) - ( this->_playButton.getGlobalBounds().height)*2 );
		this->_hsButton.setPosition( ( SCREEN_WIDTH / 2 ) - ( this->_hsButton.getGlobalBounds().width / 2 ), ( SCREEN_HEIGHT / 2 ) - ( this->_hsButton.getGlobalBounds().height / 4 ) );
	}

	void MainMenuState::HandleInput()
	{
		sf::Event event;

		while ( this->_data->window.pollEvent( event ) )
		{
			if ( sf::Event::Closed == event.type )
			{
				this->_data->window.close();
			}

      if ( this->_data->input.IsSpriteClicked( this->_playButton, sf::Mouse::Left, this->_data->window ) )
      {
        this->_data->machine.AddState( StateRef( new GameState( this->_data ) ), true );
      }
		}


		// if ( this->_data->input.IsSpriteClicked( this->_hsButton, sf::Mouse::Left, this->_data->window ) )
		// {
		// 	this->_data->machine.AddState( StateRef( new HighscoreState( this->_data ) ), true );
		// }
	}

	void MainMenuState::Update( float dt )
	{

	}

	void MainMenuState::Draw( float dt )
	{
		this->_data->window.clear(sf::Color::Red);
		this->_data->window.draw( this->_background );
    //this->_data->window.draw( this->_title );
    this->_data->window.draw( this->_playButton );
		this->_data->window.draw(this->_hsButton);
		this->_data->window.display();
	}

}
