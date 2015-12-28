#include "Camera.h"
#include "define.h"



Camera::Camera(){
	is_update=false;
	m_up=Vector3(0.0, 1.0, 0.0);
	m_position=Vector3(0.0,0.0,5.0);
	m_target=Vector3(0.0,0.0,0.0);
	m_ratio=(float)Globals::screenWidth/(float) Globals::screenHeight;
	m_fov=1.0; m_speed=3;
	m_near=0.1;
	m_far=500;
}

void Camera::Init(){}
Camera::Camera(Vector3 pos, Vector3 tar){
	m_position=pos;
	m_target=tar;
	m_up=Vector3(0.0, 1.0, 0.0);

	m_ratio=(float)Globals::screenWidth/ Globals::screenHeight;
	m_fov=2; m_speed=0.1;
	m_near=0.1;
	m_far=100;
}

void Camera::movementForward( float deltaTime){
	Vector3 deltaMove= -(m_position-m_target).Normalize()*deltaTime*m_speed;
	m_position+=deltaMove;
	m_target+=deltaMove;

	

}
void Camera::movementBackward(float deltaTime){
	Vector3 deltaMove= (m_position-m_target).Normalize()*deltaTime*m_speed;
	m_position+=deltaMove;
	m_target+=deltaMove;

	
}
void Camera::movementLeft(float deltaTime){
	Vector3 deltaMove= -m_up.Cross(m_position-m_target).Normalize()*deltaTime*m_speed;
	m_position+=deltaMove;
	m_target+=deltaMove;

}

void Camera::movementRight(float deltaTime){
	Vector3 deltaMove= m_up.Cross(m_position-m_target).Normalize()*deltaTime*m_speed;
	m_position+=deltaMove;
	m_target+=deltaMove;


}


void Camera::rotationsUp(float deltaTime){
	Matrix tmp;
	calculateWorldMatrix();
	R.SetRotationX(deltaTime*m_speed);

	Vector4 localTarget=Vector4(m_target,1.0)*m_V;
	Vector4 localNewTarget = localTarget * R;
	Vector4 worldNewTarget=localNewTarget* m_World;
	
	m_target=Vector3(worldNewTarget.x,worldNewTarget.y,worldNewTarget.z);

	
}
void Camera::rotationsDown(float deltaTime){
	Matrix tmp;
	calculateWorldMatrix();
	R.SetRotationX(-deltaTime*m_speed);

	Vector4 localTarget=Vector4(m_target,1.0)*m_V;
	Vector4 localNewTarget = localTarget * R;
	Vector4 worldNewTarget=localNewTarget* m_World;
	
	m_target=Vector3(worldNewTarget.x,worldNewTarget.y,worldNewTarget.z);


}
void Camera::rotationsLeft(float deltaTime){
	Matrix tmp;
	calculateWorldMatrix();
	R.SetRotationY(deltaTime*m_speed);

	Vector4 localTarget=Vector4(m_target,1.0)*m_V;
	Vector4 localNewTarget = localTarget * R;
	Vector4 worldNewTarget=localNewTarget* m_World;
	
	m_target=Vector3(worldNewTarget.x,worldNewTarget.y,worldNewTarget.z);


}
void Camera::rotationsRight(float deltaTime){
	Matrix tmp;
	calculateWorldMatrix();
	R.SetRotationY(-deltaTime*m_speed);

	Vector4 localTarget=Vector4(m_target,1.0)*m_V;
	Vector4 localNewTarget = localTarget * R;
	Vector4 worldNewTarget=localNewTarget* m_World;
	
	m_target=Vector3(worldNewTarget.x,worldNewTarget.y,worldNewTarget.z);


}


void Camera::calculateViewMatrix(){
	Vector3 zaxis= (m_position-m_target).Normalize();
	Vector3 xaxis= (m_up.Cross(zaxis)).Normalize();
	Vector3 yaxis= (zaxis.Cross(xaxis)).Normalize();

	m_V.m[0][0]=xaxis.x;		m_V.m[0][1]=yaxis.x;	m_V.m[0][2]=zaxis.x;		m_V.m[0][3]=0.0;
	m_V.m[1][0]=xaxis.y;		m_V.m[1][1]=yaxis.y;	m_V.m[1][2]=zaxis.y;		m_V.m[1][3]=0.0;
	m_V.m[2][0]=xaxis.z;		m_V.m[2][1]=yaxis.z;	m_V.m[2][2]=zaxis.z;		m_V.m[2][3]=0.0;
	m_V.m[3][0]=-m_position.Dot(xaxis);		m_V.m[3][1]=-m_position.Dot(yaxis);	m_V.m[3][2]=-m_position.Dot(zaxis);		m_V.m[3][3]=1.0;

}
void Camera::calculatePMatrix(){
	//chieu phoi canh
	//m_P.SetPerspective(m_fov, m_ratio, m_near, m_far);
	
	//chieu truc giao
	m_P.SetScale(Vector3(0.01,0.017777777778,0.01));
//	m_P.SetScale(0.01);
}

void Camera::calculateWorldMatrix(){
	Matrix T;
	T.SetIdentity();
	T.m[3][0]=m_position.x;
	T.m[3][1]=m_position.y;
	T.m[3][2]=m_position.z;

	Vector3 zaxis= (m_position-m_target).Normalize();
	Vector3 xaxis= (m_up.Cross(zaxis)).Normalize();
	Vector3 yaxis= (zaxis.Cross(xaxis)).Normalize();

	R.SetIdentity();
	R.m[0][0]=xaxis.x;	R.m[0][1]=xaxis.y;	R.m[0][2]=xaxis.z;
	R.m[1][0]=yaxis.x;	R.m[1][1]=yaxis.y;	R.m[1][2]=yaxis.z;
	R.m[2][0]=zaxis.x;	R.m[2][1]=zaxis.y;	R.m[2][2]=zaxis.z;
	m_World=R*T;

}

void Camera::calculateVP(){
	if(!is_update){
		calculateViewMatrix();
		calculatePMatrix();
		m_VP=m_V*m_P;
		is_update=true;
	}
}
Matrix Camera::getVP(){
	return m_VP;
}

//void Camera::putPosition(){
//	glGenBuffers(1, &vboId);
//	glBindBuffer(GL_ARRAY_BUFFER, vboId);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(m_position),(GLvoid*)m_position,GL_STATIC_DRAW);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//}
Camera::~Camera(){

}

void Camera::update(float deltaTime, unsigned char keyevent){
	if(keyevent & MOVE_FORWARD)		movementForward(deltaTime);
	if(keyevent & MOVE_BACKWARD)	movementBackward(deltaTime);
	if(keyevent & MOVE_LEFT)		movementLeft(deltaTime);
	if(keyevent & MOVE_RIGHT)		movementRight(deltaTime);
	
	if(keyevent & ROTATION_UP)		rotationsUp(deltaTime/2);
	if(keyevent & ROTATION_DOWN)	rotationsDown(deltaTime/2);
	if(keyevent & ROTATION_LEFT)	rotationsLeft(deltaTime/2);
	if(keyevent & ROTATION_RIGHT)	rotationsRight(deltaTime/2);
	is_update=false;
	calculateVP();
}