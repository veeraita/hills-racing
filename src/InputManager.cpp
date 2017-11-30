#pragma once
#include "InputManager.hpp"

namespace Hills
{
	bool InputManager::IsSpriteClicked( sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window)
	{
		if( sf::Mouse::isButtonPressed( button ) )
		{
			sf::IntRect playButtonRect( object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height );

			if( playButtonRect.contains( sf::Mouse::getPosition( window ) ) )
			{
				return true;
			}
		}
		return false;
	}

	sf::Vector2i InputManager::GetMousePosition( sf::RenderWindow &window )
	{
		return sf::Mouse::getPosition( window );
	}

	/*bool IsLeftClicked( sf::Sprite object, sf::Keyboard::Left, sf::RenderWindow &window)
	{

	}

	bool IsRightClicked( sf::Sprite object, sf::Keyboard::Right, sf::RenderWindow &window)
	{

	}

	bool IsUpClicked( sf::Sprite object, sf::Keyboard::Up, sf::RenderWindow &window)
	{

	}

	bool IsDownClicked( sf::Sprite object, sf::Keyboard::Down, sf::RenderWindow &window)
	{

	}*/


}
