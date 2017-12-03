#pragma once

#include <map>
#include <SFML/Graphics.hpp>

namespace Hills
{
	class AssetManager
	{
		public:
			AssetManager() { }
			~AssetManager() { }

			void LoadTexture( std::string name, std::string fileName, bool repeat = false );
			sf::Texture &GetTexture( std::string name );

			void LoadFont( std::string name, std::string fileName );
			sf::Font &GetFont( std::string name );

		private:
			//map-containerit, johon ladataan SFML-Texturet ja -fontit. Toimii avaimilla (python dictionary)
			std::map<std::string, sf::Texture> _textures;
			std::map<std::string, sf::Font> _fonts;
	};



}
