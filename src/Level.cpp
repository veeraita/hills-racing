#include "Level.hpp"
#include <Box2D/Box2D.h>
#include <random>
#include <fstream>

namespace Hills
{

    Level::Level( GameDataRef data, b2World& world, std::string& filename ) : _data(data), world(world), filename(filename)
    {
        LoadTerrain(filename);
        CreateTerrain();
        CreateTokens();
        /*
        b2Body* ground = NULL;
        
        //create physical ground and add it to the world
        b2BodyDef bd;
        ground = world.CreateBody(&bd);
        
        b2EdgeShape shape;
        
        b2FixtureDef fd;
		fd.shape = &shape;
		fd.density = 0.0f;
		fd.friction = 0.6f*SCALE;
		
		//shape.Set(b2Vec2(-20.0f, 5.0f), b2Vec2(20.0f, 5.0f));
		//ground->CreateFixture(&fd);
		
		//factor: magnitude of displacement
		//roughness: how much the displacement range is reducted (0.5 -> very smooth, 1.0 -> jagged)
		std::vector<float> points = GenerateTerrain( factor, roughness );
		unsigned int n = NUM_POINTS + 3;
		
		float x = 0.0f, y1 = 5.0f, dx = LEVEL_DX;
		
		//construct the terrain sprite from multiple quads
		_vertices.setPrimitiveType(sf::Quads); 
		//set the number of vertices (4 per quad)
		_vertices.resize( n * 4 );
		
		this->_data->assets.LoadTexture( "Land", LAND_FILEPATH );
		
		_leveltexture = this->_data->assets.GetTexture( "Land" );
		
		// create some flat ground at the start of the level
		for (unsigned int i = 0; i < 3; ++i)
		{
			float32 y = 5.0f;
			shape.Set(b2Vec2(x, y), b2Vec2(x + dx, y));
			ground->CreateFixture(&fd);

            // get a pointer to the current quad
            sf::Vertex* quad = &_vertices[ i * 4];

            // define its 3 corners
            quad[0].position = sf::Vector2f(x * SCALE, SCREEN_HEIGHT * 2);
            quad[1].position = sf::Vector2f((x + dx) * SCALE, SCREEN_HEIGHT * 2);
            quad[2].position = sf::Vector2f((x + dx) * SCALE, SCREEN_HEIGHT - (y * SCALE));
            quad[3].position = sf::Vector2f(x * SCALE, SCREEN_HEIGHT - (y * SCALE));
            
            quad[0].texCoords = sf::Vector2f(0, 0);
            quad[1].texCoords = sf::Vector2f(50, 0);
            quad[2].texCoords = sf::Vector2f(50, 50);
            quad[3].texCoords = sf::Vector2f(0, 50);
            
			x += dx;
        
        }	
		
		for (unsigned int i = 3; i < n; ++i)
		{
			float32 y2 = 5.0f + points[i];
			std::cout << points[i] << std::endl;
			shape.Set(b2Vec2(x, y1), b2Vec2(x + dx, y2));
			ground->CreateFixture(&fd);

            // get a pointer to the current quad
            sf::Vertex* quad = &_vertices[ i * 4];

            // define its 3 corners
            quad[0].position = sf::Vector2f(x * SCALE, SCREEN_HEIGHT * 2);
            quad[1].position = sf::Vector2f((x + dx) * SCALE, SCREEN_HEIGHT * 2);
            quad[2].position = sf::Vector2f((x + dx) * SCALE, SCREEN_HEIGHT - (y2 * SCALE));
            quad[3].position = sf::Vector2f(x * SCALE, SCREEN_HEIGHT - (y1 * SCALE));
            
            quad[0].texCoords = sf::Vector2f(0, 0);
            quad[1].texCoords = sf::Vector2f(50, 0);
            quad[2].texCoords = sf::Vector2f(50, 50);
            quad[3].texCoords = sf::Vector2f(0, 50);
            
            y1 = y2;
			x += dx;
        }
        */		
    }
    
