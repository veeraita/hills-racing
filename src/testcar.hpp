#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class Testcar
{
public:
  Testcar( b2World& world, int MouseX, int MouseY );
  b2WheelJoint* GetSpring1();
  b2WheelJoint* GetSpring2();
  float GetMhz();
  void Keyboard( sf::Event event );
private:
  b2World& world;
  int MouseX;
  int MouseY;
  b2WheelJoint* spring1;
  b2WheelJoint* spring2;
  float m_hz = 5.0f;
};
