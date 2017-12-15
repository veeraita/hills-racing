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

      // b2BodyDef bd;
      // bd.type = b2_dynamicBody;
      // bd.position.Set(4.0f, 1.5*5.0+1.0f); //origin of chassis
      //
      // b2PolygonShape chassis;
      // b2Vec2 vertices[8];
      // vertices[0].Set(0.0f, 0.0f);
      // vertices[1].Set(3.0f, 0.0f);
      // vertices[2].Set(3.0f, -1.0f);
      // vertices[3].Set(2.0f, -1.5f);
      // vertices[4].Set(0.3f, -1.5f);
      // vertices[5].Set(0.0f, -1.0f);
      // chassis.Set(vertices, 6);
      // car = world.CreateBody(&bd);
      // car->CreateFixture( &chassis, 1.0f );
      //
      // /*========== wheel properties =================*/
      // b2CircleShape circle;
      // circle.m_radius = 0.35f;
      //
      // b2FixtureDef fd;
      // fd.shape = &circle;
      // fd.density = 1.0f;
      // fd.friction = 0.9f;
      //
      // /*========== wheel1 ================*/
      // bd.position.Set(3.0f, 1.5*5.0+0.35f); //backwheel
      // wheel1 = world.CreateBody( &bd );
      // wheel1->CreateFixture( &fd );
      //
      // /*=========== wheel2 ================*/
      // bd.position.Set(5.0f, 1.5*5.0+0.4f); //frontwheel
      // wheel2 = world.CreateBody( &bd );
      // wheel2->CreateFixture( &fd );
      //
      // /*========== Joints =================*/
      // b2WheelJointDef jd;
      // b2Vec2 axis(0.0f, 1.0f);
      // //axis.Normalize();
      //
      // //joints connect the origin of the chassis and origin of circleshapes
      // jd.Initialize(car, wheel1, wheel1->GetPosition(), axis);
      // jd.motorSpeed = 0.0f;
      // jd.maxMotorTorque = 20.0f;
      // jd.enableMotor = true;
      // jd.frequencyHz = m_hz;
      // jd.dampingRatio = m_zeta;
      // spring1 = (b2WheelJoint*)world.CreateJoint(&jd);
      //
      // jd.Initialize(car, wheel2, wheel2->GetPosition(), axis);
      // jd.motorSpeed = 0.0f;
      // jd.maxMotorTorque = 10.0f;
      // jd.enableMotor = false;
      // jd.frequencyHz = m_hz;
      // jd.dampingRatio = m_zeta;
      // spring2 = (b2WheelJoint*)world.CreateJoint(&jd);

/*=========================== CHASSIS = RUNKO ====================================================*/
      //This shape is used in Car.h testbed
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
      chassis.SetAsBox( (135.0f/2.0f)/SCALE, (18.0f/2.0f)/SCALE );//Sprite: width=100px, height=36.33px
      b2FixtureDef fd_chassis;
      fd_chassis.density = 2.0;
      fd_chassis.filter.groupIndex = -1;
      fd_chassis.shape = &chassis;

      b2BodyDef bd_chassis;
      bd_chassis.type = b2_dynamicBody;
      bd_chassis.userData = (void*)"chassis";
      bd_chassis.position = b2Vec2( MouseX/SCALE, MouseY/SCALE ); //origin of the chassis
      b2Body* car = world.CreateBody( &bd_chassis );
      car->CreateFixture( &fd_chassis );

