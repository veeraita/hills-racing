#pragma once

#include "lib/SFML/Graphics.hpp"

namespace Hills
{
	class InputManager
	{
		public:
			InputManager() { }
			~InputManager() { }
			
			bool IsSpriteClicked( sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window);
//			bool IsLeftPressed( sf::Sprite object, sf::Keyboard::Left, sf::RenderWindow &window);
//			bool IsRightPressed( sf::Sprite object, sf::Keyboard::Right, sf::RenderWindow &window);
//			bool IsUpPressed( sf::Sprite object, sf::Keyboard::Up, sf::RenderWindow &window);
//			bool IsDownPressed( sf::Sprite object, sf::Keyboard::Down, sf::RenderWindow &window);
			sf::Vector2i GetMousePosition( sf::RenderWindow &window );
	};
}
