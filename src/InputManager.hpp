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
//			bool IsLeftClicked( sf::Sprite object, sf::Keyboard::Left, sf::RenderWindow &window);
//			bool IsRightClicked( sf::Sprite object, sf::Keyboard::Right, sf::RenderWindow &window);
//			bool IsUpClicked( sf::Sprite object, sf::Keyboard::Up, sf::RenderWindow &window);
//			bool IsDownClicked( sf::Sprite object, sf::Keyboard::Down, sf::RenderWindow &window);
			sf::Vector2i GetMousePosition( sf::RenderWindow &window );
	};
}