/*=========================== AXLES = AKSELIT =====================================================*/
      b2PolygonShape axleshape;//axles will be regular square boxes
      axleshape.SetAsBox( (11.66f/2.0f)/SCALE, (11.66f/2.0f)/SCALE );//Need to fit inside wheels

      b2FixtureDef fd_axle;
      fd_axle.density = 0.5f;
      fd_axle.friction = 1.9f;
      fd_axle.restitution = 0.3f;
      fd_axle.filter.groupIndex = -1;
      fd_axle.shape = &axleshape;

      b2BodyDef bd_axle;
      bd_axle.type = b2_dynamicBody;
      bd_axle.userData = (void*)"axle";
      bd_axle.position.Set( (MouseX/SCALE)-(30.0f/SCALE), (MouseY/SCALE));//car->GetWorldCenter().x-(35.66f/SCALE), car->GetWorldCenter().y+0.9f

      /*===================== REAR AXLE ===========================*/
      b2Body* rearAxle = world.CreateBody( &bd_axle );
      rearAxle->CreateFixture( &fd_axle );

      /*===================== FRONT AXLE ===========================*/
      bd_axle.position.Set( (MouseX/SCALE)+(30.0f/SCALE), (MouseY/SCALE));//car->GetWorldCenter().x+(33.66f/SCALE), car->GetWorldCenter().y+0.9f
      b2Body* frontAxle = world.CreateBody( &bd_axle );
      frontAxle->CreateFixture( &fd_axle );

/*=========================== WHEELS ==============================================================*/
      b2CircleShape circle;
      circle.m_radius = 23.0f/SCALE;//WheelSprite: half-width=11.66px

      b2FixtureDef fd_wheel1;
      fd_wheel1.density = 1.0f;
      fd_wheel1.friction = 2.9f;
      fd_wheel1.filter.groupIndex = -1;
      fd_wheel1.shape = &circle;

       /*========== REAR WHEEL ================*/
      b2BodyDef bd_wheel1;
      bd_wheel1.type = b2_dynamicBody;
      bd_wheel1.userData = (void*)"wheel1";
      bd_wheel1.position.Set( (MouseX/SCALE)-(30.0f/SCALE), (MouseY/SCALE));//(MouseX/SCALE)-0.3f (MouseY/SCALE)+0.9f

      b2Body* wheel1 = world.CreateBody( &bd_wheel1 );
      wheel1->CreateFixture( &fd_wheel1 );

      /*=========== FRONT WHEEL ===============*/
      b2FixtureDef fd_wheel2;
      fd_wheel2.density = 1.0f;
      fd_wheel2.friction = 2.9f;
      fd_wheel2.filter.groupIndex = -1;
      fd_wheel2.shape = &circle;

      b2BodyDef bd_wheel2;
      bd_wheel2.type = b2_dynamicBody;
      bd_wheel2.userData = (void*)"wheel2";
      bd_wheel2.position.Set( (MouseX/SCALE)+(30.0f/SCALE), (MouseY/SCALE));

      b2Body* wheel2 = world.CreateBody( &bd_wheel2 );
      wheel2->CreateFixture( &fd_wheel2 );

