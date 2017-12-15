#pragma once

#include "Car.hpp"

namespace Hills
{
  Car::Car( GameDataRef data, b2World& world ) : _data(data), world(world)
  {
      //Initialization of the b2body of the car and the sprites in the constructor

/*========================== BOX2Dsetup Begin ==========================================*/
        //variables for the joints
        m_hz = 4.0f;
        m_zeta = 0.8f;
        m_speed = 40.0f;
        float y1 = 5.0f;
        /*========= chassis =============*/
        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.position.Set(4.0f, 1.5*y1+1.0f); //origin of chassis

        b2PolygonShape chassis;
        b2Vec2 vertices[8];
		vertices[0].Set(-1.5f, -0.2f);
		vertices[1].Set(1.2f, -0.2f);
		vertices[2].Set(1.2f, 0.0f);
		vertices[3].Set(0.0f, 0.5f);
		vertices[4].Set(-1.15f, 0.5f);
		vertices[5].Set(-1.5f, 0.2f);
        chassis.Set(vertices, 6);
        car = world.CreateBody(&bd);
        car->CreateFixture( &chassis, 1.0f );

        /*========== wheel properties =================*/
        b2CircleShape circle;
        circle.m_radius = 0.35f;

    	b2FixtureDef fd;
		fd.shape = &circle;
		fd.density = 1.0f;
        fd.friction = 1.9f;
        fd.restitution = 0.2;

        /*========== back wheel ================*/
        bd.position.Set(3.0f, 1.5*y1+0.35f);
        wheel1 = world.CreateBody( &bd );
        wheel1->CreateFixture( &fd );

        /*=========== front wheel ================*/
        bd.position.Set(5.0f, 1.5*y1+0.4f);
        wheel2 = world.CreateBody( &bd );
        wheel2->CreateFixture( &fd );

        /*========== Joints =================*/
        b2WheelJointDef jd;
        b2Vec2 axis(0.0f, 1.0f);
        //axis.Normalize();

        //joints connect the origin of the chassis and origin of circleshapes
        jd.Initialize(car, wheel1, wheel1->GetPosition(), axis);
        jd.motorSpeed = 0.0f;
        jd.maxMotorTorque = 7.0f;
        jd.enableMotor = true;
        jd.frequencyHz = m_hz;
        jd.dampingRatio = m_zeta;
        spring1 = (b2WheelJoint*)world.CreateJoint(&jd);

        jd.Initialize(car, wheel2, wheel2->GetPosition(), axis);
        jd.motorSpeed = 0.0f;
        jd.maxMotorTorque = 5.0f;
        jd.enableMotor = false;
        jd.frequencyHz = m_hz;
        jd.dampingRatio = m_zeta;
        spring2 = (b2WheelJoint*)world.CreateJoint(&jd);

/*=============================== Box2d setup end ====================================*/

        //load Resources to sprites
        this->_data->assets.LoadTexture( "Chassis", CHASSIS_FILEPATH );
        this->_data->assets.LoadTexture( "Wheel", WHEEL_FILEPATH );

        _chassissprite.setTexture( this->_data->assets.GetTexture( "Chassis") );
        _chassissprite.setOrigin( _chassissprite.getGlobalBounds().width / 2, _chassissprite.getGlobalBounds().height / 2 );
        _chassissprite.setScale(0.5, 0.5);

    	_wheelsprite1.setTexture( this->_data->assets.GetTexture( "Wheel" ) );
    	_wheelsprite1.setOrigin( _wheelsprite1.getGlobalBounds().width / 2, _wheelsprite1.getGlobalBounds().height / 2 );
    	_wheelsprite1.setScale(0.5, 0.5);

        _wheelsprite2.setTexture( this->_data->assets.GetTexture( "Wheel" ) );
        _wheelsprite2.setOrigin( _wheelsprite2.getGlobalBounds().width / 2, _wheelsprite2.getGlobalBounds().height / 2 );
        _wheelsprite2.setScale(0.5, 0.5);

  }

    sf::Sprite& Car::getChassisSprite()
    {
        _chassissprite.setPosition(SCALE * car->GetPosition().x , SCREEN_HEIGHT - SCALE * car->GetPosition().y );
        _chassissprite.setRotation( car->GetAngle() * -180/b2_pi );
        if (_chassissprite.getPosition().x < 1.5f * SCALE)
        {
            spring1->SetMotorSpeed(0.0f);
        }
        return _chassissprite;
    }

    sf::Sprite& Car::getWheelSprite1()
    {
        _wheelsprite1.setPosition( SCALE * wheel1->GetPosition().x , SCREEN_HEIGHT - SCALE * wheel1->GetPosition().y );
        _wheelsprite1.setRotation( wheel1->GetAngle() * -180/b2_pi );
        return _wheelsprite1;
    }

    sf::Sprite& Car::getWheelSprite2()
    {
        _wheelsprite2.setPosition( SCALE * wheel2->GetPosition().x , SCREEN_HEIGHT - SCALE * wheel2->GetPosition().y );
        _wheelsprite2.setRotation( wheel2->GetAngle() * -180/b2_pi );
        return _wheelsprite2;
    }
    
    float Car::GetAngle()
    {
        return car->GetAngle();
    }

    void Car::Reverse()
    {
            spring1->SetMotorSpeed(std::min(m_speed, spring1->GetMotorSpeed() + 0.3f));
    }

    void Car::Accelerate()
    {
        spring1->SetMotorSpeed(std::max(-m_speed, spring1->GetMotorSpeed() - 0.3f));
    }

    void Car::Brake()
    {
        spring1->SetMotorSpeed(0.0f);
    }

    void Car::TiltUp()
    {
        car->ApplyTorque(15, true);
    }

    void Car::TiltDown()
    {
        car->ApplyTorque(-15, true);
    }
}



