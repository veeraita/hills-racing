#include <iostream>
#include "lib/SFML/Graphics.hpp"
#include "AssetManager.hpp"


//AssetManager säilyttää ja käsittelee kaikkia kuvia, spriteja ym. ettei niitä tarvitse ladata useasti
namespace Hills
{
	//LoadTexture lataa kuvan fileNamen perusteella mappiin. Avaimena toimii std::string name
	//fileName löytyy valmiiksi DEFINITIONS.hpp:sta, jonne kirjataan kaikki resurssien FILEPATH:t!!
	//std::string namen voi heittää miksi huvittaa
	void AssetManager::LoadTexture( std::string name, std::string fileName )
	{
		//aluksi luodaan sfml-texture-muuttuja tex
		sf::Texture tex;

		//yritetään ladata sinne sfml-loadFromFile-funktiolla kuva tiedostosta
		if ( tex.loadFromFile( fileName ) )
		{
			//Jos lataus onnistuu asetetaan se mappiin avaimella: name
			this->_textures[name] = tex;
		}
		else
		{
			std::cout <<"vituiks mäni, ei latautunu mappiin" << std::endl;
		}
	}

	//GetTexture palautaa mapista halutun Texturen. Tämä toteutetaan aina LoadTexturen jälkeen koodissa
	//Esim. ...State.cpp-filuissa
	sf::Texture &AssetManager::GetTexture( std::string name )
	{
		return this->_textures.at( name );
	}

	//Sama kuin LoadTexture, mutta nyt kyseessä fontti.
	void AssetManager::LoadFont( std::string name, std::string fileName )
	{
		sf::Font font;

		if ( font.loadFromFile( fileName ) )
		{
			this->_fonts[name] = font;
		}
	}

	sf::Font &AssetManager::GetFont( std::string name )
	{
		return this->_fonts.at( name );
	}
}

//Tänne toteutetaan samalla logiikalla audiot