/*========================== JOINTS =======================================================================*/
  /*========= REVOLUTE JOINTS ===================*/
      /*===== REAR =============*/
      b2RevoluteJointDef rear_rjd;
      rear_rjd.Initialize( wheel1, rearAxle, wheel1->GetWorldCenter() );
      rear_rjd.enableMotor = true;
      rear_rjd.maxMotorTorque = 50000.0f;
      rear_revoluter = (b2RevoluteJoint*)world.CreateJoint( &rear_rjd );

      /*===== FRONT ==============*/
      b2RevoluteJointDef front_rjd;
      front_rjd.Initialize( wheel2, frontAxle, wheel2->GetWorldCenter() );
      front_rjd.enableMotor = true;
      front_rjd.maxMotorTorque = 50000.0f;
      front_revoluter = (b2RevoluteJoint*)world.CreateJoint( &front_rjd );

  /*========= PRISMATIC JOINTS ==================*/
      b2Vec2 axis1( 0, 1 );
      b2PrismaticJointDef pjd;
      pjd.lowerTranslation = -3/SCALE;
      pjd.upperTranslation = 4/SCALE;
      pjd.enableLimit = true;
      pjd.enableMotor = true;

      /*===== REAR ===================*/
      pjd.Initialize( car, frontAxle, frontAxle->GetWorldCenter(), axis1 );
      rear_prismatic = (b2PrismaticJoint*)world.CreateJoint( &pjd );

      /*===== FRONT ==================*/
      pjd.Initialize( car, rearAxle, rearAxle->GetWorldCenter(), axis1 );
      rear_prismatic = (b2PrismaticJoint*)world.CreateJoint( &pjd ); bd_axle.position.Set( (MouseX/SCALE)+(30.0f/SCALE), (MouseY/SCALE)+(27.0f/SCALE));//car->GetWorldCenter().x+(33.66f/SCALE), car->GetWorldCenter().y+0.9f

  /*========= WHEEL JOINTS ======================*/
      // b2WheelJointDef jd;
      // b2Vec2 axis( MouseX/SCALE, MouseY/SCALE ); //origin of chassis
      // axis.Normalize();
      // //wheeljoints connect the origin of the chassis and origin of circleshapes
      // jd.Initialize(car, wheel1, wheel1->GetPosition(), axis );
      // jd.motorSpeed = 0.0f;
      // jd.maxMotorTorque = 20.0f;
      // jd.enableMotor = true;
      // jd.frequencyHz = m_hz;
      // jd.damp-2.5ingRatio = m_zeta;
      // spring1 = (b2WheelJoint*)world.CreateJoint(&jd);
      //
      // jd.Initialize(car, wheel2, wheel2->GetPosition(), axis );
      // jd.motorSpeed = 0.0f;
      // jd.maxMotorTorque = 10.0f;
      // jd.enableMotor = false;
      // jd.frequencyHz = m_hz;
      // jd.dampingRatio = m_zeta;
      // spring2 = (b2WheelJoint*)world.CreateJoint(&jd);

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
b2RevoluteJoint* Testcar::GetRearRevoluter()
{
  return rear_revoluter;
}
b2RevoluteJoint* Testcar::GetFrontRevoluter()
{
  return front_revoluter;
}
b2PrismaticJoint* Testcar::GetRearPrismatic()
{
  return rear_prismatic;
}
b2PrismaticJoint* Testcar::GetFrontPrismatic()
{
  return front_prismatic;
}
float Testcar::GetMhz()
{
  return m_hz;
}
b2Body* Testcar::GetCar()
{
    return car;
}


/*============================= KEYBOARD INPUTS ================================================*/
void Testcar::Keyboard( sf::Event event )
{
  if( event.type == sf::Event::KeyPressed )
  {
    if( event.key.code == sf::Keyboard::Up )
    {
      GetRearRevoluter()->SetMotorSpeed(-15.5f);
      GetFrontRevoluter()->SetMotorSpeed(-15.5f);
    }
    if( event.key.code == sf::Keyboard::Left )
    {
      GetRearRevoluter()->SetMotorSpeed(0.0f);
      GetFrontRevoluter()->SetMotorSpeed(0.0f);
    }
    if( event.key.code == sf::Keyboard::Down )
    {
      GetRearRevoluter()->SetMotorSpeed(15.5f);
      GetFrontRevoluter()->SetMotorSpeed(15.5f);
    }
    // if( event.key.code == sf::Keyboard::Right )
    // {
    //   GetCar()->ApplyTorque(-35, true);
    // }
  }


//   if( event.type == sf::Event::KeyPressed )
//   {
//     if( event.key.code == sf::Keyboard::Left && event.key.code == sf::Keyboard::Up )
//     {
//       float hz = GetMhz();
//       hz = b2Max(0.0f, hz - 1.0f);
//   	  GetSpring1()->SetSpringFrequencyHz(hz);
//   	  GetSpring2()->SetSpringFrequencyHz(hz);
//     }
//   }
//   if( event.type == sf::Event::KeyPressed )
//   {
//     if( event.key.code == sf::Keyboard::Right && event.key.code == sf::Keyboard::Up )
//     {
//       float hz = GetMhz();
//       hz += 1.0f;
//   	  GetSpring1()->SetSpringFrequencyHz(hz);
//   	  GetSpring2()->SetSpringFrequencyHz(hz);
//     }
//   }
}
