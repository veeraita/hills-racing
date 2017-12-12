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
        float y1 = 10.0f;
        /*========= chassis =============*/
        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.position.Set(5.0f, 1.5*y1+1.0f); //origin of chassis

        b2PolygonShape chassis;
        b2Vec2 vertices[8];
		vertices[0].Set(-1.5f, -0.5f);
		vertices[1].Set(1.5f, -0.5f);
		vertices[2].Set(1.5f, 0.0f);
		vertices[3].Set(0.0f, 0.9f);
		vertices[4].Set(-1.15f, 0.9f);
		vertices[5].Set(-1.5f, 0.2f);
        chassis.Set(vertices, 6);
        car = world.CreateBody(&bd);
        car->CreateFixture( &chassis, 1.0f );

        /*========== wheel properties =================*/
        b2CircleShape circle;
        circle.m_radius = 0.4f;
        
    	b2FixtureDef fd;
		fd.shape = &circle;
		fd.density = 1.0f;
		fd.friction = 0.9f;

        /*========== wheel1 ================*/
        bd.position.Set(1.5f, 1.5*y1); //backwheel
        wheel1 = world.CreateBody( &bd );
        wheel1->CreateFixture( &fd );

        /*=========== wheel2 ================*/
        bd.position.Set(8.5f, 1.5*y1); //frontwheel
        wheel2 = world.CreateBody( &bd );
        wheel2->CreateFixture( &fd );

        /*========== Joints =================*/
        b2WheelJointDef jd;
        b2Vec2 axis(0.0f, 1.0f); //origin of chassis
        //axis.Normalize();

        //joints connect the origin of the chassis and origin of circleshapes
        jd.Initialize(car, wheel1, wheel1->GetPosition(), axis);
        jd.motorSpeed = 0.0f;
        jd.maxMotorTorque = 20.0f;
        jd.enableMotor = true;
        jd.frequencyHz = m_hz;
        jd.dampingRatio = m_zeta;
        spring1 = (b2WheelJoint*)world.CreateJoint(&jd);

        jd.Initialize(car, wheel2, wheel2->GetPosition(), axis);
        jd.motorSpeed = 0.0f;
        jd.maxMotorTorque = 10.0f;
        jd.enableMotor = false;
        jd.frequencyHz = m_hz;
        jd.dampingRatio = m_zeta;
        spring2 = (b2WheelJoint*)world.CreateJoint(&jd);

/*=============================== Box2d setup end ====================================*/

        //load Resources to sprites
        this->_data->assets.LoadTexture( "Chassis", CHASSIS_FILEPATH );
        this->_data->assets.LoadTexture( "Wheel", WHEEL_FILEPATH );
        
        _chassissprite.setTexture( this->_data->assets.GetTexture( "Chassis") );
        //_chassissprite.setScale(1/SCALE, 1/SCALE);
        _chassissprite.setOrigin( _chassissprite.getGlobalBounds().width / 2, _chassissprite.getGlobalBounds().height / 2 );

    	_wheelsprite1.setTexture( this->_data->assets.GetTexture( "Wheel" ) );
    	//_wheelsprite1.setScale(1/SCALE, 1/SCALE);
        _wheelsprite1.setOrigin( _wheelsprite1.getGlobalBounds().width / 2, _wheelsprite1.getGlobalBounds().height / 2 );
        
        _wheelsprite2.setTexture( this->_data->assets.GetTexture( "Wheel" ) );
        //_wheelsprite2.setScale(1/SCALE, 1/SCALE);
        _wheelsprite2.setOrigin( _wheelsprite2.getGlobalBounds().width / 2, _wheelsprite2.getGlobalBounds().height / 2 );

  }
/*
  void Car::Draw( b2Body* car, b2Body* wheel1, b2Body* wheel2, sf::Sprite _chassissprite, sf::Sprite _wheelsprite1, sf::Sprite _wheelsprite2, GameDataRef _data )
  {
        _chassissprite.setScale(1/SCALE, 1/SCALE);
        _chassissprite.setOrigin( _chassissprite.getGlobalBounds().width / 2, _chassissprite.getGlobalBounds().height / 2 );
        _chassissprite.setPosition(SCALE * car->GetPosition().x , SCREEN_HEIGHT - SCALE * car->GetPosition().y );
        _chassissprite.setRotation( car->GetAngle() * 180/b2_pi );
        _data->window.draw( _chassissprite );
        
        _wheelsprite1.setScale(1/SCALE, 1/SCALE);
        _wheelsprite1.setOrigin( _wheelsprite1.getGlobalBounds().width / 2, _wheelsprite1.getGlobalBounds().height / 2 );
        _wheelsprite1.setPosition( SCALE * wheel1->GetPosition().x , SCREEN_HEIGHT - SCALE * wheel1->GetPosition().y );
        _wheelsprite1.setRotation( wheel1->GetAngle() * 180/b2_pi );
        _data->window.draw( _wheelsprite1 );

        _wheelsprite1.setScale(1/SCALE, 1/SCALE);
        _wheelsprite2.setOrigin( _wheelsprite2.getGlobalBounds().width / 2, _wheelsprite2.getGlobalBounds().height / 2 );
        _wheelsprite2.setPosition( SCALE * wheel2->GetPosition().x , SCREEN_HEIGHT - SCALE * wheel2->GetPosition().y );
        _wheelsprite2.setRotation( wheel2->GetAngle() * 180/b2_pi );
        _data->window.draw( _wheelsprite2 );
      
  }
 */ 
    sf::Sprite& Car::getChassisSprite()
    {
        _chassissprite.setPosition(SCALE * car->GetPosition().x , SCREEN_HEIGHT - SCALE * car->GetPosition().y );
        _chassissprite.setRotation( car->GetAngle() * 180/b2_pi );
        return _chassissprite;
    }
    
    sf::Sprite& Car::getWheelSprite1()
    {
        _wheelsprite1.setPosition( SCALE * wheel1->GetPosition().x , SCREEN_HEIGHT - SCALE * wheel1->GetPosition().y );
        _wheelsprite1.setRotation( wheel1->GetAngle() * 180/b2_pi );
        return _wheelsprite1;
    }
    
    sf::Sprite& Car::getWheelSprite2()
    {
        _wheelsprite2.setPosition( SCALE * wheel2->GetPosition().x , SCREEN_HEIGHT - SCALE * wheel2->GetPosition().y );
        _wheelsprite2.setRotation( wheel2->GetAngle() * 180/b2_pi );
        return _wheelsprite2;
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
