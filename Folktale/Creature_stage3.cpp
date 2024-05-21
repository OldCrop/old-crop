#include "Creature_stage3.h"
#define SNAKESIZE 10

//구렁이 메서드 구현 -------------------------------------------------------------------------------
Snake::Snake(int x, int y, int speed, double health, int attackPower, int tX, int tY) : Monster(x, y, speed, health, attackPower, tX, tY){//init 함수 -> 초기값 설정
	//구렁이 좌표 초기값 설정 
	//구렁이의 길이는 일단 10개로 지정
	int centerX = screenWidth / 2;
	int centerY = screenHeight / 2;
	for (int i = 0;i < SNAKESIZE;i++) {
		Node* n = new Node;
		n->sX=i+ centerX;
		n->sY = centerY;
		snakeList.push_back(n);
	}

}

void Snake::Draw() { //얘는 뭐하는 함수지

}

void Snake::GetAttackted(int damage) { //생각해보니 구렁이는 데미지를 안 받음
	//double hp = getHealth(); //현재 Snake의 hp 가져오기
	//hp -= damage; 
	//if (hp < 0) //만약 죽었으면 0으로 설정
	//	hp = 0;
	//setHealth(hp); //hp에서 damage 받은 값으로 재설정
}

void Snake::move(int newX, int newY) { //newX와 newY는 범위확인이 끝난 값 
	//front에 새 노드 추가
	Node* n = new Node;
	n->sX = newX;
	n->sY = newY;
	snakeList.push_front(n);
	//back에서 노드 제거
	Node* lastNode = snakeList.back();
	delete lastNode;
	snakeList.pop_back();
}

void Snake::attackDamage(int attackPower) { 
	//구렁이가 까치한테 데미지 주는 메서드 -> 까치의 attacked메서드로 쓰자
	//이 메서드는 isColliding이 true일 때 호출

}


Snake::~Snake() {
	//snake 메모리 해제
	while (!snakeList.empty()) {
		delete snakeList.back();
		snakeList.pop_back();
	}
}

//까치 메서드 구현 -----------------------------------------------------------------------------

Magpie::Magpie(int x, int y, int speed, double health, int attackPower) :Ally(x, y, speed, health, attackPower) {

}

bool Magpie::isCollidingSnake(Snake snake) { //구렁이와의 충돌 여부 확인
	bool is = false; //충돌 안 함으로 초기화

	// snake의 모든 노드를 돌며 확인해야 함
	for (const auto& node : snake.getSnakeList()) {
		// 만약 부딪혔으면 true 반환
		if ((node->sX == this->getX()) && (node->sY == this->getY())) {
			is = true;
			break;
		}
	}

	return is;
}

void Magpie::Draw() { //얘는 뭐하는 함수지

}

void Magpie::GetAttackted(int damage) { 
	//까치 데미지 받기 -> damage=구렁이 attackPower가져오기
	double hp = getHealth(); //현재 까치의 hp 가져오기
	hp -= damage; 
	if (hp < 0) //만약 죽었으면 0으로 설정
		hp = 0;
	setHealth(hp); //hp에서 damage 받은 값으로 재설정
}

void Magpie::move(int newX, int newY) {
	//newX와 newY 범위 확인
	if (newX > screenWidth)
		newX = screenWidth;
	else if (newX < 0)
		newX = 0;
	if (newY > screenHeight)
		newY = screenHeight;
	else if (newY < 0)
		newY = 0;

	this->setXY(newX, newY);
}

void Magpie::attackDamage(int attackPower) {
	
}