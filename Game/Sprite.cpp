#include "Sprite.h"
#include "string.h"
#include "stdio.h"
//#include "Game.h"
#include "define.h"
#include "SceneManager.h"


Sprite::Sprite(void){
	force= 0;
	is_display=true;
	m_score=0;
	is_playAnimation = false;
	is_sensor=false;
	m_body=NULL;
	time_show_score=0;
	m_score=0;
	m_scale= Vector3(0.0f,0.0f,0.0f);
	m_rotation=Vector3(0.0f,0.0f,0.0f);
	m_position= Vector3(0.0f,0.0f,0.0f);
}

void Sprite::Clone(Object *ob){
	m_ID= ob->m_ID;
	numOfTexture=ob->numOfTexture;
	m_position =  Vector3(ob->m_position);

	m_rotation =  Vector3(ob->m_rotation);
	m_scale = Vector3(ob->m_scale);
	m_model = ob->m_model;
	m_myShaders = ob->m_myShaders;
	m_texture_list= new Texture*[numOfTexture];
	for(int i=0; i<numOfTexture; i++){
		m_texture_list[i]=ob->m_texture_list[i];
	}

	strcpy(m_type,ob->m_type);
	strcpy(m_shape, ob->m_shape);
	m_density= ob->m_density;
	m_friction =  ob->m_friction;
	m_restitution=ob->m_restitution;

	if(numOfTexture>=2)
		m_currentTexture=1;
	else m_currentTexture=0;
	is_sensor=false;
}
Sprite::Sprite(Object *ob){
	m_body=NULL;
	m_ID= ob->m_ID;
	numOfTexture=ob->numOfTexture;
	m_position =  Vector3(ob->m_position);
	m_rotation =  Vector3(ob->m_rotation);
	m_scale = Vector3(ob->m_scale);
	m_model = ob->m_model;
	m_myShaders = ob->m_myShaders;

	m_texture_list= new Texture*[numOfTexture];
	for(int i=0; i<numOfTexture; i++){
		m_texture_list[i]=ob->m_texture_list[i];
	}

	strcpy(m_type,ob->m_type);
	strcpy(m_shape, ob->m_shape);
	m_density= ob->m_density;
	m_friction =  ob->m_friction;
	m_restitution=ob->m_restitution;
	if(numOfTexture>=2)
		m_currentTexture=1;
	else m_currentTexture=0;
	m_fps= FPS_DEFAULT;
	force=0;
	is_display=true;
	m_score=0;
	is_sensor=false;
	time_show_score=0;
}
void Sprite::Render(){
	if(is_display){
		//m_myShaders->enableStates();	

		Camera *camera= GetSMInstance()->getCamera();
		//tinh matrix mvp
		updateSRT();
		camera->calculateVP();
		glBindBuffer(GL_ARRAY_BUFFER, m_model->vboId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_model->iboId);

		glUseProgram(m_myShaders->program);
		if(m_myShaders->positionAttribute != -1)
		{
			glEnableVertexAttribArray(m_myShaders->positionAttribute);
			glVertexAttribPointer(m_myShaders->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2), 0);
		}
		if(m_myShaders->uvAttribute!=-1){
			glEnableVertexAttribArray(m_myShaders->uvAttribute);
			glVertexAttribPointer(m_myShaders->uvAttribute, 2, GL_FLOAT,GL_FALSE,sizeof(Vertex2),(GLvoid*)sizeof(Vector3));
		}

		if(m_myShaders->mvpUniform!=-1){
			glUniformMatrix4fv(m_myShaders->mvpUniform,1, GL_FALSE,(GLfloat*) (m_SRT* camera->m_VP).m);
		}

		if(m_myShaders->ForceUniform!=-1){
			glUniform1f(m_myShaders->ForceUniform,force/FORCE_MAX);
		}

		if(m_myShaders->MaskLocation!=-1)
			glUseProgram(m_myShaders->program);
		/*if(m_myShaders->positionAttribute != -1)
		{
			glEnableVertexAttribArray(m_myShaders->positionAttribute);
			glVertexAttribPointer(m_myShaders->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2), 0);
		}
		if(m_myShaders->uvAttribute!=-1){
			glEnableVertexAttribArray(m_myShaders->uvAttribute);
			glVertexAttribPointer(m_myShaders->uvAttribute, 2, GL_FLOAT,GL_FALSE,sizeof(Vertex2),(GLvoid*)sizeof(Vector3));
		}

		if(m_myShaders->mvpUniform!=-1){
			glUniformMatrix4fv(m_myShaders->mvpUniform,1, GL_FALSE,(GLfloat*) (m_SRT* camera->m_VP).m);
		}

		if(m_myShaders->ForceUniform!=-1){
			glUniform1f(m_myShaders->ForceUniform,force/200);
		}
		if(m_myShaders->TimeUniform!=-1)
			glUniform1f(m_myShaders->TimeUniform,runtime);*/

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		if(m_myShaders->MaskLocation!=-1)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_texture_list[0]->textureID);
			glUniform1i(m_myShaders->MaskLocation,0);
			if(m_myShaders->textureLocation!=-1)
			{
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, m_texture_list[m_currentTexture]->textureID);
				glUniform1i(m_myShaders->textureLocation,1);
			}
		}
		else
		{
			if(m_myShaders->textureLocation!=-1)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, m_texture_list[m_currentTexture]->textureID);
				glUniform1i(m_myShaders->textureLocation,0);
			}
		}
		/*if(m_myShaders->mUniform!=-1)
		glUniformMatrix4fv(m_myShaders->mUniform, 1,GL_FALSE,(GLfloat*)m_SRT.m);*/

		glDrawElements(GL_TRIANGLES, m_model->numberOfIndices, GL_UNSIGNED_INT, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		//glBindTexture(GL_TEXTURE_2D,0);
		//m_myShaders->disableStats();
	}

	//show score
	if(time_show_score!=0&&m_score!=0){
		char line[50];
		sprintf(line, " %d", m_score);
		Vector3 out;
		out.x=(m_position.x+EDGE_RECTANGLE)/2/EDGE_RECTANGLE*Globals::screenWidth;
		out.y= (m_position.y+HEIGHT_RECTANGLE)/2/HEIGHT_RECTANGLE*Globals::screenHeight+20;
		Text::TEXT_ARIAL->RenderTextRenderString(line, Vector4(0,1,1,1), out.x, out.y, (float)time_show_score/300, (float)time_show_score/300);
	}
}

