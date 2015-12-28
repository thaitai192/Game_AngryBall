#ifndef __STATEBASE_H__
#define __STATEBASE_H__

class StateBase{
public:
	virtual void Create()=0;
	//virtual bool Release();

	virtual void Render()=0;
	virtual void Update(float deltaTime)=0;
	virtual void Clean()=0;
	virtual void KeyEvent(unsigned char key, bool bIsPressed)=0;
	virtual void MouseEvent(int x, int y, int type)=0;

};

#endif