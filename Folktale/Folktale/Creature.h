#pragma once

class Creature // 최상위
{
private:
	int pos_x, pos_y;
	int speed;
	double health;
public:
	virtual void Draw() = 0;
	virtual void GetAttackted(int damage) = 0;
	virtual void move(int newX, int newY) = 0;
};

//거북이 강아지똥 민들레 까치
class Ally : public Creature
{
private:
	int attackPower;
public:

};

//병아리 참새 구렁이
class Monster : public Creature
{
private:
	int attackPower;
	int target_x, target_y;

public:
	void attackDamage(int attackPower);
	virtual void update_targetXY() = 0;
};

//종, 토끼
class bellAndRabbit : public Creature
{
private:
	bool isFace = false;
	int count = 0;
public:
	virtual void spawn() = 0;
	//얘네는 무브 스루하기
};