    void Level::LoadTerrain(std::string& filename)
    {
        //std::vector<std::pair<float, float>> points;
        std::ifstream infile(filename);
        std::string line;
        
        while (std::getline(infile, line))
        {
            std::istringstream iss(line);
            float a; 
            float b;
            if (iss >> a ) 
            { 
                if (iss >> b ) 
                { 
                    _points.push_back(std::make_pair(a, b)); 
                }
                else
                {
                    _points.push_back(std::make_pair(a, -1));
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
		
		this->_data->assets.LoadTexture( "Land", LAND_FILEPATH );
		this->_data->assets.LoadTexture( "Finish", FINISH_LINE_FILEPATH, true );
		
		_leveltexture = this->_data->assets.GetTexture( "Land" );
		
		for (unsigned int i = 0; i < n; ++i)
		{
			float32 y2 = 5.0f + _points[i].first;
			
			//std::cout << points[i].first << std::endl;
			
			shape.Set(b2Vec2(x, y1), b2Vec2(x + dx, y2));
			ground->CreateFixture(&fd);

            // get a pointer to the current quad
            sf::Vertex* quad = &_vertices[ i * 4];

            // define its 3 corners
            quad[0].position = sf::Vector2f(x * SCALE, SCREEN_HEIGHT * 2);
            quad[1].position = sf::Vector2f((x + dx) * SCALE, SCREEN_HEIGHT * 2);
            quad[2].position = sf::Vector2f((x + dx) * SCALE, SCREEN_HEIGHT - (y2 * SCALE));
            quad[3].position = sf::Vector2f(x * SCALE, SCREEN_HEIGHT - (y1 * SCALE));
            
            quad[0].texCoords = sf::Vector2f(0, 0);
            quad[1].texCoords = sf::Vector2f(50, 0);
            quad[2].texCoords = sf::Vector2f(50, 50);
            quad[3].texCoords = sf::Vector2f(0, 50);
            
            y1 = y2;
			x += dx;
        }
        
        // create finish line 
        _finishLine.setSize(sf::Vector2f(50.0f, 300.0f));
        _finishLine.setTexture(&(this->_data->assets.GetTexture( "Finish" )));
        _finishLine.setTextureRect(sf::IntRect(0, 0, 50, 300));
        _finishLine.setPosition((x-4*dx)*SCALE, SCREEN_HEIGHT - ((_points[n-5].first+8.0f)*SCALE + 150.0f));
        //std::cout << _finishLine.getPosition().x << " " << _finishLine.getPosition().y << std::endl;
    }
    
    void Level::CreateTokens()
    {
        this->_data->assets.LoadTexture( "Token", TOKEN_FILEPATH );
        
        for (unsigned int i = 0; i < _points.size(); i++)
        {
            if (_points.at(i).second != -1 && _points.at(i).second > _points.at(i).first)
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

    
/*    
    std::vector<float> Level::GenerateTerrain( float factor, float roughness )
    {
        srand(time(NULL));
        
        float range;
        std::vector<float> points;
        
        for (int i = 0; i < NUM_POINTS; i++)
        {
            points.push_back( 0.0 );
        }
        
        for (int p = 0; p < 50; p++)
        {
            range = 20.0;
            int segments = 1;
            for (int i = 0; i < (NUM_POINTS / pow(2, 2)); i++)
            {
                int segs = segments;
                for (int j = 0; j < segs; j++)
                {
                    //how many points are in a segment
                    int x = floor(NUM_POINTS / segs);
                    int start = (j * x) + 1;
                    int end = start + x;
                    if (i == 0)
                    {
                        end--;
                    }
                    float lo = -range;
                    float hi = +range;
                    float change = lo + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hi - lo)));

                    //find the midpoint of the segment
                    int center = ((end - start) / 2) + start;
                    //displace the midpoint by a random amount
                    points[center - 1] = (points[start] + points[end]) / 2;
                    points[center - 1] += change * factor;
                    if (points[center - 1] < 0.0f)
                    {
                        points[center - 1] = 0.0f;
                    }
                    else if (points[center - 1] > 10.0f)
                    {
                        points[center - 1] = 10.0f;
                    }
                    segments++;
                }
                range *= roughness;
            }
        }
        
        return points;
    }
*/    
    
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




