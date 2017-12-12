#include "Level.hpp"
#include <Box2D/Box2D.h>
#include <random>

namespace Hills
{

    Level::Level( GameDataRef data, b2World& world, float factor, float roughness ) : _data(data), world(world)
    {
        b2Body* ground = NULL;
        
        //create physical ground and add it to the world
        b2BodyDef bd;
        ground = world.CreateBody(&bd);
        
        b2EdgeShape shape;
        
        b2FixtureDef fd;
		fd.shape = &shape;
		fd.density = 0.0f;
		fd.friction = 10.0f;
		
		//shape.Set(b2Vec2(-20.0f, 5.0f), b2Vec2(20.0f, 5.0f));
		ground->CreateFixture(&fd);
		
		//factor: magnitude of displacement
		//roughness: how much the displacement range is reducted (0.5 -> very smooth, 1.0 -> jagged)
		std::vector<float> points = GenerateTerrain( factor, roughness );
		unsigned int n = NUM_POINTS + 3;
		
		float x = 0.0f, y1 = 10.0f, dx = LEVEL_DX;
		
		//construct the terrain sprite from multiple quads
		_vertices.setPrimitiveType(sf::Quads); 
		//set the number of vertices (4 per quad)
		_vertices.resize( n * 4 );
		
		this->_data->assets.LoadTexture( "Land", LAND_FILEPATH );
		
		_leveltexture = this->_data->assets.GetTexture( "Land" );
		
		// create some flat ground at the start of the level
		for (unsigned int i = 0; i < 3; ++i)
		{
			float32 y = 10.0f;
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
			float32 y2 = 10.0f + points[i];
			std::cout << y2 << std::endl;
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
    }
    
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
            range = 15.0;
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
                    segments++;
                }
                range *= roughness;
            }
        }
        
        return points;
    }
    
    
    void Level::draw( sf::RenderTarget& target, sf::RenderStates states ) const
    {
        //apply texture
        states.texture = &_leveltexture;
        
        // draw the vertex array
        target.draw(_vertices, states);
    }

    
}




