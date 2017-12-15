#pragma once

#include "lib/SFML/Graphics.hpp"
#include "State.hpp"
#include "Game.hpp"

namespace Hills
{
	class HighscoreState : public State
	{
		public:
			HighscoreState(GameDataRef data);
			void Init();
			void HandleInput();
			void Update( float dt );
			void Draw( float dt );
		private:
			GameDataRef _data;
			sf::Sprite _background;
			sf::Sprite _exitButton;
            sf::Text scores1;
            sf::Text scores2;
            sf::Text scores3;
			sf::Font hsFont;

	};
}
