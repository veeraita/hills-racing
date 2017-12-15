#pragma once
#include <sstream>
#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "GameState.cpp"
#include "DEFINITIONS.hpp"
#include "HighscoreState.cpp"
#include "HighscoreState.hpp"
#include <iostream>


namespace Hills
{
	MainMenuState::MainMenuState( GameDataRef data ) : _data( data )
	{

	}

	void MainMenuState::Init()
    {
        this->_data->window.setView(view); // sets the view to the start
        this->_data->assets.LoadTexture( "Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH );
        this->_data->assets.LoadTexture( "Level 1", LEVEL1_BUTTON_FILEPATH );
        this->_data->assets.LoadTexture( "Level 2", LEVEL2_BUTTON_FILEPATH );
        this->_data->assets.LoadTexture( "Level 3", LEVEL3_BUTTON_FILEPATH );
		this->_data->assets.LoadTexture( "Highscore Button", HIGHSCORE_FILEPATH );
		
		this->_background.setTexture( this->_data->assets.GetTexture( "Main Menu Background") );
        this->_button1.setTexture( this->_data->assets.GetTexture( "Level 1") );
        this->_button2.setTexture( this->_data->assets.GetTexture( "Level 2") );
        this->_button3.setTexture( this->_data->assets.GetTexture( "Level 3") );
		this->_hsButton.setTexture( this->_data->assets.GetTexture("Highscore Button"));

        this->_button1.setPosition( ( SCREEN_WIDTH / 2 ) - ( this->_button1.getGlobalBounds().width / 2 ), 100);
        this->_button2.setPosition( ( SCREEN_WIDTH / 2 ) - ( this->_button2.getGlobalBounds().width / 2 ), 300);
        this->_button3.setPosition( ( SCREEN_WIDTH / 2 ) - ( this->_button3.getGlobalBounds().width / 2 ), 500);
		this->_hsButton.setPosition( ( SCREEN_WIDTH / 2 ) - ( this->_hsButton.getGlobalBounds().width / 2 ), 700 );
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
        }
        
        //Level 1 selected
        if ( this->_data->input.IsSpriteClicked( this->_button1, sf::Mouse::Left, this->_data->window ) )
        {
            this->_data->machine.AddState( StateRef( new GameState( this->_data, LEVEL1_FILEPATH ) ), true );
            std::ofstream recentlevel;
            recentlevel.open("recentlevel.txt");
            recentlevel << 1 << std::endl;
            recentlevel.close();
        }
        
        //Level 2 selected
        if ( this->_data->input.IsSpriteClicked( this->_button2, sf::Mouse::Left, this->_data->window ) )
        {
            this->_data->machine.AddState( StateRef( new GameState( this->_data, LEVEL2_FILEPATH ) ), true );
            std::ofstream recentlevel;
            recentlevel.open("recentlevel.txt");
            recentlevel << 2 << std::endl;
            recentlevel.close();
        }
        
        //Level 3 selected
        if ( this->_data->input.IsSpriteClicked( this->_button3, sf::Mouse::Left, this->_data->window ) )
        {
            this->_data->machine.AddState( StateRef( new GameState( this->_data, LEVEL3_FILEPATH ) ), true );
            std::ofstream recentlevel;
            recentlevel.open("recentlevel.txt");
            recentlevel << 3 << std::endl;
            recentlevel.close();
        }
        
        //Go to High Scores state
		if ( this->_data->input.IsSpriteClicked( this->_hsButton, sf::Mouse::Left, this->_data->window ) )
		{
			this->_data->machine.AddState( StateRef( new HighscoreState( this->_data ) ), true );
		}
	}

	void MainMenuState::Update( float dt )
	{

	}

	void MainMenuState::Draw( float dt )
    {
        this->_data->window.clear(sf::Color::Red);
		this->_data->window.draw( this->_background );
        this->_data->window.draw( this->_button1 );
        this->_data->window.draw( this->_button2 );
        this->_data->window.draw( this->_button3 );
		this->_data->window.draw(this->_hsButton);
		this->_data->window.display();
	}

}
