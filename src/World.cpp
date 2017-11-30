// Tänne world joka pitää sisällään staattiset objektit (lattia,esteet,etc)
#include <World.hpp>
namespace Hills
{

  WorldManager::World() // luodaan uusi b2 maailma
  {
    // Setup the worlds properties
    bool doSleep = true;
    b2Vec2 gravity(0,9.8f)
    int iterations = 10;
    float scale = 30; // 1 meter is 30 pixels ingame
    float timestep = 1 / 60;
    // Setup the size of the worlc
    b2AABB worldAABB;
    worldAABB.lowerBound.set(-1000/scale, -1000/scale) // Upper left corner of the window
    worldAABB.upperBound.set(1000/scale, 1000/scale); // Lower right corner of the window
    this->world = new b2World(worldAABB,gravity,doSleep);
  }

  Floor::World() // luodaan lattia?
  {
    sf::Texture GroundTexture;
    GroundTexture.LoadFromFile("Resources/ground.png")
    void CreateGround

  }
}
