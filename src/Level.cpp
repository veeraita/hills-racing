#include "Level.hpp"
#include <Box2D/Box2D.h>

namespace Hills
{

    Level::Level( GameDataRef data ) : _data(data)
    {
        b2Vec2 gravity(0.0f, -9.8f);
        b2World world(gravity);
        b2Body* ground = NULL;

        b2BodyDef bd;
        ground = world.CreateBody(&bd);
        
        b2EdgeShape shape;
        
        b2FixtureDef fd;
		fd.shape = &shape;
		fd.density = 0.0f;
		fd.friction = 0.6f;
		
		shape.Set(b2Vec2(-20.0f, 0.0f), b2Vec2(20.0f, 0.0f));
		ground->CreateFixture(&fd);
		
		float32 hs[10] = {0.25f, 1.0f, 4.0f, 0.0f, 0.0f, -1.0f, -2.0f, -2.0f, -1.25f, 0.0f};

		float32 x = 0.0f, y1 = 10.0f, dx = 5.0f;
		
		_vertices.setPrimitiveType(sf::Quads); 
		//set the number of vertices (4 per quad)
		_vertices.resize( 10 * 4 );
		
		this->_data->assets.LoadTexture( "Land", LAND_FILEPATH );
		
		_leveltexture = this->_data->assets.GetTexture( "Land" );
		
		for (int32 i = 0; i < 10; ++i)
		{
			float32 y2 = y1 + hs[i];
			shape.Set(b2Vec2(x, y1), b2Vec2(x + dx, y2));
			ground->CreateFixture(&fd);

            // get a pointer to the current quad
            sf::Vertex* quad = &_vertices[ i * 4];
            //std::cout << x << std::endl;
            // define its 3 corners
            quad[0].position = sf::Vector2f(x * SCALE, SCREEN_HEIGHT);
            quad[1].position = sf::Vector2f((x + dx) * SCALE, SCREEN_HEIGHT);
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
    
    void Level::MoveLevel( )
    {

    }
    
    void Level::draw( sf::RenderTarget& target, sf::RenderStates states ) const
    {
        //apply texture
        states.texture = &_leveltexture;
        
        // draw the vertex array
        target.draw(_vertices, states);
    }

    
}




