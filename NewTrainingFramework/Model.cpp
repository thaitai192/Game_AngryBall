
#include "Model.h"
#include <string.h>

Model::Model(){
	
}


void Model::Init(char* pos_link,  char* heightmap_link){
	FILE *f = fopen(pos_link,"r");
	if(f==NULL) return;
	fscanf(f, "NrVertices: %d\n", &numberOfVertices);

	Vertex2 *vertices= new Vertex2[numberOfVertices];
	for(int i=0; i<numberOfVertices; i++){
		fscanf(f,"   %*d. pos:[%f, %f, %f]; \
				 norm:[%*f, %*f, %*f]; binorm:[%*f, %*f, %*f]; tgt:[%*f, %*f, %*f]; \
				 uv:[%f, %f];\n"\
				 ,&vertices[i].pos.x,&vertices[i].pos.y,&vertices[i].pos.z, &vertices[i].uv.x, &vertices[i].uv.y);

	}
	//xuly height map
	if(strcmp(heightmap_link,"\"\"")!=0){
			loadHeightmap(strtok(heightmap_link+1,"\""),vertices);
	}
	
	fscanf(f,"NrIndices: %d",&numberOfIndices);
	int *indices = new int[numberOfIndices];
	for(int i=0; i<numberOfIndices/3; i++){
		fscanf(f,"   %*d.    %d,    %d,    %d\n", &indices[3*i],&indices[3*i+1], &indices[3*i+2]);

		
	}

	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2)*numberOfVertices, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//put index
	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices)*numberOfIndices, indices,
	GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	delete[] vertices;
	delete[] indices;
	fclose(f);
}

void Model::loadHeightmap(char* link, Vertex2 vertices[]){
	int iWidth, iHeight, rgb;
	FILE *f=fopen(link,"r");
	
	fseek(f, 0, SEEK_END);    // Go to end
	int length = ftell(f);

	fseek(f, SEEK_SET, 0);	//go to start
	unsigned char * heightData= new unsigned char[length];
	fread(heightData, length, 1, f);
	for(int i=0; i<numberOfVertices; i++){
		vertices[i].pos.y= getHeightAt(heightData, vertices[i].uv, length);
	}
	delete heightData;
	fclose(f);

}
float Model::getHeightAt(unsigned char* heightmapData, Vector2 uv, int length){
	float a= sqrt((float)length);
	int u_bot=floor(uv.x*(a-1));
	int u_top= ceil(uv.x*(a-1));
	int v_bot = floor(uv.y*(a-1));
	int v_top= ceil(uv.y*(a-1));
	int u= (uv.x-u_bot)<=(u_top-uv.x)?u_bot:u_top;
	int v= (uv.y- v_bot)<=(v_top-uv.y)?v_bot:v_top;
	//float out= (uv.y*(a-1))*(a)+ (uv.x*(a-1));
	int out = v*a + u;
	
	return heightmapData[out];
}
Model::~Model(){
	
}