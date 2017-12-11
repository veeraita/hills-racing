#pragma once

#include "Car.hpp"

namespace Hills
{
  Car::Car( GameDataRef data, b2World& world ) : _data(data), world(world)
  {
      //Initialization of the b2body of the car and the sprites in the constructor
/*========================== BOX2Dsetup Begin ==========================================*/
        //Random variables for the joints
        float m_hz = 4.0f;
        float m_zeta = 0.7f;
        float m_speed = 50.0f;

        /*========= chassis =============*/
        b2BodyDef bd_chassis;
        bd_chassis.type = b2_dynamicBody;
        bd_chassis.userData = (void*)"chassis";
        bd_chassis.position.Set(2.0f, 15.0f); //origin of chassis

        b2PolygonShape chassis;
        b2Vec2 vertices[8];
        vertices[0].Set(2.0f, 11.0f);
        vertices[1].Set(5.0f, 11.0f);
        vertices[2].Set(5.0f, 11.5f);
        vertices[3].Set(4.0f, 12.4f);
        vertices[4].Set(2.4f, 12.4f);
        vertices[5].Set(2.0f, 11.9f);
        chassis.Set(vertices, 6);
        b2Body* car = world.CreateBody(&bd_chassis);

        b2FixtureDef fd_chassis;
        fd_chassis.density = 1.0;
        fd_chassis.shape = &chassis;
        car->CreateFixture( &fd_chassis );

        /*========== wheels =================*/
        b2CircleShape circle;
        circle.m_radius = 0.4f;

        /*========== wheel1 ================*/
        b2BodyDef bd_wheel1;
        bd_wheel1.type = b2_dynamicBody;
        bd_wheel1.userData = (void*)"wheel1";
        bd_wheel1.position.Set(1.0f, 14.25f); //backwheel
        b2Body* wheel1 = world.CreateBody( &bd_wheel1 );

        b2FixtureDef fd_wheel1;
        fd_wheel1.shape = &circle;
        fd_wheel1.density = 1.0f;
        fd_wheel1.friction = 0.9f;
        wheel1->CreateFixture( &fd_wheel1 );

        /*=========== wheel2 ================*/
        b2BodyDef bd_wheel2;
        bd_wheel2.type = b2_dynamicBody;
        bd_wheel2.userData = (void*)"wheel2";
        bd_wheel2.position.Set(3.0f, 14.25f); //frontwheel
        b2Body* wheel2 = world.CreateBody( &bd_wheel2 );

        b2FixtureDef fd_wheel2;
        fd_wheel2.shape = &circle;
        fd_wheel2.density = 1.0f;
        fd_wheel2.friction = 0.9f;
        wheel2->CreateFixture( &fd_wheel2 );

        /*========== Joints =================*/
        b2WheelJointDef jd;
        b2Vec2 axis(2.0f, 15.0f); //origin of chassis

        //joints connect the origin of the chassis and origin of circleshapes
        jd.Initialize(car, wheel1, wheel1->GetPosition(), axis);
        jd.motorSpeed = 0.0f;
        jd.maxMotorTorque = 20.0f;
        jd.enableMotor = true;
        jd.frequencyHz = m_hz;
        jd.dampingRatio = m_zeta;
        b2WheelJoint* spring1 = (b2WheelJoint*)world.CreateJoint(&jd);

        jd.Initialize(car, wheel2, wheel2->GetPosition(), axis);
        jd.motorSpeed = 0.0f;
        jd.maxMotorTorque = 10.0f;
        jd.enableMotor = false;
        jd.frequencyHz = m_hz;
        jd.dampingRatio = m_zeta;
        b2WheelJoint* spring2 = (b2WheelJoint*)world.CreateJoint(&jd);

/*=============================== Box2d setup end ====================================*/
        //load Resources to sprites
        this->_data->assets.LoadTexture( "Chassis", CHASSIS_FILEPATH );
        _chassissprite.setTexture( this->_data->assets.GetTexture( "Chassis") );

        this->_data->assets.LoadTexture( "Wheel", WHEEL_FILEPATH );
    		_wheelsprite1.setTexture( this->_data->assets.GetTexture( "Whleel" ) );
        _wheelsprite2.setTexture( this->_data->assets.GetTexture( "Whleel" ) );

        Draw( world, _chassissprite, _wheelsprite1, _wheelsprite2, this->_data );

  }

  void Car::Draw( b2World& world, sf::Sprite _chassissprite, sf::Sprite _wheelsprite1, sf::Sprite _wheelsprite2, GameDataRef _data )
  {
    //Here we are going to draw the sprites on top of the Shapes
    for( b2Body* b = world.GetBodyList(); b != 0 ; b = b->GetNext() )
    {
      if( b->GetUserData() == "chassis" )
      {
        _chassissprite.setScale(1/SCALE, 1/SCALE);
        _chassissprite.setOrigin( _chassissprite.getGlobalBounds().width / 2, _chassissprite.getGlobalBounds().height / 2 );
        _chassissprite.setPosition(SCALE * b->GetPosition().x , SCALE * b->GetPosition().y );
        _chassissprite.setRotation( b->GetAngle() * 180/b2_pi );
        _data->window.draw( _chassissprite );
      }

      else if( b->GetUserData() == "wheel1")
      {
        _wheelsprite1.setScale(1/SCALE, 1/SCALE);
        _wheelsprite1.setOrigin( _wheelsprite1.getGlobalBounds().width / 2, _wheelsprite1.getGlobalBounds().height / 2 );
        _wheelsprite1.setPosition( SCALE * b->GetPosition().x , SCALE * b->GetPosition().y );
        _wheelsprite1.setRotation( b->GetAngle() * 180/b2_pi );
        _data->window.draw( _wheelsprite1 );
      }

      else if( b->GetUserData() == "wheel2" )
      {
        _wheelsprite1.setScale(1/SCALE, 1/SCALE);
        _wheelsprite2.setOrigin( _wheelsprite2.getGlobalBounds().width / 2, _wheelsprite2.getGlobalBounds().height / 2 );
        _wheelsprite2.setPosition( SCALE * b->GetPosition().x , SCALE * b->GetPosition().y );
        _wheelsprite2.setRotation( b->GetAngle() * 180/b2_pi );
        _data->window.draw( _wheelsprite2 );
      }
    }
  }
}



// Liikuttaa vasemmalle
// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
// {
//     // left key is pressed: move our character
//     character.move(-1, 0);
// }
//
//
//
// Liikuttaa oikealle
// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
// {
//     // left key is pressed: move our character
//     character.move(1, 0);
// }
