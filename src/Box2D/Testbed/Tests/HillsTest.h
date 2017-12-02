#ifndef HILLSTEST_H
#define HILLSTEST_H

class Hills : public Test 
{
    public:
    Hills( )
    {
        b2Body* ground = NULL;
        {
            b2BodyDef bd;
            ground = m_world->CreateBody(&bd);
            
            b2EdgeShape shape;
            
            b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 0.0f;
			fd.friction = 0.6f;
			
			shape.Set(b2Vec2(-20.0f, 0.0f), b2Vec2(20.0f, 0.0f));
			ground->CreateFixture(&fd);
			
			
			//terrain created by connecting points
			float32 hs[10] = {0.25f, 1.0f, 4.0f, 0.0f, 0.0f, -1.0f, -2.0f, -2.0f, -1.25f, 0.0f};

			float32 x = 20.0f, y1 = 0.0f, dx = 5.0f;
			
			for (int32 i = 0; i < 10; ++i)
			{
				float32 y2 = hs[i];
				shape.Set(b2Vec2(x, y1), b2Vec2(x + dx, y2));
				ground->CreateFixture(&fd);
				y1 = y2;
				x += dx;
			}
			
			//cosine curved terrain
			for (int32 i = 0; i < 80; ++i)
			{
				float32 x2 = x + 0.5f;
				float32 y2 = 2.0f * cosf(x2 / 10.0f * b2_pi);

				//b2EdgeShape shape;
				shape.Set(b2Vec2(x, y1), b2Vec2(x2, y2));
				ground->CreateFixture(&shape, 0.0f);

				x = x2;
				y1 = y2;
			}
        }
        
    }
    
    void Step(Settings* settings)
	{
		m_debugDraw.DrawString(5, m_textLine, "Test for Hillside Racing physics");
		m_textLine += DRAW_STRING_NEW_LINE;

		//settings->viewCenter.x = m_car->GetPosition().x;
		Test::Step(settings);
	}
    
    static Test* Create()
	{
		return new Hills;
	}
    
    
};

#endif




