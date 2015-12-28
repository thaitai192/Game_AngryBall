/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef WEB_H
#define WEB_H

// This tests distance joints, body destruction, and joint destruction.
class Web : public Test
{
public:
	Web()
	{
		b2Body* ground = NULL;
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.Set(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
			ground->CreateFixture(&shape, 0.0f);
		}

		{
			//mine

			b2CircleShape circleShape;
			circleShape.m_radius = 3.0f;
			b2BodyDef bd2;
			bd2.type= b2_dynamicBody;
			bd2.position.Set(-30,3);
			test[0]= m_world->CreateBody(&bd2);
			test[0]->CreateFixture(&circleShape, 5.0f);
			test[0]->SetLinearVelocity(b2Vec2(-1.0, 0.0));

			b2PolygonShape shape_test;
			shape_test.SetAsBox(7, 2);
			b2FixtureDef fd1;
			fd1.shape=&shape_test;
			b2BodyDef bd1;
			bd1.position.Set(-20, 5);
			bd1.type= b2_dynamicBody;
			test[1]= m_world->CreateBody(&bd1);
			test[1]->CreateFixture(&fd1);

			/*b2DistanceJointDef jd1;
			jd1.frequencyHz=1.0;
			jd1.dampingRatio=1.0;
			jd1.bodyA= ground;
			jd1.bodyB= test[0];
			jd1.localAnchorA.Set(-20.0f, 0.0f);
			jd1.localAnchorB.Set(-0.0f, -0.0f);
			b2Vec2 b1, b2, dis;
			b1 = jd1.bodyA->GetWorldPoint(jd1.localAnchorA);
			b2 = jd1.bodyB->GetWorldPoint(jd1.localAnchorB);
			dis=b2-b1;
			jd1.length=dis.Length();
			test_joint[0] = m_world->CreateJoint(&jd1);

			jd1.bodyA= ground;
			jd1.bodyB= test[0];
			jd1.localAnchorA.Set(-40.0f, 0.0f);
			jd1.localAnchorB.Set(-0.0f, -0.0f);
			b1 = jd1.bodyA->GetWorldPoint(jd1.localAnchorA);
			b2 = jd1.bodyB->GetWorldPoint(jd1.localAnchorB);
			dis=b2-b1;
			jd1.length=dis.Length();
			test_joint[0] = m_world->CreateJoint(&jd1);*/

			b2RevoluteJointDef rjd;
			rjd.Initialize(test[0], test[1], b2Vec2(-30.0f, 2.0f));
			m_world->CreateJoint(&rjd);
			//end mine


			b2PolygonShape shape;
			shape.SetAsBox(0.5f, 0.5f);

			b2BodyDef bd;
			bd.type = b2_dynamicBody;

			bd.position.Set(-5.0f, 5.0f);
			m_bodies[0] = m_world->CreateBody(&bd);
			m_bodies[0]->CreateFixture(&shape, 5.0f);

			bd.position.Set(5.0f, 5.0f);
			m_bodies[1] = m_world->CreateBody(&bd);
			m_bodies[1]->CreateFixture(&shape, 5.0f);

			bd.position.Set(5.0f, 15.0f);
			m_bodies[2] = m_world->CreateBody(&bd);
			m_bodies[2]->CreateFixture(&shape, 5.0f);

			bd.position.Set(-5.0f, 15.0f);
			m_bodies[3] = m_world->CreateBody(&bd);
			m_bodies[3]->CreateFixture(&shape, 5.0f);

			b2DistanceJointDef jd;
			b2Vec2 p1, p2, d;

			jd.frequencyHz = 2.0f;
			jd.dampingRatio = 0.0f;

			jd.bodyA = ground;
			jd.bodyB = m_bodies[0];
			jd.localAnchorA.Set(-10.0f, 0.0f);
			jd.localAnchorB.Set(-0.5f, -0.5f);
			p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
			p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
			d = p2 - p1;
			jd.length = d.Length();
			m_joints[0] = m_world->CreateJoint(&jd);

			jd.bodyA = ground;
			jd.bodyB = m_bodies[1];
			jd.localAnchorA.Set(10.0f, 0.0f);
			jd.localAnchorB.Set(0.5f, -0.5f);
			p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
			p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
			d = p2 - p1;
			jd.length = d.Length();
			m_joints[1] = m_world->CreateJoint(&jd);

			jd.bodyA = ground;
			jd.bodyB = m_bodies[2];
			jd.localAnchorA.Set(10.0f, 20.0f);
			jd.localAnchorB.Set(0.5f, 0.5f);
			p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
			p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
			d = p2 - p1;
			jd.length = d.Length();
			m_joints[2] = m_world->CreateJoint(&jd);

			jd.bodyA = ground;
			jd.bodyB = m_bodies[3];
			jd.localAnchorA.Set(-10.0f, 20.0f);
			jd.localAnchorB.Set(-0.5f, 0.5f);
			p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
			p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
			d = p2 - p1;
			jd.length = d.Length();
			m_joints[3] = m_world->CreateJoint(&jd);

			jd.bodyA = m_bodies[0];
			jd.bodyB = m_bodies[1];
			jd.localAnchorA.Set(0.5f, 0.0f);
			jd.localAnchorB.Set(-0.5f, 0.0f);;
			p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
			p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
			d = p2 - p1;
			jd.length = d.Length();
			m_joints[4] = m_world->CreateJoint(&jd);

			jd.bodyA = m_bodies[1];
			jd.bodyB = m_bodies[2];
			jd.localAnchorA.Set(0.0f, 0.5f);
			jd.localAnchorB.Set(0.0f, -0.5f);
			p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
			p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
			d = p2 - p1;
			jd.length = d.Length();
			m_joints[5] = m_world->CreateJoint(&jd);

			jd.bodyA = m_bodies[2];
			jd.bodyB = m_bodies[3];
			jd.localAnchorA.Set(-0.5f, 0.0f);
			jd.localAnchorB.Set(0.5f, 0.0f);
			p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
			p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
			d = p2 - p1;
			jd.length = d.Length();
			m_joints[6] = m_world->CreateJoint(&jd);

			jd.bodyA = m_bodies[3];
			jd.bodyB = m_bodies[0];
			jd.localAnchorA.Set(0.0f, -0.5f);
			jd.localAnchorB.Set(0.0f, 0.5f);
			p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
			p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
			d = p2 - p1;
			jd.length = d.Length();
			m_joints[7] = m_world->CreateJoint(&jd);
		}
	}