void Sprite::Update(float deltaTime){
	m_position.x= m_body->GetPosition().x/SCALE_BOX2D;
	m_position.y= m_body->GetPosition().y/SCALE_BOX2D;
	m_rotation.z=m_body->GetAngle();
	playAnimation();

	//runtime+=0.1
	srt_update= false;
	if(time_show_score>0) time_show_score-=deltaTime*1000;
	else time_show_score=0;
}
void Sprite::updateSRT(){
	if(!srt_update){
		Matrix S, Rx, Ry, Rz, T;		
		S.SetScale(m_scale.x, m_scale.y, m_scale.z);
		T.SetTranslation(m_position.x, m_position.y, m_position.z);
		Rx.SetRotationX(m_rotation.x);
		Ry.SetRotationY(m_rotation.y);
		Rz.SetRotationZ(m_rotation.z);
		m_SRT=S*Rx*Ry*Rz*T;
		srt_update=true;
	}
}

void Sprite::Loadtobox2D(b2World* world){
	b2BodyDef bd;
	if(strcmp(m_type,"b2_dynamicBody")==0){
		bd.type= b2_dynamicBody;
	}else{
		if(strcmp(m_type, "b2_kinematicBody")==0){
			bd.type= b2_kinematicBody;
		}else if(strcmp(m_type, "b2_staticBody")==0)
			bd.type = b2_staticBody;
	}
	bd.position.Set(m_position.x*SCALE_BOX2D, m_position.y*SCALE_BOX2D);
	bd.angle=m_rotation.z;

	b2FixtureDef fd;
	fd.density=m_density;
	fd.friction=m_friction;
	fd.restitution=m_restitution;

	b2PolygonShape shape;
	b2CircleShape shape_cirle;
	b2EdgeShape shape_edge;
	//bucket
	if(strcmp(m_shape, "b2_L_U_R_Edge")==0){
		b2BodyDef bd1;
		b2Body* ground = world->CreateBody(&bd1);
		b2EdgeShape shape1;
		shape1.Set(b2Vec2((m_position.x-EDGE_RECTANGLE*m_scale.x)*SCALE_BOX2D, (m_position.y+EDGE_RECTANGLE*m_scale.y)*SCALE_BOX2D), 
			b2Vec2((m_position.x-EDGE_RECTANGLE*m_scale.x+3)*SCALE_BOX2D, (m_position.y-EDGE_RECTANGLE*m_scale.y)*SCALE_BOX2D));
		fd.shape=&shape1;
		ground->CreateFixture(&fd);

		ground = world->CreateBody(&bd1);
		b2EdgeShape shape2;
		shape2.Set(b2Vec2((m_position.x+EDGE_RECTANGLE*m_scale.x)*SCALE_BOX2D, (m_position.y+EDGE_RECTANGLE*m_scale.y)*SCALE_BOX2D), 
			b2Vec2((m_position.x+EDGE_RECTANGLE*m_scale.x-3)*SCALE_BOX2D, (m_position.y-EDGE_RECTANGLE*m_scale.y)*SCALE_BOX2D));
		fd.shape=&shape2;
		ground->CreateFixture(&fd);

		ground = world->CreateBody(&bd1);
		b2EdgeShape shape3;
		shape3.Set(b2Vec2((m_position.x-EDGE_RECTANGLE*m_scale.x)*SCALE_BOX2D, (m_position.y-EDGE_RECTANGLE*m_scale.y)*SCALE_BOX2D), 
			b2Vec2((m_position.x+EDGE_RECTANGLE*m_scale.x)*SCALE_BOX2D, (m_position.y-EDGE_RECTANGLE*m_scale.y)*SCALE_BOX2D));
		fd.shape=&shape3;
		ground->CreateFixture(&fd);

		shape_edge.Set(b2Vec2(0.0, 0.0), b2Vec2(0.0, 0.0));
		fd.shape=&shape_edge;

	}else{
		if(strcmp(m_shape, "b2PolygonShape")==0){
			//b2PolygonShape shape;
			/*shape.SetAsBox(EDGE_RECTANGLE*m_scale.x*SCALE_BOX2D, EDGE_RECTANGLE*m_scale.y*SCALE_BOX2D);
			fd.shape=&shape;*/
			//port android, replace by edge
			/*if(!IS_WIN32){
				b2BodyDef bd1;
				b2Body* ground = world->CreateBody(&bd1);
				b2EdgeShape shape1;
				shape1.Set(b2Vec2((m_position.x-EDGE_RECTANGLE*m_scale.x)*SCALE_BOX2D, (m_position.y+EDGE_RECTANGLE*m_scale.y)*SCALE_BOX2D), 
					b2Vec2((m_position.x+EDGE_RECTANGLE*m_scale.x+3)*SCALE_BOX2D, (m_position.y+EDGE_RECTANGLE*m_scale.y)*SCALE_BOX2D));
				fd.shape=&shape1;
				ground->CreateFixture(&fd);
			}*/

			b2Vec2 vertices[4];
			vertices[0] = b2Vec2((-EDGE_RECTANGLE*m_scale.x)*SCALE_BOX2D, 
										(EDGE_RECTANGLE*m_scale.y)*SCALE_BOX2D);
			vertices[1] = b2Vec2((EDGE_RECTANGLE*m_scale.x)*SCALE_BOX2D, 
										(EDGE_RECTANGLE*m_scale.y)*SCALE_BOX2D);
			vertices[2] = b2Vec2((EDGE_RECTANGLE*m_scale.x)*SCALE_BOX2D, 
										(-EDGE_RECTANGLE*m_scale.y)*SCALE_BOX2D);
			vertices[3] = b2Vec2((-EDGE_RECTANGLE*m_scale.x)*SCALE_BOX2D, 
										(-EDGE_RECTANGLE*m_scale.y)*SCALE_BOX2D);
			shape.Set(vertices, 4);
			fd.shape=&shape;

			
			
		}else {
			if(strcmp(m_shape, "b2CircleShape")==0){
				shape_cirle.m_radius= EDGE_RECTANGLE*m_scale.x*SCALE_BOX2D;
				fd.shape=&shape_cirle;
			}else{
				if(strcmp(m_shape, "b2EdgeShape")==0){
					shape_edge.Set(b2Vec2(-EDGE_RECTANGLE*m_scale.x*SCALE_BOX2D, EDGE_RECTANGLE*m_scale.y*SCALE_BOX2D), b2Vec2(EDGE_RECTANGLE*m_scale.x*SCALE_BOX2D, EDGE_RECTANGLE*m_scale.y*SCALE_BOX2D));
					fd.shape=&shape_edge;
				}
				else{	
				}
			}
		}
	}
	fd.isSensor=is_sensor;
	m_body=world->CreateBody(&bd);
	m_body->CreateFixture(&fd);
}

