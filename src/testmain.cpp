#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "testcar.cpp"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <vector>
#include "b2GLDraw.h"
#include "b2GLDraw.cpp"
/*======================== GLOBALS ======================================================*/
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 1024
#define SCALE 30

/*======================== HEADERS ======================================================*/
void CreateCircle(b2World& world, int MouseX, int MouseY);
void CreateGround( b2World& world, float X, float Y, float angle );
void CreateCar( b2World& world, int MouseX, int MouseY );
b2Vec2 findCentroid( std::vector<b2Vec2> vs, unsigned count );
void drawHills( b2World& world, int numbeOfHills, int pixelStep );


/*======================== MAIN =========================================================*/
int main()
{
/*======================== PREPARE THE WINDOW AND B2WORLD ===============================*/
  sf::RenderWindow window( sf::VideoMode( SCREEN_WIDTH, SCREEN_HEIGHT ), "SFML Physics Testing with Box2D" );
  window.setFramerateLimit( 60 );
  b2Vec2 gravity( 0.0f, 8.0f );
  b2World world( gravity );
  /*====================== DEBUG DRAWING MODE ============================================*/
  b2GLDraw debugDrawInstance(window);
  world.SetDebugDraw( &debugDrawInstance );
  uint32 flags = 0;
  flags += b2Draw::e_shapeBit;
  flags += b2Draw::e_jointBit;
  //flags += b2Draw::e_pairBit;
  flags += b2Draw::e_centerOfMassBit;
  //flags += b2Draw::e_aabbBit;
  debugDrawInstance.SetFlags( flags );

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
  // CreateGround( world, 0, 1000, 0 );
  // CreateGround( world, 249, 1000, 0 );
  // CreateGround( world, 498, 1000, 0 );
  // CreateGround( world, 747, 1000, 0 );
  // CreateGround( world, 996, 1000, 0 );
  drawHills( world, 2, 10 );
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
      // if( b->GetUserData() == "chassis" )
      // {
      //   _chassissprite.setOrigin( _chassissprite.getGlobalBounds().width / 2, _chassissprite.getGlobalBounds().height / 2 );
      //   _chassissprite.setPosition(SCALE * b->GetWorldCenter().x , SCALE * b->GetWorldCenter().y );
      //   _chassissprite.setRotation( b->GetAngle() * 180/b2_pi );
      //   window.draw( _chassissprite );
      // }
      // else if( b->GetUserData() == "wheel1")
      // {
      //   _wheelsprite1.setOrigin( _wheelsprite1.getGlobalBounds().width / 2, _wheelsprite1.getGlobalBounds().height / 2 );
      //   _wheelsprite1.setPosition( (SCALE*b->GetWorldCenter().x)-11.66f , (SCALE*b->GetWorldCenter().y)-11.66f );
      //   _wheelsprite1.setRotation( b->GetAngle()*180/b2_pi );
      //   window.draw( _wheelsprite1 );
      // }
      // else if( b->GetUserData() == "wheel2" )
      // {
      //   _wheelsprite2.setOrigin( _wheelsprite2.getGlobalBounds().width / 2, _wheelsprite2.getGlobalBounds().height / 2 );
      //   _wheelsprite2.setPosition( (SCALE*b->GetWorldCenter().x)-11.66f , (SCALE*b->GetWorldCenter().y)-11.66f );
      //   _wheelsprite2.setRotation( b->GetAngle()*180/b2_pi );
      //   window.draw( _wheelsprite2 );
      // }
      if( b->GetUserData() == "Circle" )
      {
        WheelSprite.setOrigin( WheelSprite.getGlobalBounds().width / 2, WheelSprite.getGlobalBounds().height / 2 );
        WheelSprite.setPosition( (b->GetWorldCenter().x*SCALE), b->GetWorldCenter().y*SCALE );
        WheelSprite.setRotation( b->GetAngle() * 180/b2_pi);
        window.draw( WheelSprite );
      }
      else if( b->GetUserData() == "Ground")
      {
        _groundsprite.setOrigin( _groundsprite.getLocalBounds().width / 2, _groundsprite.getLocalBounds().height / 2 );
        _groundsprite.setPosition( SCALE*b->GetWorldCenter().x, SCALE*b->GetWorldCenter().y );
        _groundsprite.setRotation( b->GetAngle()*180/b2_pi );
        window.draw( _groundsprite );
      }
    }
/*========================== SFML SETUP END =====================================================*/
  world.DrawDebugData();
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

void drawHills( b2World& world, int numbeOfHills, int pixelStep )
{
  srand (time(NULL));
  int hillStartY = 24+( rand()%5+1 )*200; //setup y-coord for the start
  int hillWidth = 1024/numbeOfHills;
  int hillSliceWidth = hillWidth/pixelStep;
  std::vector<b2Vec2> hillVector;
  for ( unsigned i = 0; i < numbeOfHills; i++ )
  {
    int randomHeight = ( rand()%5+1 )*100;
    if( i != 0 )
    {
      hillStartY-=randomHeight; //This is done so that all the hills wont start at the same Y-coord
    }
    for( unsigned j = 0; j < hillSliceWidth; j++ )
    {
      hillVector.push_back( b2Vec2( ( j*pixelStep+hillWidth*i )/SCALE , 1024/SCALE  ) );
      hillVector.push_back( b2Vec2( ( j*pixelStep+hillWidth*i )/SCALE , ( hillStartY+randomHeight*cos( 2*b2_pi/hillSliceWidth*j ) )/SCALE ) );
      hillVector.push_back( b2Vec2( ( (j+1)*pixelStep+hillWidth*i )/SCALE, ( hillStartY+randomHeight*cos( 2*b2_pi/hillSliceWidth*(j+1) ) )/SCALE ) );
      hillVector.push_back( b2Vec2( ( (j+1)*pixelStep+hillWidth*i )/SCALE, 1024/SCALE ) );

      b2BodyDef sliceBody;
      b2Vec2 center = findCentroid( hillVector, hillVector.size() );
      sliceBody.position.Set( center.x, center.y );
      for( unsigned t = 0; t < hillVector.size(); t++ )
      {
        hillVector[t] -= center;
      }
      b2PolygonShape slicePolygon;
      slicePolygon.SetAsVector( hillVector, 4 );
      b2FixtureDef sliceFixture;
      sliceFixture.shape = &slicePolygon;
      b2Body* worldSlice = world.CreateBody( &sliceBody );
      worldSlice->CreateFixture( &sliceFixture );
    }
    hillStartY = hillStartY+randomHeight;
  }
}

b2Vec2 findCentroid( std::vector<b2Vec2> vs, unsigned count )
{
  b2Vec2 c;
  float area = 0.0;
  float p1X = 0.0;
  float p1Y = 0.0;
  float inv3 = 1.0/3.0;
  for( unsigned i = 0; i < count; i++ )
  {
    b2Vec2 p2 = vs[i];
    b2Vec2 p3 = (i+1 < count) ? vs[i+1] : vs[0];
    float e1X = p2.x-p1X;
    float e1Y = p2.y-p1Y;
    float e2X = p3.x-p1X;
    float e2Y = p3.y-p1Y;
    float D = ( e1X * e2Y - e1Y * e2X );
    float triangleArea = 0.5*D;
    area+=triangleArea;
    c.x += triangleArea * inv3 * ( p1X + p2.x + p3.x );
    c.y += triangleArea * inv3 * ( p1Y + p2.y + p3.y );
  }
  c.x*=1.0/area;
  c.y*=1.0/area;
  return c;
}
