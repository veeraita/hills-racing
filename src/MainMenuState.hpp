#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"


namespace Hills
{
	class MainMenuState : public State
	{
		public:
			MainMenuState(GameDataRef data);
			void Init();
			void HandleInput();
			void Update( float dt );
			void Draw( float dt );
		private:
			GameDataRef _data;
			sf::Sprite _background;
            sf::Sprite _title;
            sf::Sprite _button1;
            sf::Sprite _button2;
            sf::Sprite _button3;
            sf::View view;
			sf::Sprite _hsButton;
	};
}
