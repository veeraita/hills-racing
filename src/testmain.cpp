#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "testcar.cpp"
#include <cstdio>
#include <iostream>
#include <vector>
/*======================== GLOBALS ======================================================*/
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 1024
#define SCALE 30

/*======================== HEADERS ======================================================*/
void CreateCircle(b2World& world, int MouseX, int MouseY);
void CreateGround( b2World& world, float X, float Y, float angle );
void CreateCar( b2World& world, int MouseX, int MouseY );
std::vector<float> GenerateTerrain( float factor, float roughness );

/*======================== MAIN =========================================================*/
int main()
{
/*======================== PREPARE THE WINDOW AND B2WORLD ===============================*/
  sf::RenderWindow window( sf::VideoMode( SCREEN_WIDTH, SCREEN_HEIGHT ), "SFML Physics Testing with Box2D" );
  window.setFramerateLimit( 60 );
  b2Vec2 gravity( 0.0f, 8.0f );
  b2World world( gravity );

/*========================= PREPARE THE TEXTURES =========================================*/
  sf::Texture _chassistexture;
  sf::Texture _wheeltexture;
  sf::Texture _groundtexture;
  _chassistexture.loadFromFile( "Resources/car.png" );
  _wheeltexture.loadFromFile( "Resources/wheel.png" );
  _groundtexture.loadFromFile( "Resources/groundtex.png" );

/*========================== PREPARE SPRITES =============================================*/
  sf::Sprite _chassissprite;
  sf::Sprite _wheelsprite1;
  sf::Sprite _wheelsprite2;
  sf::Sprite _groundsprite;
  sf::Sprite WheelSprite;
  WheelSprite.setTexture( _wheeltexture );
  _chassissprite.setTexture( _chassistexture );
  _wheelsprite1.setTexture( _wheeltexture );
  _wheelsprite2.setTexture( _wheeltexture );
  _groundsprite.setTexture( _groundtexture );
  _chassissprite.setScale( 0.33f, 0.33f );
  _wheelsprite1.setScale( 0.33f, 0.33f );
  _wheelsprite2.setScale( 0.33f, 0.33f );

/*========================= PREPARE THE GROUND ===========================================*/
  CreateGround( world, 0, 1000, 0 );
  CreateGround( world, 249, 1000, 0 );
  CreateGround( world, 498, 1000, 0 );
  CreateGround( world, 747, 1000, 0 );
  CreateGround( world, 996, 1000, 0 );
  Testcar* car = new Testcar( world, 139, 842 );
/*========================= GAME LOOP BEGINS =============================================*/
  while( window.isOpen() )
  {
/*========================= EVENT POLLING ================================================*/
    sf::Event event;
		while ( window.pollEvent( event ) )
		{
			if ( sf::Event::Closed == event.type )
			{
				window.close();
			}
      if ( event.type == sf::Event::KeyPressed )
      {
          if(event.key.code == sf::Keyboard::Space)
          {
            int MouseX = sf::Mouse::getPosition(window).x;
            int MouseY = sf::Mouse::getPosition(window).y;
            std::cout << sf::Mouse::getPosition(window).x << std::endl;
            std::cout << sf::Mouse::getPosition(window).y << std::endl;
          }
          if( event.key.code == sf::Keyboard::RShift )
          {
            int MouseX = sf::Mouse::getPosition(window).x;
            int MouseY = sf::Mouse::getPosition(window).y;
            CreateCircle( world, MouseX, MouseY );
          }
          car->Keyboard( event );
      }
		}

/*========================== ONE STEP FOR B2WORLD AND WINDOW ===================================*/
    world.Step( 1.0f/60.0f, 8, 3 );
    world.ClearForces();
    window.clear();

/*========================== DRAWING SPRITES ON B2BODIES =======================================*/
    for( b2Body* b = world.GetBodyList(); b != 0 ; b = b->GetNext() )
    {
      if( b->GetUserData() == "chassis" )
      {
        _chassissprite.setOrigin( _chassissprite.getGlobalBounds().width / 2, _chassissprite.getGlobalBounds().height / 2 );
        _chassissprite.setPosition(SCALE * b->GetPosition().x , SCALE * b->GetPosition().y );
        _chassissprite.setRotation( b->GetAngle() * 180/b2_pi );
        window.draw( _chassissprite );
      }
      else if( b->GetUserData() == "wheel1")
      {
        _wheelsprite1.setOrigin( _wheelsprite1.getGlobalBounds().width / 2, _wheelsprite1.getGlobalBounds().height / 2 );
        _wheelsprite1.setPosition( SCALE*b->GetPosition().x , SCALE*b->GetPosition().y );
        _wheelsprite1.setRotation( b->GetAngle()*180/b2_pi );
        window.draw( _wheelsprite1 );
      }
      else if( b->GetUserData() == "wheel2" )
      {
        _wheelsprite2.setOrigin( _wheelsprite2.getGlobalBounds().width / 2, _wheelsprite2.getGlobalBounds().height / 2 );
        _wheelsprite2.setPosition( SCALE*b->GetPosition().x , SCALE*b->GetPosition().y );
        _wheelsprite2.setRotation( b->GetAngle()*180/b2_pi );
        window.draw( _wheelsprite2 );
      }
      else if( b->GetUserData() == "Circle" )
      {
        WheelSprite.setOrigin( WheelSprite.getGlobalBounds().width / 2, WheelSprite.getGlobalBounds().height / 2 );
        WheelSprite.setPosition( b->GetPosition().x * SCALE, b->GetPosition().y * SCALE);
        WheelSprite.setRotation( b->GetAngle() * 180/b2_pi);
        window.draw( WheelSprite );
      }
      else if( b->GetUserData() == "Ground")
      {
        _groundsprite.setOrigin( _groundsprite.getLocalBounds().width / 2, _groundsprite.getLocalBounds().height / 2 );
        _groundsprite.setPosition( SCALE*b->GetPosition().x, SCALE*b->GetPosition().y );
        _groundsprite.setRotation( b->GetAngle()*180/b2_pi );
        window.draw( _groundsprite );
      }
    }
/*========================== SFML SETUP END =====================================================*/
  window.display();
  }
  return 0;
}

