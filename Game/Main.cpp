// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include <Box2D/Box2D.h>

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
//#include "Application_android.cpp"
#include "Game.h"
using namespace irrklang;
//#pragma comment(lib, "irrKlang.lib")
int Init ( ESContext *esContext )
{	
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
	//load RM SM, physicengine
	return GetGameIS()->Init(LINK_RM, LINK_SM, LINK_MAP);
}

void Draw ( ESContext *esContext )
{	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	
	GetGameIS()->Render();
	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{
	GetGameIS()->Update(deltaTime);
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{		
	GetGameIS()->KeyEvent(key, bIsPressed);
}

void TouchActionDown(ESContext *esContext,int x, int y)
{
	GetGameIS()->MouseDown(x,y);
}

void TouchActionUp(ESContext *esContext,int x, int y)
{
	GetGameIS()->MouseUp(x,y);
}

void TouchActionMove(ESContext *esContext,int x, int y)
{
	GetGameIS()->MouseDrag(x,y);
}

void CleanUp()
{
	delete GetGameIS();
}

int main()
{
	//ISoundEngine* engine= createIrrKlangDevice();
	//engine->play2D("../Resources/Sound/ophelia.mp3",true);
	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Angry Ball", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	//mouse event
	esRegisterMouseDownFunc(&esContext, TouchActionDown);
	esRegisterMouseUpFunc(&esContext, TouchActionUp);
	esRegisterMouseMoveFunc(&esContext, TouchActionMove);

	esMainLoop ( &esContext );
	//delete AnimSprite::getInstance();
	//releasing OpenGL resources
	CleanUp();
	//engine->drop();
	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}
