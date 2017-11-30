#pragma once

<<<<<<< HEAD
#include <SFML/Graphics.hpp>
=======
#include "lib/SFML/Graphics.hpp"
>>>>>>> d3b180d66d123383818ad60d1dfa6e64f0f6daa3
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
	};
}
