#include <iostream>
#include "lib/SFML/Graphics.hpp"
#include "AssetManager.hpp"


namespace Hills
{
	//resource filepaths are defined in DEFINITIONS.hpp
	void AssetManager::LoadTexture( std::string name, std::string fileName, bool repeat)
	{
		sf::Texture tex;

		if ( tex.loadFromFile( fileName ) )
		{
		    if (repeat)
		    {
		        tex.setRepeated(true);
		    }

			this->_textures[name] = tex;
		}
		else
		{
			std::cout <<"Texture loading failed" << std::endl;
		}
	}
	

	sf::Texture &AssetManager::GetTexture( std::string name )
	{
		return this->_textures.at( name );
	}


	void AssetManager::LoadFont( std::string name, std::string fileName )
	{
		sf::Font font;

		if ( font.loadFromFile( fileName ) )
		{
			this->_fonts[name] = font;
		}
		
		else
		{
			std::cout <<"Font loading failed" << std::endl;
		}
	}
	

	sf::Font &AssetManager::GetFont( std::string name )
	{
		return this->_fonts.at( name );
	}
}


