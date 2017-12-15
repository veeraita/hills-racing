#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Level.hpp"
#include "State.hpp"
#include "Game.hpp"
#include "Car.hpp"
#include <string>

namespace Hills
{
	class GameState : public State
	{
		public:
			GameState( GameDataRef data, std::string level_filename );
			//prevent copying
			GameState( const GameState& ) = delete;
			GameState& operator= (const GameState&) = delete;
			~GameState();
			void Init();
			void HandleInput();
			void Update( float dt );
			void Draw( float dt );
			sf::Vector2f getPrevPos();
            sf::Text getPoints();
		private:
			GameDataRef _data;
			b2World world;
			std::string _filename;
			sf::Sprite _background;
			Level *level;
			Car *car;
			sf::View view;
			sf::Clock clock;
			sf::Text timerText;
			sf::Text velocityText;
			sf::Text angleText;
            int intPoints = 0;
            sf::Text pointsText;
			sf::Text pointsNumber;
			sf::Vector2f prevPos;
			//AUDIO
			sf::SoundBuffer applauseBuffer;
			sf::SoundBuffer driveBuffer;
			sf::SoundBuffer buttonBuffer;
			sf::SoundBuffer engineBuffer;
			sf::SoundBuffer gameoverBuffer;
			sf::SoundBuffer musicBuffer;
			sf::Sound applauseSound;
			sf::Sound driveSound;
			sf::Sound buttonSound;
			sf::Sound engineSound;
			sf::Sound gameoverSound;
			sf::Sound music;

	};
}
