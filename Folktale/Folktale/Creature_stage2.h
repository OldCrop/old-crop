#pragma once
#include "Creature.h"
#include <iostream>
#include <SDL.h>
#include <random>
#define GRID 30

using namespace std;
enum DIRECTION { LEFT, RIGHT, UP, DOWN };
//화면 사이즈
const int SCREEN_WIDTH = 20;
const int SCREEN_HEIGHT = 20;

//거북이 *
//토끼 ^
//산호 @


//미로
class Maze {
public:
	static int maze[SCREEN_HEIGHT][SCREEN_WIDTH];

	static bool isCoral(int x, int y);
};

//산호

class Coral : public Ally {
private:
	char C_output;

public:
	Coral(int x, int y, int speed, double health, int attackPower);
	~Coral(); 

	virtual void Draw();
	virtual void attackDamage(int attackPower);
	virtual void GetAttackted(int damage);
	virtual void move(int newX, int newY);
	char get_output();
};


//토끼
class Rabbit : public bellAndRabbit {
private:
	char R_output;
public:
	Rabbit(int x, int y, int speed, double health);
	~Rabbit();
	virtual void Draw();
	virtual void GetAttackted(int damage);
	virtual void move(int newX, int newY);
	void spawn(); 
	char get_output();
};




//거북이
class Turtle :public Ally
{
private:
	char T_output;

public:
	Turtle(int x, int y, int speed, double health, int attackPower);
	~Turtle();

	virtual void Draw();
	virtual void GetAttackted(int damage);
	virtual void move(int newX, int newY);
	virtual void attackDamage(int attackPower);
	bool isCollision_Coral(Coral* coral);
	bool isCollision_Rabbit(Rabbit* rabbit);

	char get_output();
};