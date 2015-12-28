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

#ifndef SPHERE_STACK_H
#define SPHERE_STACK_H

class SphereStack : public Test
{
public:

	enum
	{
		e_count = 10
	};

	SphereStack()
	{
		b2Body* ground1 = NULL;
		b2BodyDef bd1;
		ground1 = m_world->CreateBody(&bd1);
		b2EdgeShape shape1;
		shape1.Set(b2Vec2(-40.0f, 20.0f), b2Vec2(40.0f, 20.0f));
		ground1->CreateFixture(&shape1, 1.0f);

					ground1 = m_world->CreateBody(&bd1);
					shape1.Set(b2Vec2(-20.0f, 0.0f), b2Vec2(20.0f, 0.0f));
					ground1->CreateFixture(&shape1, 1.0f);
	}

	void Step(Settings* settings)
	{
		Test::Step(settings);

		//for (int32 i = 0; i < e_count; ++i)
		//{
		//	printf("%g ", m_bodies[i]->GetWorldCenter().y);
		//}

		//for (int32 i = 0; i < e_count; ++i)
		//{
		//	printf("%g ", m_bodies[i]->GetLinearVelocity().y);
		//}

		//printf("\n");
	}

	static Test* Create()
	{
		return new SphereStack;
	}

	b2Body* m_bodies[e_count];
};

#endif
