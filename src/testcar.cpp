#include "testcar.hpp"

/*======================== GLOBALS ======================================================*/
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 1024
#define SCALE 30

Testcar::Testcar( b2World& world, int MouseX, int MouseY ) : world(world), MouseX(MouseX), MouseY(MouseY)
{
  /*========================== BOX2D SETUP FOR CAR =================================================*/
      //Random variables for the joints
      float wheeldistance = 2.3f;
      float m_zeta = 0.7f;

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

  /*========= PRISMATIC JOINTS ==================*/
      // b2PrismaticJointDef pjd1;
      // pjd1.bodyA = wheel1;
      // pjd1.bodyB = car;
      // pjd1.collideConnected = false;
      // pjd1.localAxisA = b2Vec2( 0, 1 );
      // pjd1.localAnchorA = wheel1->GetPosition();
      // pjd1.localAnchorB = b2Vec2( car->GetPosition().x-0.57, car->GetPosition().y );
      // b2PrismaticJoint* damper1 = (b2PrismaticJoint*)world.CreateJoint( &pjd1 );
      //
      // b2PrismaticJointDef pjd2;
      // pjd2.bodyA = wheel2;
      // pjd2.bodyB = car;
      // pjd2.collideConnected = false;
      // pjd2.localAxisA = b2Vec2( 0, 1 );
      // pjd2.localAnchorA = wheel2->GetPosition();
      // pjd2.localAnchorB = b2Vec2( car->GetPosition().x+4.0, car->GetPosition().y );
      // b2PrismaticJoint* damper2 = (b2PrismaticJoint*)world.CreateJoint( &pjd2 );

  /*========= WHEEL JOINTS ======================*/
      b2WheelJointDef jd;
      b2Vec2 axis( MouseX/SCALE, MouseY/SCALE ); //origin of chassis
      axis.Normalize();
      //wheeljoints connect the origin of the chassis and origin of circleshapes
      jd.Initialize(car, wheel1, wheel1->GetPosition(), axis );
      jd.motorSpeed = 0.0f;
      jd.maxMotorTorque = 20.0f;
      jd.enableMotor = true;
      jd.frequencyHz = m_hz;
      jd.dampingRatio = m_zeta;
      spring1 = (b2WheelJoint*)world.CreateJoint(&jd);

      jd.Initialize(car, wheel2, wheel2->GetPosition(), axis );
      jd.motorSpeed = 0.0f;
      jd.maxMotorTorque = 10.0f;
      jd.enableMotor = false;
      jd.frequencyHz = m_hz;
      jd.dampingRatio = m_zeta;
      spring2 = (b2WheelJoint*)world.CreateJoint(&jd);

  /*========================== BOX2Dsetup End ==========================================*/
}

/*============================ GETTERS ========================================================*/
b2WheelJoint* Testcar::GetSpring1()
{
  return spring1;
}
b2WheelJoint* Testcar::GetSpring2()
{
  return spring2;
}
float Testcar::GetMhz()
{
  return m_hz;
}

/*============================= KEYBOARD INPUTS ================================================*/
void Testcar::Keyboard( sf::Event event )
{
  if( event.type == sf::Event::KeyPressed )
  {
    if( event.key.code == sf::Keyboard::Left )
    {
       GetSpring1()->SetMotorSpeed(-50.0f);
    }
  }
  if( event.type == sf::Event::KeyPressed )
  {
    if( event.key.code == sf::Keyboard::Down )
    {
      GetSpring1()->SetMotorSpeed(0.0f);
    }
  }
  if( event.type == sf::Event::KeyPressed )
  {
    if( event.key.code == sf::Keyboard::Right )
    {
      GetSpring1()->SetMotorSpeed(50.0);
    }
  }
  if( event.type == sf::Event::KeyPressed )
  {
    if( event.key.code == sf::Keyboard::Left && event.key.code == sf::Keyboard::Up )
    {
      float hz = GetMhz();
      hz = b2Max(0.0f, hz - 1.0f);
  	  GetSpring1()->SetSpringFrequencyHz(hz);
  	  GetSpring2()->SetSpringFrequencyHz(hz);
    }
  }
  if( event.type == sf::Event::KeyPressed )
  {
    if( event.key.code == sf::Keyboard::Right && event.key.code == sf::Keyboard::Up )
    {
      float hz = GetMhz();
      hz += 1.0f;
  	  GetSpring1()->SetSpringFrequencyHz(hz);
  	  GetSpring2()->SetSpringFrequencyHz(hz);
    }
  }
}
