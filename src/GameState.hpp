#pragma once

#include <SFML/Graphics.hpp>
#include "Level.hpp"
#include "State.hpp"
#include "Game.hpp"
#include "Car.hpp"
#include <string>

namespace Hills
{
	class GameState : public State
	{
		public:
			GameState(GameDataRef data, std::string level_filename);
			void Init();
			void HandleInput();
			void Update( float dt );
			void Draw( float dt );
			sf::Vector2f getPrevPos();
            sf::Text getPoints();
		private:
			GameDataRef _data;
			b2World world;
			std::string _filename;
			sf::Sprite _background;
			Level *level;
			Car *car;
			sf::View view;
			sf::Clock clock;
			sf::Font timerFont;
			sf::Text timerText;
			sf::Text velocityText;
            int intPoints;
            sf::Text pointsText;
			sf::Vector2f prevPos;


	};
}
