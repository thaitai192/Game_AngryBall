#ifndef __GS_HIGHSCORE_H__
#define __GS_HIGHSCORE_H__

#include "StateManager.h"
#include "Text.h"
#include "CButton.h"

class GS_HighScore :public StateBase{
public:
	GS_HighScore();
	static GS_HighScore* s_Instance;
	static GS_HighScore* GetIS();
	//GS_HighScore(int newScore);
	CButton* btnBack;
	Object *backgroundHighScore;
	Object *table;
	Text *NameAndScore;
	int NumOfHighScore;
	char name[10][255];
	int score[10];
	char *file_txt;
	int m_star[10];
	/*int m_newScore;
	char newname[100];
	int index_newScore, m_dem;*/
	
	void Init(char* txt);
	void Create();
	void Update(float deltaTime);
	void Render();
	void KeyEvent(unsigned char key, bool bIsPressed);
	void MouseEvent(int x, int y, int type);
	void WriteFile(char* link);
	void OnButtonBackListener();
	void Check_newScore(int new_score,int new_star, int map_index);
	void Clean();

	~GS_HighScore();

};

#endif