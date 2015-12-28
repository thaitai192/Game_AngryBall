#include "MyContactListener.h"
#include "Sprite.h"
#include "StateManager.h"
#include "Map.h"
#include "SoundManager.h"
void MyContactListener::Create(){
	//m_previous=NULL;
}
void MyContactListener::BeginContact(b2Contact* contact){
	b2Body *bodyUserData[2];
	bodyUserData[0]= contact->GetFixtureA()->GetBody();
	bodyUserData[1]= contact->GetFixtureB()->GetBody();
	Map* tmp= (Map*)(getStateIS()->GetCurrentState());
	for(int i=0;i<2;i++)
	{
		if(bodyUserData[i]==tmp->m_display[0].m_body)
		{
			for(int j=1;j<tmp->numOfDisplay;j++)
			{
				if(bodyUserData[1-i]==tmp->m_display[j].m_body)
				{
					tmp->m_display[j].time_show_score=600;
					if(tmp->m_display[j].m_ID==26)
					{
						tmp->m_display[j].m_body->SetLinearVelocity(b2Vec2(10, 0));
						tmp->m_star++;
						GetSoundInstance()->playSound(3);
						tmp->m_display[j].time_show_score=600;
						//break;
					}
					if(tmp->m_display[j].m_score!=0) GetSoundInstance()->playSound(2);
					tmp->m_score+=tmp->m_display[j].m_score;
					break;
				}

			}
			
			break;
		}
	}

	//b2Body* bodyUserData = contact->GetFixtureA()->GetBody();
	//b2Body* bodyUserData2 = contact->GetFixtureB()->GetBody();

	//Map* tmp= (Map*)(getStateIS()->GetCurrentState());
	//if ( bodyUserData ==tmp->m_display[0].m_body )
	//{
	//	for(int i=1; i<tmp->numOfDisplay; i++)
	//	{
	//		if(bodyUserData2==tmp->m_display[i].m_body)
	//		{
	//			//if(tmp->m_display[i].m_ID==6) GetSoundInstance()->playSound(2);
	//		}
	//	}
	//}

	//else
	//{
	//	if ( bodyUserData2 ==tmp->m_display[0].m_body )
	//	{
	//		for(int i=1; i<tmp->numOfDisplay; i++)
	//		{
	//			if(bodyUserData==tmp->m_display[i].m_body)
	//			{
	//				tmp->m_display[i].time_show_score=100;
	//				if(tmp->m_display[i].m_ID==6)GetSoundInstance()->playSound(SOUND_GET_A_SCORE);
	//				if(tmp->m_display[i].m_ID==26)
	//				{
	//					tmp->m_display[i].m_body->SetLinearVelocity(b2Vec2(10, 0));
	//					tmp->m_star++;
	//					tmp->m_display[i].time_show_score=10;
	//				}
	//				if(m_previous==NULL||(m_previous!=NULL&&m_previous!=bodyUserData))
	//				{
	//					tmp->m_score+=tmp->m_display[i].m_score;
	//					m_previous=tmp->m_display[i].m_body;
	//				}

	//				break;
	//			}
	//		}
	//	}
	//}
}

void MyContactListener::EndContact(b2Contact* contact){
}