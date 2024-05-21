#pragma once
#include "Creature.h"

//거북이
class Turtle :public Ally
{
private:

public:
	Turtle(int _health, int _x, int _y);
};

//토끼
class Rabbit : public bellAndRabbit
{
};


//종
class Bell : public bellAndRabbit

{

};