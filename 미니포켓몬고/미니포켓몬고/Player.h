#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "BallPocket.h"
#include "Monster.h"
using namespace std;

class Player
{
	string name;//이름
	int sex;	//성별 1:남자/2:여자
	int money;	//소지금
	int maxMonster; //최대 잡을 수 있는 몬스터의 수
	int maxBall;	//최대 소유 몬스터볼 수
	int ballKind;	//가진 볼의 정보수
	vector<BallPocket> ballPocket;  //소유한 볼 
	int monsterCount; //포획한 몬스터 수
	vector<Monster> monsters;	//가진 몬스터
public:
	Player(string name, 
		int sex, 
		int money, 
		int maxMonster, 
		int maxBall, 
		int ballKind, 
		vector<BallPocket> ballPocket, 
		int monsterCount, 
		vector<Monster> monsters);
	~Player();

	//getter
	string getName();
	int getSex();
	int getMoney();
	int getMaxMonster();
	int getMaxBall();
	int getBallKind();
	vector<BallPocket>& getBallPocket();
	vector<Monster>& getMonster();

	//setter
	void setName(string name);
	void setSex(int sex);
	void setMoney(int money);
	void setMaxMonster(int maxMonster);
	void setMaxBall(int maxBall);	
};

#pragma once

