#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class Testcar
{
public:
  Testcar( b2World& world, int MouseX, int MouseY );
  b2WheelJoint* GetSpring1();
  b2WheelJoint* GetSpring2();
  b2RevoluteJoint* GetRearRevoluter();
  b2RevoluteJoint* GetFrontRevoluter();
  b2PrismaticJoint* GetRearPrismatic();
  b2PrismaticJoint* GetFrontPrismatic();
  b2Body* GetCar();
  float GetMhz();
  void Keyboard( sf::Event event );

private:
  b2World& world;
  int MouseX;
  int MouseY;
  b2Body* car;
  b2Body* wheel1;
  b2Body* wheel2;
  b2WheelJoint* spring1;
  b2WheelJoint* spring2;
  b2RevoluteJoint* rear_revoluter;
  b2RevoluteJoint* front_revoluter;
  b2PrismaticJoint* rear_prismatic;
  b2PrismaticJoint* front_prismatic;
  float m_hz = 5.0f;
};
