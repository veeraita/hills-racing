#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace Hills
{
	class GameOverState : public State
	{
		public:
			GameOverState(GameDataRef data, std::string level_filename);
			void Init();
			void HandleInput();
			void Update( float dt );
			void Draw( float dt );
		private:
			GameDataRef _data;
            sf::Sprite _background;
            sf::View view;
			sf::Text score;
			sf::Font textFont;
			sf::Text exitText;
			sf::Text gameOver;
			std::string _filename;
	};
}
