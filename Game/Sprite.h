#ifndef __SPRITE_H__
#define __SPRITE_H__
#pragma once
#include <Box2D/Box2D.h>
#include "Object.h"
#include "Texture.h"
#include "AnimSprite.h"
#include "Text.h"

class Sprite:public Object{
public:
	b2Body* m_body;
	bool is_sensor;
	float m_fps;
	int m_currentTexture;
	int numOfAnimation;
	int currentAnimation;
	float force;
	bool is_display;
	int m_score, time_show_score;
	bool is_playAnimation;
	Sprite(void);
	Sprite(Object *ob);
	void Clone(Object *ob);
	void Rotate(Vector3 rotate);
	void Scale(Vector3 scale);
	void Translate(Vector3 translate);
	void Render();
	void Update(float deltaTime);
	void updateSRT();
	void updateTexture();
	void setTexture(int animationID, int frameID);
	void playAnimation();
	bool isTouch(int x, int y);
	void Loadtobox2D(b2World* world);
	~Sprite();
};
#endif