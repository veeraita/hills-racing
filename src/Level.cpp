#include "Level.hpp"
#include <Box2D/Box2D.h>
#include <random>
#include <fstream>
#include <string>

namespace Hills
{

    Level::Level( GameDataRef data, b2World& world, std::string filename ) : _data(data), world(world), _filename(filename)
    {
        LoadTerrain(filename);
        CreateTerrain();
        CreateTokens();
    }
    
    void Level::LoadTerrain(std::string& filename)
    {
        //read terrain coordinates from file
        std::ifstream infile(filename);
        std::string line;
        
        while (std::getline(infile, line))
        {
            std::istringstream iss(line);
            float y_ground; 
            float y_token;
            
            if (iss >> y_ground ) 
            { 
                if (iss >> y_token ) 
                { 
                    _points.push_back(std::make_pair(y_ground, y_token)); 
                }
                
                else
                {
                    _points.push_back(std::make_pair(y_ground, -99));
                }
            }
            
            else
            {
                break;
            }
        }
        //return points;
    }
    
    void Level::CreateTerrain()
    {
        b2Body* ground = NULL;
        
        //create physical ground and add it to the world
        b2BodyDef bd;
        ground = world.CreateBody(&bd);
        
        b2EdgeShape shape;
        
        b2FixtureDef fd;
		fd.shape = &shape;
		fd.density = 0.0f;
		fd.friction = 0.6f*SCALE;
        unsigned int n = _points.size();
		
		float x = 0.0f, y1 = 5.0f, dx = LEVEL_DX;
		
		//construct the terrain sprite from multiple quads
		_vertices.setPrimitiveType(sf::Quads); 
		//set the number of vertices (4 per quad)
		_vertices.resize( n * 4 );

        //============LOAD TEXTURES====================================================================
        this->_data->assets.LoadTexture( "Land", LAND_FILEPATH_1 );

        if("Levels/level2.txt" == _filename)
        {
            this->_data->assets.LoadTexture( "Land", LAND_FILEPATH_2 );
        }
        else if("Levels/level3.txt" == _filename)
        {
            this->_data->assets.LoadTexture( "Land", LAND_FILEPATH_3 );
        }

        this->_data->assets.LoadTexture( "Finish", FINISH_LINE_FILEPATH, true );
		
		_leveltexture = this->_data->assets.GetTexture( "Land" );
        _leveltexture.setRepeated(true);
		
		for (unsigned int i = 0; i < n; ++i)
		{
			float32 y2 = 5.0f + _points[i].first;
			
			shape.Set(b2Vec2(x, y1), b2Vec2(x + dx, y2));
			ground->CreateFixture(&fd);

            // get a pointer to the current quad
            sf::Vertex* quad = &_vertices[ i * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(x * SCALE, SCREEN_HEIGHT * 2);
            quad[1].position = sf::Vector2f((x + dx) * SCALE, SCREEN_HEIGHT * 2);
            quad[2].position = sf::Vector2f((x + dx) * SCALE, SCREEN_HEIGHT - (y2 * SCALE));
            quad[3].position = sf::Vector2f(x * SCALE, SCREEN_HEIGHT - (y1 * SCALE));
            
            quad[0].texCoords = sf::Vector2f(0, 0);
            quad[1].texCoords = sf::Vector2f(100, 0);
            quad[2].texCoords = sf::Vector2f(100, -1600);
            quad[3].texCoords = sf::Vector2f(0, -1600);
            
            y1 = y2;
			x += dx;
        }
        
        // create finish line 
        _finishLine.setSize(sf::Vector2f(50.0f, 300.0f));
        _finishLine.setTexture(&(this->_data->assets.GetTexture( "Finish" )));
        _finishLine.setTextureRect(sf::IntRect(0, 0, 50, 300));
        _finishLine.setPosition((x-4*dx)*SCALE, SCREEN_HEIGHT - ((_points[n-5].first+8.0f)*SCALE + 150.0f));
    }
    
    
    void Level::CreateTokens()
    {
        this->_data->assets.LoadTexture( "Token", TOKEN_FILEPATH );
        
        for (unsigned int i = 0; i < _points.size(); i++)
        {
            if (_points.at(i).second != -99 && _points.at(i).second > _points.at(i).first)
            {
                sf::Sprite token(this->_data->assets.GetTexture( "Token"));
                token.setPosition((i+1) * LEVEL_DX * SCALE, SCREEN_HEIGHT - (_points.at(i).second + 5.0f) * SCALE);
                //std::cout << token.getPosition().x << " " << token.getPosition().y << std::endl;
                _tokens.push_back(token);
            }
        }
    }
    
    sf::RectangleShape Level::getFinishSprite()
    {
        return _finishLine;
    }
    
    std::vector<sf::Sprite> Level::getTokens()
    {
        return _tokens;
    }
    
    int Level::getLevelLength()
    {
        return _points.size() * LEVEL_DX * SCALE;
    }
    
    void Level::deleteToken(unsigned int i)
    {
        _tokens.erase(_tokens.begin() + i);
    }

    void Level::draw( sf::RenderTarget& target, sf::RenderStates states ) const
    {
        //apply texture
        states.texture = &_leveltexture;
        
        // draw the vertex array
        target.draw(_vertices, states);
        
        // draw the tokens
        for (auto i = _tokens.begin(); i != _tokens.end(); i++)
        {
            target.draw(*i);
        }
    }
  
}