	void Keyboard(int key)
	{
		switch (key)
		{
		case GLFW_KEY_B:
			for (int32 i = 0; i < 4; ++i)
			{
				if (m_bodies[i])
				{
					m_world->DestroyBody(m_bodies[i]);
					m_bodies[i] = NULL;
					break;
				}
			}
			break;

		case GLFW_KEY_J:
			for (int32 i = 0; i < 8; ++i)
			{
				if (m_joints[i])
				{
					m_world->DestroyJoint(m_joints[i]);
					m_joints[i] = NULL;
					break;
				}
			}
			break;
		}
	}

	void Step(Settings* settings)
	{
		Test::Step(settings);
		g_debugDraw.DrawString(5, m_textLine, "This demonstrates a soft distance joint.");
		m_textLine += DRAW_STRING_NEW_LINE;
		g_debugDraw.DrawString(5, m_textLine, "Press: (b) to delete a body, (j) to delete a joint");
		m_textLine += DRAW_STRING_NEW_LINE;
	}

	void JointDestroyed(b2Joint* joint)
	{
		for (int32 i = 0; i < 8; ++i)
		{
			if (m_joints[i] == joint)
			{
				m_joints[i] = NULL;
				break;
			}
		}
	}

	static Test* Create()
	{
		return new Web;
	}

	b2Body* m_bodies[4];
	b2Joint* m_joints[8];
	b2Body* test[2];
	b2Joint* test_joint[3];
};

#endif
