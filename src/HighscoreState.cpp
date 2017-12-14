#pragma once
#include <sstream>
#include "HighscoreState.hpp"
#include "MainMenuState.hpp"
#include "MainMenuState.cpp"
#include "DEFINITIONS.hpp"
#include <iostream>
#include <istream>
#include <vector>
#include <fstream>
#include <algorithm>

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
		//std::string scores_string = "score1 \nscore2\nscore3";

		std::vector<int> scoreVector;
		std::string oneScore;
		std::ifstream allScores;
		std::stringstream convert;
		std::vector<int> topScores;
		int tmp;

		allScores.open("allscores.txt");

		while(!allScores.eof())
		{
			std::getline(allScores,oneScore);
			convert << oneScore;
			convert >> tmp;
			scoreVector.push_back(tmp);
			convert.str("");
			convert.clear();
		}
		allScores.close();
		std::sort (scoreVector.begin(),scoreVector.end());
		int size = scoreVector.size();
		int top1,top2,top3;
		top1 = scoreVector[size-1];
		top2 = scoreVector[size-2];
		top3 = scoreVector[size-3];



		if(!hsFont.loadFromFile("Resources/KhmerOS.ttf"))
		{
			std::cerr << "No font file found!" << std::endl;
		}
		std::cout << oneScore << std::endl;
		scores.setFont(hsFont);
		scores.setCharacterSize(20);
		scores.setString("Level1 Highscores\n#1 " + std::to_string(top1) + "\n#2 " + std::to_string(top2) + "\n#3 " + std::to_string(top3));
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
