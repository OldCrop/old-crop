#pragma once
#include "Creature.h"

//¹Îµé·¹
class Dandelion :public Ally
{
private:

public:
};

//°­¾ÆÁö¶Ë
class DogPoop :public Ally
{
private:

public:
	DogPoop(int _health, int _x, int _y);

};

//º´¾Æ¸®
class Chick : public Monster
{
	// hp, attck_damage, (x,y), speed, (fx,fy),spon()  -  Å¸°ÙÁÂÇ¥(0)
private:
	int attack_damage;

public:

};

//Âü»õ
class Sparrow : public Monster
{
private:
	int attack_damage;

public:

};