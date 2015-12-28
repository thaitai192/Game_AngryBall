#ifndef __MYCONTACTLISTENER_H__
#define __MYCONTACTLISTENER_H__

#include <Box2D/Box2D.h>
class MyContactListener: public b2ContactListener{
public:
	b2Body* m_previous;
//	irrklang::ISoundEngine *contactSound;
	int contact_id;
	void Create();
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
};

#endif