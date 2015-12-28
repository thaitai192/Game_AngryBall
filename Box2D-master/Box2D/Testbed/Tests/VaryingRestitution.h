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

#ifndef VARYING_RESTITUTION_H
#define VARYING_RESTITUTION_H

// Note: even with a restitution of 1.0, there is some energy change
// due to position correction.
class VaryingRestitution : public Test
{
public:

	VaryingRestitution()
	{
		b2BodyDef myBodyDef;
      myBodyDef.type = b2_staticBody;
      myBodyDef.position.Set(0, 0);
      b2Body* staticBody = m_world->CreateBody(&myBodyDef);
  
      //shape definition
      b2PolygonShape polygonShape;
    
      //fixture definition
      b2FixtureDef myFixtureDef;
      myFixtureDef.shape = &polygonShape;
      
      //add four walls to the static body
      polygonShape.SetAsBox( 20, 1, b2Vec2(0, 0), 0);//ground
      staticBody->CreateFixture(&myFixtureDef);
      polygonShape.SetAsBox( 20, 1, b2Vec2(0, 40), 0);//ceiling
      staticBody->CreateFixture(&myFixtureDef);
      polygonShape.SetAsBox( 1, 20, b2Vec2(-20, 20), 0);//left wall
      staticBody->CreateFixture(&myFixtureDef);
      polygonShape.SetAsBox( 1, 20, b2Vec2(20, 20), 0);//right wall
      staticBody->CreateFixture(&myFixtureDef);
	}

	static Test* Create()
	{
		return new VaryingRestitution;
	}
};

#endif
