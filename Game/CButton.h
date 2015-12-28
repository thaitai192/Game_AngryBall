#ifndef  ____CBUTTON_H____
#define	 ____CBUTTON_H____

#include "Sprite.h"
#include "Text.h"
//#include "../Utilities/math.h"

class CButton:public Sprite{
public:

	char* buttName;
	Vector4 text_color;
	Vector3 text_pos;
	float text_scaleX, text_scaleY;
	bool is_active;

	Text title;
	CButton();
	Vector3 buttpos;
	CButton(char* buttname, Vector4 color, float scaleX, float scaleY, Object* obj, Vector3 position);
	void Init(char* buttname, Vector4 color, float scaleX, float scaleY, Object* obj, Vector3 position);
	void Render();
	void Update(float deltaTime);
	Vector3 getTextPos();
	bool isTouch(int x, int y);
	void Clean();
	~CButton();
};
#endif