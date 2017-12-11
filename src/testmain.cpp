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
      else
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

void CreateCar( b2World& world, int MouseX, int MouseY )
{
/*========================== BOX2D SETUP FOR CAR =================================================*/
    //Random variables for the joints
    float wheeldistance = 2.3f;
    float m_hz = 4.0f;
    float m_zeta = 0.7f;
    //float m_speed = 50.0f;

/*=========================== CHASSIS = RUNKO ====================================================*/
    b2BodyDef bd_chassis;
    bd_chassis.type = b2_dynamicBody;
    bd_chassis.userData = (void*)"chassis";
    bd_chassis.position = b2Vec2( MouseX/SCALE, MouseY/SCALE ); //origin of chassis

    // b2PolygonShape chassis;
    // b2Vec2 vertices[8];
    // vertices[0].Set(2.0f, 11.0f);
    // vertices[1].Set(5.33f, 11.0f);
    // vertices[2].Set(5.33f, 11.5f);
    // vertices[3].Set(4.0f, 12.21f);
    // vertices[4].Set(2.4f, 12.21f);
    // vertices[5].Set(2.0f, 11.8f);
    // chassis.Set(vertices, 6);
    b2PolygonShape chassis;
    chassis.SetAsBox( (100.0f/2.0f)/SCALE, (36.33f/2.0f)/SCALE );
    b2Body* car = world.CreateBody(&bd_chassis);

    b2FixtureDef fd_chassis;
    fd_chassis.density = 1.0;
    fd_chassis.shape = &chassis;
    car->CreateFixture( &fd_chassis );

/*=========================== WHEELS ==============================================================*/
    b2CircleShape circle;
    circle.m_radius = 11.66f/SCALE;

    /*========== BACK WHEEL ================*/
    b2BodyDef bd_wheel1;
    bd_wheel1.type = b2_dynamicBody;
    bd_wheel1.userData = (void*)"wheel1";
    bd_wheel1.position.Set( (MouseX/SCALE)-0.3f, (MouseY/SCALE)+0.9f );
    b2Body* wheel1 = world.CreateBody( &bd_wheel1 );

    b2FixtureDef fd_wheel1;
    fd_wheel1.shape = &circle;
    fd_wheel1.density = 1.0f;
    fd_wheel1.friction = 0.9f;
    wheel1->CreateFixture( &fd_wheel1 );

    /*=========== FRONT WHEEL ===============*/
    b2BodyDef bd_wheel2;
    bd_wheel2.type = b2_dynamicBody;
    bd_wheel2.userData = (void*)"wheel2";
    bd_wheel2.position.Set( (MouseX/SCALE)+2.05f, (MouseY/SCALE)+0.9f ); //frontwheel
    b2Body* wheel2 = world.CreateBody( &bd_wheel2 );

    b2FixtureDef fd_wheel2;
    fd_wheel2.shape = &circle;
    fd_wheel2.density = 1.0f;
    fd_wheel2.friction = 0.9f;
    wheel2->CreateFixture( &fd_wheel2 );

/*========================== JOINTS =========================================================*/

  /*======== PRISMATIC JOINTS ==========*/
    // b2PrismaticJointDef pjd1;
    // pjd1.bodyA = wheel1;
    // pjd1.bodyB = car;
    // pjd1.collideConnected = true;
    // pjd1.localAxisA = b2Vec2( 0, 1 );
    // pjd1.localAnchorA = wheel1->GetPosition();
    // pjd1.localAnchorB = b2Vec2( car->GetPosition().x-wheeldistance/2, car->GetPosition().y );
    // b2PrismaticJoint* spring1 = (b2PrismaticJoint*)world.CreateJoint( &pjd1 );
    //
    // b2PrismaticJointDef pjd2;
    // pjd2.bodyA = wheel2;
    // pjd2.bodyB = car;
    // pjd2.collideConnected = true;
    // pjd2.localAxisA = b2Vec2( 0, 1 );
    // pjd2.localAnchorA = wheel2->GetPosition();
    // pjd2.localAnchorB = b2Vec2( car->GetPosition().x+wheeldistance/2, car->GetPosition().y );
    // b2PrismaticJoint* spring2 = (b2PrismaticJoint*)world.CreateJoint( &pjd2 );

    b2WheelJointDef jd;
    b2Vec2 axis( MouseX/SCALE, MouseY/SCALE ); //origin of chassis
    axis.Normalize();
    //joints connect the origin of the chassis and origin of circleshapes
    jd.Initialize(car, wheel1, wheel1->GetPosition(), axis );
    jd.motorSpeed = 0.0f;
    jd.maxMotorTorque = 20.0f;
    jd.enableMotor = true;
    jd.frequencyHz = m_hz;
    jd.dampingRatio = m_zeta;
    b2WheelJoint* spring1 = (b2WheelJoint*)world.CreateJoint(&jd);

    jd.Initialize(car, wheel2, wheel2->GetPosition(), axis );
    jd.motorSpeed = 0.0f;
    jd.maxMotorTorque = 10.0f;
    jd.enableMotor = false;
    jd.frequencyHz = m_hz;
    jd.dampingRatio = m_zeta;
    b2WheelJoint* spring2 = (b2WheelJoint*)world.CreateJoint(&jd);

/*========================== BOX2Dsetup End ==========================================*/
}

void CreateGround(b2World& world, float X, float Y, float angle)
{
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2( X/SCALE, Y/SCALE );
    BodyDef.type = b2_staticBody;
    BodyDef.angle = angle;
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
