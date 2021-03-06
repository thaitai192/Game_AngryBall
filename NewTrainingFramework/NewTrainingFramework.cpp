// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
//#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include "define.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "CubeTexture.h"
#include "Fog.h"

int Init ( ESContext *esContext )
{	
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
	
	//load RM SM
	GetRMInstace()->Init("RM.txt");
	GetSMInstance()->Init("SM.txt");

	Fog::getInstance();
	return 0;
}

void Draw ( ESContext *esContext )
{	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	
	GetSMInstance()->Render();
	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{
	GetSMInstance()->Update(deltaTime);
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{		
	GetSMInstance()->setKeyevent(key,bIsPressed);
}

void CleanUp()
{
	delete GetRMInstace();
	delete GetSMInstance();
	delete Fog::getInstance();
}

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}
