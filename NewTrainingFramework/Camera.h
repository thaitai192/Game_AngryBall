#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "../Utilities/math.h"
#include "../Utilities/utilities.h"
#include "Globals.h"

class Camera{
public:

	int m_ID;
	//GLuint vboId;
	bool is_update;

	Vector3 m_position;
	Vector3 m_target;
	Vector3 m_up;
	float m_ratio,m_fov,m_speed;
	float m_near, m_far;
	Matrix m_V, m_P, m_VP,m_World, R;

	Camera();
	~Camera();
	Camera(Vector3 pos, Vector3 tar);

	static Camera* getCamera();
	static void makeCamera();

	void movementForward(float deltaTime);
	void movementBackward(float deltaTime);
	void movementLeft(float deltaTime);
	void movementRight(float deltaTime);

	void rotationsUp(float deltaTime);
	void rotationsDown(float deltaTime);
	void rotationsLeft(float deltaTime);
	void rotationsRight(float deltaTime);

	void calculateViewMatrix();
	void calculatePMatrix();
	void calculateWorldMatrix();

	void Init();
	void calculateVP();

	Matrix getVP();
	void update(float deltaTime, unsigned char keyevent);
	//void putPosition();

	

	
};

#endif