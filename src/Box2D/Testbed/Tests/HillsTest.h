#ifndef HILLSTEST_H
#define HILLSTEST_H

class Hills : public Test 
{
    public:
    Hills( )
    {
        m_hz = 4.0f;
		m_zeta = 0.7f;
		m_speed = 50.0f;
		
        b2Body* ground = NULL;
        {
            b2BodyDef bd;
            ground = m_world->CreateBody(&bd);
            
            b2EdgeShape shape;
            
            b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 0.0f;
			fd.friction = 0.6f;
			
			float32 x = 20.0f, y1 = 10.0f, dx = 5.0f;
			
			shape.Set(b2Vec2(-20.0f, y1), b2Vec2(20.0f, y1));
			ground->CreateFixture(&fd);
			
			
			//terrain created by connecting points
			float32 hs[10] = {0.25f, 1.0f, 4.0f, 0.0f, 0.0f, -1.0f, -2.0f, -2.0f, -1.25f, 0.0f};
			
			for (int32 i = 0; i < 10; ++i)
			{
				float32 y2 = y1 + hs[i];
			    shape.Set(b2Vec2(x, y1), b2Vec2(x + dx, y2));
			    ground->CreateFixture(&fd);
				y1 = y2;
				x += dx;
			}
			
        }
        
        // Car
		{
		    float32 y1 = 10.0f;
			b2PolygonShape chassis;
			b2Vec2 vertices[8];
		    vertices[0].Set(-1.5f, -0.5f);
		    vertices[1].Set(1.5f, -0.5f);
		    vertices[2].Set(1.5f, 0.0f);
		    vertices[3].Set(0.0f, 0.9f);
		    vertices[4].Set(-1.15f, 0.9f);
		    vertices[5].Set(-1.5f, 0.2f);
			chassis.Set(vertices, 6);

			b2CircleShape circle;
			circle.m_radius = 0.4f;

			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(4.0f, 2*y1+1.0f);
			m_car = m_world->CreateBody(&bd);
			m_car->CreateFixture(&chassis, 1.0f);

			b2FixtureDef fd;
			fd.shape = &circle;
			fd.density = 1.0f;
			fd.friction = 0.9f;

			bd.position.Set(3.0f, 2*y1+0.35f);
			m_wheel1 = m_world->CreateBody(&bd);
			m_wheel1->CreateFixture(&fd);

			bd.position.Set(5.0f, 2*y1+0.4f);
			m_wheel2 = m_world->CreateBody(&bd);
			m_wheel2->CreateFixture(&fd);

			b2WheelJointDef jd;
			b2Vec2 axis(0.0f, 1.0f);
			//b2Vec2 axis(139/30, 842/30);
			//axis.Normalize();

			jd.Initialize(m_car, m_wheel1, m_wheel1->GetPosition(), axis);
			jd.motorSpeed = 0.0f;
			jd.maxMotorTorque = 40.0f;
			jd.enableMotor = true;
			jd.frequencyHz = m_hz;
			jd.dampingRatio = m_zeta;
			m_spring1 = (b2WheelJoint*)m_world->CreateJoint(&jd);

			jd.Initialize(m_car, m_wheel2, m_wheel2->GetPosition(), axis);
			jd.motorSpeed = 0.0f;
			jd.maxMotorTorque = 20.0f;
			jd.enableMotor = false;
			jd.frequencyHz = m_hz;
			jd.dampingRatio = m_zeta;
			m_spring2 = (b2WheelJoint*)m_world->CreateJoint(&jd);
		}
	}
        
    
	void Keyboard(unsigned char key)
	{
		switch (key)
		{
		case 'a':
			m_spring1->SetMotorSpeed(m_speed);
			break;

		case 's':
			m_spring1->SetMotorSpeed(0.0f);
			break;

		case 'd':
			m_spring1->SetMotorSpeed(-m_speed);
			break;

		case 'q':
			m_hz = b2Max(0.0f, m_hz - 1.0f);
			m_spring1->SetSpringFrequencyHz(m_hz);
			m_spring2->SetSpringFrequencyHz(m_hz);
			break;

		case 'e':
			m_hz += 1.0f;
			m_spring1->SetSpringFrequencyHz(m_hz);
			m_spring2->SetSpringFrequencyHz(m_hz);
			break;
		}
	}
    
    void Step(Settings* settings)
	{
		m_debugDraw.DrawString(5, m_textLine, "Test for Hillside Racing physics");
		m_textLine += DRAW_STRING_NEW_LINE;
		m_debugDraw.DrawString(5, m_textLine, "Keys: left = a, brake = s, right = d, hz down = q, hz up = e");
		m_textLine += DRAW_STRING_NEW_LINE;
		m_debugDraw.DrawString(5, m_textLine, "frequency = %g hz, damping ratio = %g", m_hz, m_zeta);

		settings->viewCenter.x = m_car->GetPosition().x;
		Test::Step(settings);
	}
    
    static Test* Create()
	{
		return new Hills;
	}
	
	b2Body* m_car;
	b2Body* m_wheel1;
	b2Body* m_wheel2;

	float32 m_hz;
	float32 m_zeta;
	float32 m_speed;
	b2WheelJoint* m_spring1;
	b2WheelJoint* m_spring2;
    
    
};

#endif




