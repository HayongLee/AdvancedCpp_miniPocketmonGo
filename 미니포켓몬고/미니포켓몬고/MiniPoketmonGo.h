#pragma once
#include "MonsterData.h"
#include "Ball.h"
#include "FileManager.h"

class MiniPoketmonGo
{
	FileManager* fm;		//파일 관리자
	Player* player;		//게임 플레이어
	vector<MonsterData> monstersData;	//몬스터 데이터
	vector<Ball> balls;		//몬스터볼 데이터

public:
	MiniPoketmonGo();
	~MiniPoketmonGo();
	void loadData();	
	/*
	void saveData();

	*/
	void run();
	int menu_main();
	void menuPlayer();
	void menuMonster();
	void menuBuy();
	string getMonsterName(int id); 
	//void menuGetPoketmon();
	//void menuExit();
	
	void debug();
};

