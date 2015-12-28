#include "fog.h"

Fog::Fog(void){

	fogStart=1;
	fogLength=500;
	fogColor=Vector3(0.65,0.65,0.65);
	
}
Fog* Fog::s_Instance=NULL;
Fog* Fog::getInstance(){
	if(!s_Instance) s_Instance=new Fog();
	return s_Instance;
}