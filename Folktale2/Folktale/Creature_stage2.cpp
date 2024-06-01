#include "Creature_stage2.h"
#include "Phase_stage2.h"

default_random_engine generator;

//미로----------------------------------------------------------------------------------------------------------------


int Maze::maze[SCREEN_HEIGHT][SCREEN_WIDTH] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} ,
	{1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1},
	{1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1},
	{1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
}; // maze 배열 외부 선언

bool Maze::isCoral(int x, int y) {
	return maze[y][x] == 1;
}

//산호----------------------------------------------------------------------------------------------------------------
Coral::Coral(int x, int y, int speed, double health, int attackPower): Ally( x, y,  speed,  health,attackPower){
	//생성자
	C_output = '#';
}

void Coral::Draw() {
}

void Coral::attackDamage(int attackPower) {
	 
}

void Coral::move(int newX, int newY) {
}

void Coral::GetAttackted(int damage) {

}

Coral::~Coral() {}




//거북이----------------------------------------------------------------------------------------------------------------
Turtle::Turtle(int x, int y, int speed, double health, int attackPower):Ally(x,  y,  speed,  health,  attackPower) {
	//생성자

	T_output = '*';
}

void Turtle::Draw() {
	
}

//거북이가 공격받았을때
void Turtle:: GetAttackted(int damage) {
	//거북이 체력 감소
	//거북이 체력이 0이하면 죽음
	int hp = getHealth();
	hp-=damage;
	if (hp <= 0) {
		//거북이 죽음
		hp= 0;
	}
	setHealth(hp);
}

void Turtle::move(int newX, int newY) {
	//거북이 이동
	this->setXY(newX, newY);


}

void Turtle::attackDamage(int attackPower) {
}

bool Turtle::isCollision_Coral(Coral* coral) {
	bool isCollision = false;//충돌여부
	//거북이와 산호의 좌표가 같으면 충돌
	if (this->getX() == coral->getX() && this->getY() == coral->getY()) {
		isCollision = true;

	}
	return isCollision;
	
}

bool Turtle::isCollision_Rabbit(Rabbit* rabbit) {
	bool isCollision = false;//충돌여부
	//거북이와 토끼의 좌표가 같으면 충돌
	if (this->getX() == rabbit->getX() && this->getY() == rabbit->getY()) {
		isCollision = true;
		// setIsFace 메서드 호출
		rabbit->setIsFace(!rabbit->getIsFace());
	}
	return isCollision;
}

char Turtle::get_output() {
	return this->T_output;
}
//소멸자정의
Turtle::~Turtle() {}

//토끼----------------------------------------------------------------------------------------------------------------
Rabbit::Rabbit(int x, int y, int speed, double health) : bellAndRabbit(x, y, speed, health) {
	R_output = '^';
}

void Rabbit::Draw() {
}

void Rabbit::GetAttackted(int damage) {
}

void Rabbit::move(int newX, int newY) {
}
void Rabbit::spawn() {
	uniform_int_distribution<int> distributionX(0, SCREEN_WIDTH - 1);
	uniform_int_distribution<int> distributionY(0, SCREEN_HEIGHT - 1);

	if (this->getIsFace()) { // 만약 거북이를 만났다면
		this->setIsFace(!this->getIsFace()); // 만났던 거 안 만났다고 갱신

		// 산호와 겹치지 않는 좌표를 찾기
		int newX, newY;
		do {
			newX = distributionX(generator);
			newY = distributionY(generator);
		} while (Maze::isCoral(newX, newY));

		// 좌표 갱신
		this->setXY(newX, newY);
	}
}
char Rabbit::get_output() {
	return this->R_output;
}

Rabbit::~Rabbit() {}
