#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "testcar.cpp"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <random>
#include <cmath>
#include <iostream>
#include <vector>
#include "b2GLDraw.h"
#include "b2GLDraw.cpp"
/*======================== GLOBALS ======================================================*/
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 1024
#define SCALE 30
std::vector<b2Body*> bodiesScheduledForRemoval;

/*======================== HEADERS ======================================================*/
void CreateCircle(b2World& world, int MouseX, int MouseY);
void CreateGround( b2World& world, float X, float Y, float angle );
void CreateCar( b2World& world, int MouseX, int MouseY );
double drawHills( b2World& world, float pixelStep, float xOffset, float yOffset );


/*======================== MAIN =========================================================*/
int main()
{
/*======================== PREPARE THE WINDOW AND B2WORLD ===============================*/
  sf::RenderWindow window( sf::VideoMode( SCREEN_WIDTH, SCREEN_HEIGHT ), "SFML Physics Testing with Box2D" );
  window.setFramerateLimit( 60 );
  b2Vec2 gravity( 0.0f, 9.8f );
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

  std::random_device rdd;
  std::default_random_engine generatorr( rdd() );
  std::uniform_real_distribution<double> distributionn( 0.8, 0.9 );
  double nextHill = distributionn( generatorr )*1024; //random hill's height
  double buildNextHillAt = 0.0; //when screen's x-pos is lower than this value, we'll buiuld another hill

  nextHill = drawHills( world, 30.0, 0, nextHill );
  nextHill = drawHills( world, 30.0, 1024, nextHill );
  Testcar* car = new Testcar( world, SCREEN_WIDTH/2, 700 );

/*========================= SETIING UP THE CAMERA VIEW FOR SCREEN SCROLLING ==============*/
  sf::View view;
  view.reset( sf::FloatRect( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT ) ); //cover the whole SCREEN
  view.setViewport( sf::FloatRect( 0, 0, 1.0f, 1.0f) );
  sf::Vector2f position( SCREEN_WIDTH/2, SCREEN_HEIGHT/2 );
  sf::Vector2f position2( SCREEN_WIDTH/2, SCREEN_HEIGHT/2 );
  int a = 0;
  int b = 2;
  //unsigned g = 0;

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
/*========================== MOVE THE VIEW AND BUILD A NEW HILL ================================*/
    for ( b2Body* currentBody = world.GetBodyList(); currentBody; currentBody = currentBody->GetNext() )
    {
      if( currentBody->GetUserData() == "chassis")
      {
        position.x = SCREEN_WIDTH/2 - currentBody->GetPosition().x*SCALE;
        position2.x = currentBody->GetPosition().x*SCALE;
        if( position.x <= buildNextHillAt )
        {
          buildNextHillAt -= 1024;
          a++;
          std::cout << "-------------------" << std::endl;
          std::cout << buildNextHillAt << std::endl;
          std::cout << a << std::endl;
          std::cout << "-------------------" << std::endl;
          nextHill = drawHills( world, 30.0, -buildNextHillAt+1024, nextHill );
        }
      }
      if( a > b )
      {
        b++;
        std::cout<<world.GetBodyCount()<<std::endl;
        // for( auto q = 0; q < bodiesScheduledForRemoval.size(); q++ )
        // {
        //   std::cout << bodiesScheduledForRemoval[q]->GetType() << std::endl;
        // }
        // for( unsigned int q = 0; q < 34; q++ )
        // {
        //   world.DestroyBody(bodiesScheduledForRemoval.back());
        //   bodiesScheduledForRemoval.pop_back();
        // }
        // for( unsigned int q = 0; q < 34; q++ )
        // {
        //   world.DestroyBody( bodiesScheduledForRemoval[q] );
        //   bodiesScheduledForRemoval.erase( bodiesScheduledForRemoval.begin(), bodiesScheduledForRemoval.begin()+33 );
        // }
        std::cout<<world.GetBodyCount()<<std::endl;
      }
      view.setCenter( position2 );
    }

/*========================== ONE STEP FOunsigned g = 0R B2WORLD AND WINDOW ===================================*/
    world.Step( 1.0f/60.0f, 8, 3 );
    world.ClearForces();
    window.setView( view );
    window.clear();

    // sf::Vector2f prevPos2 = getPrevPos();
    // sf::Vector2f pos = car->getChassisSprite().getPosition();
    // if (pos.x > SCREEN_WIDTH/2 && pos.x < level->getLevelLength() - SCREEN_WIDTH/2)
    // {
    //     if (pos.y <= SCREEN_HEIGHT - 10.0f*SCALE)
    //     {unsigned g = 0
    //         view.setCenter(pos.x, SCREEN_HEIGHT - 10.0f*SCALE);
    //     }
    //     else if (pos.y >=  SCREEN_HEIGHT)
    //     {
    //         view.setCenter(pos.x, SCREEN_HEIGHT);
    //     }
    //     else
    //     {
    //         view.setCenter(pos);
    //     }
    // }

/*========================== DRAWING SPRITES ON B2BODIES =======================================*/
    // for( b2Body* b = world.GetBodyList(); b != 0 ; b = b->GetNext() )
    // {
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
      // if( b->GetUserData() == "Circle" )
      // {
      //   WheelSprite.setOrigin( WheelSprite.getGlobalBounds().width / 2, WheelSprite.getGlobalBounds().height / 2 );
      //   WheelSprite.setPosition( (b->GetWorldCenter().x*SCALE), b->GetWorldCenter().y*SCALE );
      //   WheelSprite.setRotation( b->GetAngle() * 180/b2_pi);
      //   window.draw( WheelSprite );
      // }
      // else if( b->GetUserData() == "Ground")
      // {
      //   _groundsprite.setOrigin( _groundsprite.getLocalBounds().width / 2, _groundsprite.getLocalBounds().height / 2 );
      //   _groundsprite.setPosition( SCALE*b->GetWorldCenter().x, SCALE*b->GetWorldCenter().y );
      //   _groundsprite.setRotation( b->GetAngle()*180/b2_pi );
      //   window.draw( _groundsprite );
      // }
    // }
/*========================== SFML SETUP END =====================================================*/
  world.DrawDebugData();
  window.display();
  }
  return 0;
}