void CreateGround(b2World& world, float X, float Y, float angle)
{
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2( X/SCALE, Y/SCALE );
    BodyDef.type = b2_staticBody;
    BodyDef.angle = angle;
    BodyDef.userData = (void*)"Ground";
    b2Body* Body = world.CreateBody( &BodyDef );

    b2PolygonShape Shape;
    Shape.SetAsBox( (249.0f/2)/SCALE, (50.0f/2)/SCALE );
    b2FixtureDef FixtureDef;
    FixtureDef.density = 0.f;
    FixtureDef.shape = &Shape;
    Body->CreateFixture(&FixtureDef);
}

void CreateCircle(b2World& world, int MouseX, int MouseY)
{
    b2BodyDef BodyDef;
    BodyDef.type = b2_dynamicBody;
    BodyDef.position = b2Vec2(MouseX/SCALE, MouseY/SCALE);
    BodyDef.userData = (void*)"Circle";
    b2Body* Body = world.CreateBody(&BodyDef);

    b2CircleShape circle;
    circle.m_radius = 35.0f/SCALE;

    b2FixtureDef FixtureDef;
    FixtureDef.density = 2.0f;
    FixtureDef.friction = 2.0f;
    FixtureDef.restitution = 0.5f;

    FixtureDef.shape = &circle;

    Body->CreateFixture(&FixtureDef);
}

void debugDraw( b2World& world )
{
  b2Draw* debug;
  debug->SetFlags( b2Draw.e_shapeBit | b2Draw.e_jointBit );
  world.SetDebugDraw()
}
