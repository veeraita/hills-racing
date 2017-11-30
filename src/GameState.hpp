#pragma once
#include <SFML/Graphics.hpp>
#include "Land.hpp"
#include "State.hpp"
#include "Game.hpp"

namespace Hills
{
	class GameState : public State
	{
		public:
			GameState(GameDataRef data);
			void Init();
			void HandleInput();
			void Update( float dt );
			void Draw( float dt );
		private:
			GameDataRef _data;
			sf::Sprite _background;
			
			Land *land;
			
			sf::Clock clock;
	};
}