/*============================ DRAW HILLS LIKE IN TINY WINGS ==================================*/
double drawHills( b2World& world, float pixelStep, float xOffset, float yOffset )
{
      std::random_device rd;                                            //seed
      std::default_random_engine generator( rd() );                     //random engine (C++11)
      std::uniform_real_distribution<double> distribution( 0.2, 1.0 );//distribution between 0.25 - 0.7
      // double random = distribution( generator );                    //random number from the distribution

      double hillStartY = yOffset; //random*SCREEN_HEIGHT;              //setup the starting y-coordinate
      int hillWidth = SCREEN_WIDTH; //SCREEN_WIDTH/numberOfHills;       //setup the hillWidth in pixels
      int hillSliceNumber = hillWidth/pixelStep;                        //setup the number of slices we will divide one hill in
      std::vector<b2Vec2> hillVector;                                   //setup a container with vertex-coordinates of the slices
      double randomHeight = distribution( generator )*155;               //change this for different sized hills
      int k = 0;
      if( xOffset != 0)
      {
        hillStartY-=randomHeight;
      }
      // DEBUG OSTREAM
      std::cout << "hillStartY: " << hillStartY << std::endl;
      // std::cout << "hillWidth: " << hillWidth << std::endl;
      std::cout << "randomHeight: "<< randomHeight << std::endl;
      // //std::cout << "hillSliceNumber: " << hillSliceNumber << std::endl;
      // std::cout << "------------------" << std::endl;

      /*====================== CREATE THE HILLS =================================================*/
      // for ( unsigned i = 0; i < numberOfHills; i++ )
      // {
        // std::uniform_real_distribution<double> distribution( 0.05, 0.5 );
        // double randomHeight = distribution( generator )*50; //change this for different sized hills
        // std::cout << "randomHeight = " << randomHeight << std::endl;
        // if( i != 0 )
        // {
        //   hillStartY-=randomHeight;    //This is done so that all the hills wont start at the same Y-coord
        // }

        /*==================== CREATE THE COORDINATES FOR THE HILLS =============================*/
        // for( unsigned j = 0; j < hillSliceNumber; j++ )
        // {
          // hillVector.push_back( b2Vec2( ( j*pixelStep+hillWidth*i )/SCALE , SCREEN_HEIGHT/SCALE  ) );
          // hillVector.push_back( b2Vec2( ( j*pixelStep+hillWidth*i )/SCALE , ( hillStartY+randomHeight*cos( 2*b2_pi/hillSliceNumber*j ) )/SCALE ) );
          // hillVector.push_back( b2Vec2( ( (j+1)*pixelStep+hillWidth*i )/SCALE, ( hillStartY+randomHeight*cos( 2*b2_pi/hillSliceNumber*(j+1) ) )/SCALE ) );
          // hillVector.push_back( b2Vec2( ( (j+1)*pixelStep+hillWidth*i )/SCALE, SCREEN_HEIGHT/SCALE ) );

          // DEBUG OSTREAM
          // int l = 0;
          // std::cout << "hill round, j = " << j << std::endl;100
          // std::cout << "****"<< std::endl;
          // std::cout << "( j*pixelStep+hillWidth*i )/SCALE: " << ( j*pixelStep+hillWidth*i )/SCALE << std::endl;
          // std::cout << "****"<< std::endl;
          // std::cout << "( (j+1)*pixelStep+hillWidth*i  )/SCALE: " << ( (j+1)*pixelStep+hillWidth*i )/SCALE << std::endl;
          // std::cout << "****"<< std::endl;
          // std::cout << "b2Vec2( " << hillVector[l].x << ", " << hillVector[l].y << " )" << std::endl;
          // std::cout << "b2Vec2( " << hillVector[l+1].x << ", " << hillVector[l+1].y << " )" << std::endl;
          // std::cout << "b2Vec2( " << hillVector[l+2].x << ", " << hillVector[l+2].y << " )" << std::endl;
          // std::cout << "b2Vec2( " << hillVector[l+3].x << ", " << hillVector[l+3].y << " )" << std::endl;
          // std::cout << "vertices: [(" << hillVector[l].x << ", " << hillVector[l].y << "), (" << hillVector[l+1].x << ", " << hillVector[l+1].y << "), (" << hillVector[l+2].x <<", " << hillVector[l+2].y << "), (" << hillVector[l+3].x << ", " << hillVector[l+3].y << ")]" << std::endl;
          // std::cout << "----------------------" << std::endl;

          /*================== BOX2D SETUP FOR THE SLICES ======================================================*/

          // b2Vec2 vertices[2];
          // vertices[0].Set( hillVector[k].x , hillVector[k].y );
          // vertices[1].Set( hillVector[k+1].x, hillVector[k+1].y );
          // vertices[2].Set( hillVector[k+2].x, hillVector[k+2].y );
          // vertices[3].Set( hillVector[k+3].x, hillVector[k+3].y );
          // b2World& world, int numbeOfHills, float pixelStep
          // //DEBUG OSTREAM
          // std::cout << "round, j = " << j << std::endl;
          // std::cout << "*********************" << std::endl;
          // std::cout << "vertices[0] = b2Vec2(" << vertices[0].x << ", " << vertices[0].y << ")" << std::endl;
          // std::cout << "vertices[1] = b2Vec2(" << vertices[1].x << ", " << vertices[1].y << ")" << std::endl;
          // std::cout << "vertices[2] = b2Vec2(" << vertices[2].x << ", " << vertices[2].y << ")" << std::endl;
          // std::cout << "vertices[3] = b2Vec2(" << vertices[3].x << ", " << vertices[3].y << ")" << std::endl;
          // std::cout <// std::cout << "hill round, j = " << j << std::endl;
            // //std::cout << "****"<< std::endl;
            // std::cout << "x-coord1: " << ( j*pixelStep+xOffset )/SCALE << std::endl;
            // //std::cout << "****"<< std::endl;
            // std::cout << "x-coord2: " << ( (j+1)*pixelStep+xOffset )/SCALE << std::endl;
            // std::cout << "****"<< std::endl;
            // std::cout << "y-coord1: " << ( hillStartY+randomHeight*cos( 2*b2_pi/hillSliceNumber*j ) )/SCALE << std::endl;
            // std::cout << "y-coord2: " << ( hillStartY+randomHeight*cos( 2*b2_pi/hillSliceNumber*(j+1) ) )/SCALE << std::endl;
            // std::cout << "****"<< std::endl;< "*********************" << std::endl;
          //
          // /*================== FIND THE CENTROID OF THE SLICE =================*/
          // float width = vertices[3].x - vertices[0].x;
          // float boxHeight = ( vertices[1].y < vertices[2].y ) ? vertices[1].y : vertices[2].y;
          // float boxArea = width*boxHeight;
          // float triangleHeight = ( vertices[1].y < vertices[2].y ) ? vertices[2].y-vertices[1].y : vertices[1].y-vertices[2].y;
          // float triangleArea = (width*triangleHeight)/2.0;
          // float axBox = boxArea*(width/2.0f);
          // float ayBox = boxArea*(boxHeight/2.0f);
          // float axTriangle = triangleArea*(width/3.0f);
          // float ayTriangle = triangleArea*(triangleHeight/3.0f + boxHeight);
          // float sumOfAreas = triangleArea + boxArea;
          // float sumOfAx = axBox + axTriangle;
          // float sumOfAy = ayBox + ayTriangle;
          // float centroidY = sumOfAy/sumOfAreas;
          // float centroidX = sumOfAx/sumOfAreas;
          //
          // //DEBUG OSTRE// std::cout << "hill round, j = " << j << std::endl;
            // //std::cout << "****"<< std::endl;
            // std::cout << "x-coord1: " << ( j*pixelStep+xOffset )/SCALE << std::endl;
            // //std::cout << "****"<< std::endl;
            // std::cout << "x-coord2: " << ( (j+1)*pixelStep+xOffset )/SCALE << std::endl;
            // std::cout << "****"<< std::endl;
            // std::cout << "y-coord1: " << ( hillStartY+randomHeight*cos( 2*b2_pi/hillSliceNumber*j ) )/SCALE << std::endl;
            // std::cout << "y-coord2: " << ( hillStartY+randomHeight*cos( 2*b2_pi/hillSliceNumber*(j+1) ) )/SCALE << std::endl;
            // std::cout << "****"<< std::endl;AM// std::cout << "hill round, j = " << j << std::endl;
            // //std::cout << "****"<< std::endl;
            // std::cout <<// std::cout << "hill round, j = " << j << std::endl;
            // //std::cout << "****"<< std::endl;
            // std::cout << "x-coord1: " << ( j*pixelStep+xOffset )/SCALE << std::endl;
            // //std::cout << "****"<< std::endl;
            // std::cout << "x-coord2: " << ( (j+1)*pixelStep+xOffset )/SCALE << std::endl;
            // std::cout << "****"<< std::endl;
            // std::cout << "y-coord1: " << ( hillStartY+randomHeight*cos( 2*b2_pi/hillSliceNumber*j ) )/SCALE << std::endl;
            // std::cout << "y-coord2: " << ( hillStartY+randomHeight*cos( 2*b2_pi/hillSliceNumber*(j+1) ) )/SCALE << std::endl;
            // std::cout << "****"<< std::endl; "x-coord1: " << ( j*pixelStep+xOffset )/SCALE << std::endl;
            // //std::cout << "****"<< std::endl;
            // std::cout << "x-coord2: " << ( (j+1)*pixelStep+xOffset )/SCALE << std::endl;
            // std::cout << "****"<< std::endl;
            // std::cout << "y-coord1: " << ( hillStartY+randomHeight*cos( 2*b2_pi/hillSliceNumber*j ) )/SCALE << std::endl;
            // std::cout << "y-coord2: " << ( hillStartY+randomHeight*cos( 2*b2_pi/hillSliceNumber*(j+1) ) )/SCALE << std::endl;
            // std::cout << "****"<< std::endl;
          // std::cout << "round, j = " << j << std::endl;100
          // std::cout << "*********************" << std::endl;
          // std::cout << "width = " << width << std::endl;
          // std::cout << "boxHeight = " << boxHeight << std::endl;
          // std::cout << "triangleHeight = " << triangleHeight << std::endl;
          // std::cout << "centroidX = " << centroidX << std::endl;
          // std::cout << "centroidY = " << centroidY << std::endl;
          // std::cout << "*********************" << std::endl;
          // std::cout << "centroidX: " << centroidX << ", centroidY: " << centroidY << std::endl;
          // std::cout << "centroidY flipped: " << SCREEN_HEIGHT/SCALE-centroidY << std::endl;

          /*=================== DRAWING EDGESHAPES INSTEAD OF POLYGONS ======================================*/

          // hillVector.push_back( b2Vec2( ( j*pixelStep+hillWidth*i )/SCALE , ( hillStartY+randomHeight*cos( 2*b2_pi/hillSliceNumber*j ) )/SCALE ) );

          for( unsigned j = 0; j < hillSliceNumber; j++ )
          {
            hillVector.push_back( b2Vec2( ( j*pixelStep+xOffset )/SCALE , ( hillStartY+randomHeight*cos( 2*b2_pi/hillSliceNumber*j ) )/SCALE ) );
            hillVector.push_back( b2Vec2( ( (j+1)*pixelStep+xOffset )/SCALE, ( hillStartY+randomHeight*cos( 2*b2_pi/hillSliceNumber*(j+1) ) )/SCALE ) );

            // DEBUG OSTREAM
            //int l = 0;
            // std::cout << "hill round, j = " << j << std::endl;
            // //std::cout << "****"<< std::endl;
            //std::cout << "x-coord1: " << ( j*pixelStep+xOffset )/SCALE << std::endl;
            // //std::cout << "****"<<
            //std::cout << "x-coord2: " << ( (j+1)*pixelStep+xOffset )/SCALE << std::endl;
            // std::cout << "****"<< std::endl;
            // std::cout << "y-coord1: " << ( hillStartY+randomHeight*cos( 2*b2_pi/hillSliceNumber*j ) )/SCALE << std::endl;
            // std::cout << "y-coord2: " << ( hillStartY+randomHeight*cos( 2*b2_pi/hillSliceNumber*(j+1) ) )/SCALE << std::endl;
            // std::cout << "****"<< std::endl;

            b2BodyDef sliceBody;
            sliceBody.type = b2_kinematicBody;
            b2Body* worldSlice = world.CreateBody( &sliceBody );
            b2EdgeShape slice;

            b2FixtureDef sliceFixture;
            slice.Set( b2Vec2( hillVector[0].x, hillVector[0].y ), b2Vec2( hillVector[1].x, hillVector[1].y ) );
            sliceFixture.shape = &slice;
            sliceFixture.friction = 0.6f;
            worldSlice->CreateFixture( &sliceFixture );

            while(!hillVector.empty())
            {
              hillVector.pop_back();
            }
            bodiesScheduledForRemoval.push_back( worldSlice );
          }
          hillStartY = hillStartY+randomHeight;
          return hillStartY;
      // }

}


/*========================== CREATE GROUND FOR THE WORLD ========================================*/
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

/*=========================== CREATE CIRCLES IN THE WORLD ====================================*/
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