void Sprite::updateTexture()
{
	/*m_texture_list[m_currentTexture]= AnimationInstance()->getTexture();
	AnimationInstance()->Update();*/
}

void Sprite::playAnimation()
{
	if(is_playAnimation)
	{
		AnimationInstance()->Update(currentAnimation);
		m_texture_list[m_currentTexture]= AnimationInstance()->getTexture(currentAnimation);
		if(AnimationInstance()->currentIndexFrame[currentAnimation]==AnimationInstance()->numberFrames[currentAnimation]-1)
		{
			is_playAnimation= false;
			AnimationInstance()->currentIndexFrame[currentAnimation]=0;
		}
	}
}

void Sprite::setTexture(int animationID, int frameID)
{
	m_texture_list[m_currentTexture]= AnimationInstance()->getTexture(animationID, frameID);
}

Sprite::~Sprite(){
	//if(m_body)  m_body=NULL;
}

bool Sprite::isTouch(int x, int y){
	Vector3 pos= m_position;
	Vector3 scale = m_scale;
	Vector3 tmp = Vector3(x-pos.x, y-pos.y, 0);
	
	Vector3 identifyX= Vector3(1,0,0);
	float alpha_cos= tmp.Dot(identifyX)/tmp.Length()/identifyX.Length();
	float alpha= acos(alpha_cos);
	if(tmp.y<0) alpha=-alpha;
	
	alpha-= m_rotation.z;
	x=tmp.Length()*cos(alpha);
	y=tmp.Length()*sin(alpha);
	x+=pos.x;
	y+=pos.y;
	if(x < pos.x+EDGE_RECTANGLE*scale.x && x > pos.x - EDGE_RECTANGLE*scale.x&&
		y < pos.y+ EDGE_RECTANGLE*scale.y&& y > pos.y - EDGE_RECTANGLE*scale.y)
			return true;
	return false;
}