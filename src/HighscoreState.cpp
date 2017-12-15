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
		this->_data->assets.LoadTexture( "Splash State Background", MAIN_MENU_BACKGROUND_FILEPATH );
		this->_background.setTexture( this->_data->assets.GetTexture( "Splash State Background") );
		this->_data->assets.LoadTexture( "Exit Button", EXIT_FILEPATH );
		this->_exitButton.setTexture(this->_data->assets.GetTexture("Exit Button"));
		this->_data->assets.LoadFont("Game font", FONT_FILEPATH);

        std::vector<int> scoreVectorL1;
        std::string oneScoreL1;
        std::ifstream allScoresL1;
        std::stringstream convertL1;
        std::vector<int> topScoresL1;
        int tmpL1;

        allScoresL1.open("allscoreslevel1.txt",std::ios::out |std::ios::app);
        
        if(!allScoresL1)
        {
            std::cerr << "Error opening the file" << std::endl;
        }

        while(!allScoresL1.eof())
		{
            std::getline(allScoresL1,oneScoreL1);
            convertL1 << oneScoreL1;
            convertL1 >> tmpL1;
            scoreVectorL1.push_back(tmpL1);
            convertL1.str("");
            convertL1.clear();
		}
		
        allScoresL1.close();
        scoreVectorL1.pop_back();
        int sizeL1 = scoreVectorL1.size();
        int top1L1 = 0, top2L1 = 0, top3L1 = 0;
        
        if(sizeL1 > 0)
        {
            std::sort (scoreVectorL1.begin(),scoreVectorL1.end());
            if(sizeL1 >= 3)
            {
                top1L1 = scoreVectorL1[sizeL1-1];
                top2L1 = scoreVectorL1[sizeL1-2];
                top3L1 = scoreVectorL1[sizeL1-3];
            }

            if(sizeL1 == 2)
            {
                top1L1 = scoreVectorL1[sizeL1-1];
                top2L1 = scoreVectorL1[sizeL1-2];
            }

            if(sizeL1 == 1)
            {
                top1L1 = scoreVectorL1[sizeL1-1];
            }
        }


        scores1.setFont(this->_data->assets.GetFont("Game font"));
        scores1.setCharacterSize(50);
        scores1.setString("Level1 Highscores\n#1 " + std::to_string(top1L1) + "\n#2 " + std::to_string(top2L1) + "\n#3 " + std::to_string(top3L1));
        scores1.setPosition((SCREEN_WIDTH - scores1.getGlobalBounds().width)/2, 100);


        std::vector<int> scoreVectorL2;
        std::string oneScoreL2;
        std::ifstream allScoresL2;
        std::stringstream convertL2;
        std::vector<int> topScoresL2;
        int tmpL2;


        allScoresL2.open("allscoreslevel2.txt",std::ios::out |std::ios::app);
        if(!allScoresL2)
        {
            std::cerr << "Error opening the file" << std::endl;
        }

        while(!allScoresL2.eof())
        {
                std::getline(allScoresL2,oneScoreL2);
                convertL2 << oneScoreL2;
                convertL2 >> tmpL2;
                scoreVectorL2.push_back(tmpL2);
                convertL2.str("");
                convertL2.clear();
        }
        allScoresL2.close();
        scoreVectorL2.pop_back();
        int sizeL2 = scoreVectorL2.size();
        int top1L2 = 0, top2L2 = 0, top3L2 = 0;
        if(sizeL2 > 0)

        {
            std::sort (scoreVectorL2.begin(),scoreVectorL2.end());
            if(sizeL2 >= 3)
            {
                top1L2 = scoreVectorL2[sizeL2-1];
                top2L2 = scoreVectorL2[sizeL2-2];
                top3L2 = scoreVectorL2[sizeL2-3];
            }

            if(sizeL2 == 2)
            {
                top1L2 = scoreVectorL2[sizeL2-1];
                top2L2 = scoreVectorL2[sizeL2-2];
            }

            if(sizeL2 == 1)
            {
                top1L2 = scoreVectorL2[sizeL2-1];
            }
        }


        scores2.setFont(this->_data->assets.GetFont("Game font"));
        scores2.setCharacterSize(50);
        scores2.setString("Level2 Highscores\n#1 " + std::to_string(top1L2) + "\n#2 " + std::to_string(top2L2) + "\n#3 " + std::to_string(top3L2));
        scores2.setPosition((SCREEN_WIDTH - scores2.getGlobalBounds().width)/2, 400);


        std::vector<int> scoreVectorL3;
        std::string oneScoreL3;
        std::ifstream allScoresL3;
        std::stringstream convertL3;
        std::vector<int> topScoresL3;
        int tmpL3;

        allScoresL3.open("allscoreslevel3.txt",std::ios::out |std::ios::app);
        
        if(!allScoresL3)
        {
            std::cerr << "Error opening the file" << std::endl;
        }

        while(!allScoresL3.eof())
        {
            std::getline(allScoresL3,oneScoreL3);
            convertL3 << oneScoreL3;
            convertL3 >> tmpL3;
            scoreVectorL3.push_back(tmpL3);
            convertL3.str("");
            convertL3.clear();
        }
        
        allScoresL3.close();
        scoreVectorL3.pop_back();
        int sizeL3 = scoreVectorL3.size();
        int top1L3 = 0, top2L3 = 0, top3L3 = 0;
        
        if(sizeL3 > 0)
        {
            std::sort (scoreVectorL3.begin(),scoreVectorL3.end());
            
            if(sizeL3 >= 3)
            {
                top1L3 = scoreVectorL3[sizeL3-1];
                top2L3 = scoreVectorL3[sizeL3-2];
                top3L3 = scoreVectorL3[sizeL1-3];
            }

            if(sizeL3 == 2)
            {
                top1L3 = scoreVectorL3[sizeL3-1];
                top2L3 = scoreVectorL3[sizeL3-2];
            }

            if(sizeL3 == 1)
            {
                top1L3 = scoreVectorL3[sizeL3-1];
            }
        }

        scores3.setFont(this->_data->assets.GetFont("Game font"));
        scores3.setCharacterSize(50);
        scores3.setString("Level3 Highscores\n#1 " + std::to_string(top1L3) + "\n#2 " + std::to_string(top2L3) + "\n#3 " + std::to_string(top3L3));
        scores3.setPosition((SCREEN_WIDTH - scores3.getGlobalBounds().width)/2, 700);
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
        this->_data->window.draw(scores1);
        this->_data->window.draw(scores2);
        this->_data->window.draw(scores3);
        this->_data->window.display();
	}

}


