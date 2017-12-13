#pragma once
#include <sstream>
#include "HighscoreState.hpp"
#include "MainMenuState.hpp"
#include "MainMenuState.cpp"
#include "DEFINITIONS.hpp"
#include <iostream>
#include <istream>

namespace Hills
{
	HighscoreState::HighscoreState( GameDataRef data) : _data( data )
	{

	}

	void HighscoreState::Init()
	{
		this->_data->assets.LoadTexture( "Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH );
		this->_background.setTexture( this->_data->assets.GetTexture( "Splash State Background") );
		this->_data->assets.LoadTexture( "Exit Button", EXIT_FILEPATH );
		this->_exitButton.setTexture(this->_data->assets.GetTexture("Exit Button"));
		std::string scores_string = "score1 \nscore2\nscore3";
		// std::ifstream is("testhighscores");
		// while(!is.eof())
		// {
		// 	std::getline(is,scores_string);
		// 	scores_string += '\n';
		// }
		// is.close();

		if(!hsFont.loadFromFile("Resources/KhmerOS.ttf"))
		{
			std::cerr << "No font file found!" << std::endl;
		}
		std::cout << scores_string << std::endl;
		scores.setFont(hsFont);
		scores.setCharacterSize(20);
		scores.setString(scores_string);
		scores.setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
	}

	void HighscoreState::HandleInput( )
	{
		sf::Event event;

		while ( this->_data->window.pollEvent( event ) )
		{
			if ( sf::Event::Closed == event.type )
			{
				this->_data->window.close();
			}

			if ( this->_data->input.IsSpriteClicked( this->_exitButton, sf::Mouse::Left, this->_data->window ) )
			{
				this->_data->machine.AddState( StateRef( new MainMenuState( this->_data ) ), true );
			}
		}
	}

	void HighscoreState::Update( float dt )
	{

	}

	void HighscoreState::Draw( float dt )
	{
		this->_data->window.clear(sf::Color::Red);
		this->_data->window.draw( this->_background );
		this->_data->window.draw(this->_exitButton);
		this->_data->window.draw(scores);
		this->_data->window.display();
	}

}
