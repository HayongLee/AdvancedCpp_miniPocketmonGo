#include "FileManager.h"
#include "Player.h"
#include "MonsterData.h"
#include "BallPocket.h"
#include "Monster.h"
#include "Ball.h"

FileManager::FileManager()
{
	mosterballFile = "MonsterBall.txt";
	poketmonFile = "Poketmon.txt";
	playerFile = "Player.txt";
}

FileManager::~FileManager()
{
}

vector<Ball> FileManager::readMonsterBallFromFile(bool& loadSuccess){
	vector<Ball> balls;
	int n, id, price, probability;
	string name;
	ifstream fin(mosterballFile);
	if (fin.is_open()){
		cout << "포켓몬 볼 정보를 가져옵니다."<<endl;
		fin >> n;
		for (int i = 0; i < n; i++)
		{
			fin >> id;
			fin.ignore(); // 새 줄 무시 
			getline(fin, name);
			fin >> price;
			fin >> probability;
			Ball newBall(id, name, price, probability);
			balls.push_back(newBall);
		}
		loadSuccess = true;
	}
	else{
		cout << "포켓몬 볼 정보를 가져오는데 실패하였습니다." << endl;
		loadSuccess = false;
	}
	return balls;
}
vector<MonsterData> FileManager::readMonsterFromFile(bool& loadSuccess){
	vector<MonsterData> monsterDatas;
	int n, id, type, probability;
	string name;
	ifstream fin(poketmonFile);
	if (fin.is_open()){
		cout << "포켓몬 정보를 가져옵니다."<<endl;
		fin >> n;
		for (int i = 0; i < n; i++)
		{
			fin >> id;
			fin.ignore(); // 새 줄 무시 
			getline(fin, name);
			fin >> type;
			fin >> probability;
			MonsterData newMonster(id, name, type, probability);
			monsterDatas.push_back(newMonster);
		}
		loadSuccess = true;
	}
	else{
		cout << "포켓몬 정보를 가져오는데 실패하였습니다." << endl;
		loadSuccess = false;
	}
	return monsterDatas;
}
Player* FileManager::readPlayerFromFile(vector<MonsterData> monsterDatas, vector<Ball> balls){
	string name;
	int sex, money, maxMonster, maxBall, ballKind;
	vector<BallPocket> ballPocket;
	int monsterCount;
	vector<Monster> monsters;
	ifstream fin(playerFile);
	if (fin.is_open()){
		getline(fin, name);
		fin >> sex;
		fin >> money;
		fin >> maxMonster;
		fin >> maxBall;
		fin >> ballKind;
		for (int i = 0; i < ballKind; i++){
			int ballId; fin >> ballId;
			int ballNum; fin >> ballNum;
			Ball ball;
			for (int j = 0; j < balls.size(); j++){
				if (balls.at(j).getId() == ballId){
					ball = balls.at(j);
					break;
				}
			}
			BallPocket newballPocket(ball, ballId, ballNum);
			ballPocket.push_back(newballPocket);
		}

		fin >> monsterCount;
		for (int i = 0; i < monsterCount; i++)
		{
			int monsterId;
			fin >> monsterId;

			///monsterDatas 백터에서 주어진 id에 해당하는 값을 구한다.
			int monstersVectorIndex = -1;
			for (int j = 0; j < monsterDatas.size(); j++){
				if (monsterDatas.at(j).getId() == monsterId){
					monstersVectorIndex = j;
					break;
				}
			}
			fin.ignore();
			string nickname; getline(fin, nickname);
			int hp; fin >> hp;
			int attk; fin >> attk;
			int def; fin >> def;

			Monster addedMonster = monsterDatas.at(monstersVectorIndex).genMonster(nickname, hp, attk, def);
			monsters.push_back(addedMonster);
		}
	}
	else{
		cout << "플레이어의 이름을 입력하세요 : ";
		getline(cin, name);
		while (1){
			cout << "성별을 입력하세요 (1:남/2:녀) : ";
			cin >> sex;
			if ((sex == 1 || sex == 2))break;
			else cout << "입력 범위를 벗어났습니다." << endl;
		}
		money = 0;
		maxBall = 10;
		maxMonster = 10;
		ballKind = balls.size();
		monsterCount = 0;
		for (int i = 0; i < balls.size(); i++){
			BallPocket newballPocket(balls.at(i), balls.at(i).getId(), 0);
			ballPocket.push_back(newballPocket);
		}

	}
	Player* player = new Player(name, sex, money, maxMonster, maxBall, ballKind, ballPocket, monsterCount, monsters);
	return player;
}
void FileManager::writePlayerToFile(Player* player){
	ofstream fout(playerFile);
	fout << player->getName() << endl;
	fout << player->getSex() << endl;
	fout << player->getMoney() << endl;
	fout << player->getMaxMonster() << endl;
	fout << player->getMaxBall() << endl;
	fout << player->getBallPocket().size() << endl;
	for (int i = 0; i < player->getBallPocket().size(); i++){
		fout << player->getBallPocket().at(i).getId()
			<< ' '
			<< player->getBallPocket().at(i).getNum()
			<< endl;
	}
	fout << player->getMonster().size() << endl;
	for (int i = 0; i < player->getMonster().size(); i++){
		fout << player->getMonster().at(i).getId() << endl;
		fout << player->getMonster().at(i).getNickname() << endl;
		fout << player->getMonster().at(i).getHp() << endl;
		fout << player->getMonster().at(i).getAttk() << endl;
		fout << player->getMonster().at(i).getDef() << endl;
	}

	if (fout.is_open() == true){
		fout.close();
	}
}
