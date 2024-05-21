#pragma once
#include "Creature.h"
#include <list>
#include <iostream>
#include <SDL.h>

using namespace std;

//ui 적용 시 값 얻어와서 할당하기
int screenWidth = 100;
int screenHeight = 100;


//구렁이 연결리스트 노드
typedef struct Node {
	//x좌표 y좌표
	int sX, sY;
}Node;


//구렁이
class Snake : public Monster  //구렁이
{
private:
	//구렁이 좌표를 저장하고 업데이트 할 연결리스트
	list<Node*> snakeList;
public:
	Snake(int x, int y, int speed, double health, int attackPower, int tX, int tY);
	~Snake();
	virtual void Draw();
	virtual void GetAttackted(int damage);
	virtual void move(int newX, int newY);
	virtual void attackDamage(int attackPower);

	//getter setter
	list<Node*> getSnakeList() const {
		return snakeList;
	}

};


//종
class Bell : public bellAndRabbit

{

};

//까치
class Magpie : public Ally
{
private:
	
public:
	Magpie(int x, int y, int speed, double health, int attackPower);
	virtual void Draw();
	virtual void GetAttackted(int damage);
	virtual void move(int newX, int newY);
	virtual void attackDamage(int attackPower);

	//충돌 여부 확인
	bool isCollidingSnake(Snake snake);
	bool isCollidingBell(Bell bell); 
};


