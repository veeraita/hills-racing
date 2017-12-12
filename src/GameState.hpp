#pragma once

#include <SFML/Graphics.hpp>
#include "Level.hpp"
#include "State.hpp"
#include "Game.hpp"
#include "Car.hpp"

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
			b2World world;
			sf::Sprite _background;
			Level *level;
			Car *car;
			sf::View view;
			sf::Clock clock;
	};
}
