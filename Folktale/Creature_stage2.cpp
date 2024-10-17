#include "Creature_stage2.h"
#include "Phase_stage2Game.h"

//�̷�----------------------------------------------------------------------------------------------------------------


int Maze::maze[SCREEN_HEIGHT_STAGE2][SCREEN_WIDTH_STAGE2] = {

    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 3, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 2, 1},
    {1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 3, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 3, 0, 1},
    {1, 0, 1, 1, 3, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 2, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 2, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 1, 0, 0, 0, 1, 3, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 2, 1, 1, 3, 1},
    {1, 3, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 1, 0, 1, 0, 1, 0, 0, 0, 0, 3, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 3, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 2, 1, 0, 2, 1, 1, 1, 2, 0, 1},
    {1, 0, 2, 0, 0, 1, 0, 1, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 3, 0, 0, 0, 2, 0, 0, 1, 0, 0, 0, 1, 1, 1},
    {1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 2, 1, 1, 0, 1, 2, 1, 1, 1, 0, 1},
    {1, 0, 0, 1, 2, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 1},
    {1, 0, 1, 1, 0, 3, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 1, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 1},
    {1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 3, 1, 0, 0, 3, 0, 1, 0, 1, 0, 0, 1, 0, 1, 2, 1, 0, 1, 2, 1, 1, 0, 2, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 2, 0, 3, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 3, 0, 0, 0, 2, 0, 1},
    {1, 2, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 3, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}


}; // maze �迭 �ܺ� ����

bool Maze::isCoral(int x, int y) {
    return maze[y][x] == 1;
}

//��ȣ----------------------------------------------------------------------------------------------------------------
Coral::Coral(int x, int y, int speed, double health, int attackPower) : Ally(x, y, speed, health, attackPower) {

}

void Coral::Draw() {
}

void Coral::attackDamage(int attackPower) {

}

void Coral::move(int newX, int newY) {
}

void Coral::GetAttackted(int damage) {

}

Coral::~Coral() {
}

//��ȣ2----------------------------------------------------------------------------------------------------------------
Coral2::Coral2(int x, int y, int speed, double health, int attackPower) : Ally(x, y, speed, health, attackPower) {

}


void Coral2::Draw() {
}

void Coral2::attackDamage(int attackPower) {

}

void Coral2::move(int newX, int newY) {
}

void Coral2::GetAttackted(int damage) {

}
Coral2::~Coral2() {
}

//�Ҷ��----------------------------------------------------------------------------------------------------------------

Conch::Conch(int x, int y, int speed, double health, int attackPower, int tX, int tY) : Monster(x, y, speed, health, attackPower, tX, tY) {//init �Լ� -> �ʱⰪ ����


    moveCounter = 0;

}

void Conch::Draw() {

}

void Conch::GetAttackted(int damage) {

}


void Conch::move(int newX, int newY) {
    // ������ ī���͸� ������Ŵ
    moveCounter++;

    // ������ ī���Ͱ� ���� ���� �����ϸ� �������� �����ϰ� ī���͸� ����
    if (moveCounter >= MOVE_DELAY) {
        int x = getX();
        int y = getY();

        // �����ϰ� ���� ����
        direction = rand() % 4;

        // ���õ� ���⿡ ���� �̵�
        switch (direction) {
        case 0: // ��
            y--;
            break;
        case 1: // ��
            y++;
            break;
        case 2: // ��
            x--;
            break;
        case 3: // ��
            x++;
            break;
        }

        // ���� ��踦 ����� �ݴ� �������� �̵�
        if (x < 1) {
            x = 1;
            direction = 3; // ��� ���� ����
        }
        else if (x >= SCREEN_WIDTH_STAGE2-1) {
            x = SCREEN_WIDTH_STAGE2 - 2;
            direction = 2; // �·� ���� ����
        }
        if (y < 1) {
            y = 1;
            direction = 1; // �Ϸ� ���� ����
        }
        else if (y >= SCREEN_HEIGHT_STAGE2-1) {
            y = SCREEN_HEIGHT_STAGE2 - 2;
            direction = 0; // ������ ���� ����
        }

        // ��ġ ������Ʈ
        setXY(x, y);

        // ������ ī���� ����
        moveCounter = 0;
    }
}

void Conch::attackDamage(int attackPower) {


}


Conch::~Conch() {

}


//�ź���----------------------------------------------------------------------------------------------------------------
Turtle::Turtle(int x, int y, int speed, double health, int attackPower) :Ally(x, y, speed, health, attackPower), turtle_invincible(false), invincible_timer(0), invincible_duration(180) {
    //������

}

void Turtle::Draw() {

}

//�ź��̰� ���ݹ޾�����
void Turtle::GetAttackted(int damage) {
    if (!isInvincible()) { // ���� ���°� �ƴ� ���� ���ظ� ����
        cout << "�ź��̰� ���ݹ޾ҽ��ϴ�." << endl;
        int hp = getHealth();
        hp -= damage;
        if (hp <= 0) {
            hp = 0; // �ź��� ����
        }
        setHealth(hp);
        setInvincible(true); // ���� ���·� ����
        setInvincibleTimer(invincible_duration); // Ÿ�̸� ����
    }
}

// �ź��� �̵� �޼���
void Turtle::move(int newX, int newY) {
    // ���ο� ��ġ�� �̷� ��� ���� �ִ��� Ȯ��
    if (newX >= 0 && newX < SCREEN_WIDTH_STAGE2 && newY >= 0 && newY < SCREEN_HEIGHT_STAGE2) {
        // ���ο� ��ġ�� ��ȣ���� Ȯ��
        if (Maze::isCoral(newX, newY)) {
            // ��ȣ�� �ε������Ƿ� ���ظ� �ް� �̵����� ����
            this->GetAttackted(1);
        }
        else {
            // ��ȣ�� �ƴ϶�� �ź��̸� ���ο� ��ġ�� �̵�
            this->setXY(newX, newY);
        }
    }

}




void Turtle::attackDamage(int attackPower) {
}

bool Turtle::isCollision_Coral(Coral* coral) {
    bool isCollision = false;//�浹����
    //�ź��̿� ��ȣ�� ��ǥ�� ������ �浹
    if (this->getX() == coral->getX() && this->getY() == coral->getY()) {
        isCollision = true;

    }
    return isCollision;

}
bool Turtle::isCollision_Coral2(Coral2* coral2) {
    bool isCollision = false;//�浹����
    //�ź��̿� ��ȣ�� ��ǥ�� ������ �浹
    if (this->getX() == coral2->getX() && this->getY() == coral2->getY()) {
        isCollision = true;

    }
    return isCollision;

}
bool Turtle::isCollision_Rabbit(Rabbit* rabbit) {
    bool isCollision = false;//�浹����
    //�ź��̿� �䳢�� ��ǥ�� ������ �浹
    if (this->getX() == rabbit->getX() && this->getY() == rabbit->getY()) {
        isCollision = true;
        // setIsFace �޼��� ȣ��
        rabbit->setIsFace(!rabbit->getIsFace());
    }
    return isCollision;
}

bool Turtle::isCollision_Conch(Conch* Conch) {
    bool isCollision = false;//�浹����
    //�ź��̿� �Ҷ���� ��ǥ�� ������ �浹
    if (this->getX() == Conch->getX() && this->getY() == Conch->getY()) {
        isCollision = true;
    }
    return isCollision;
}

bool Turtle::isCollision_Conch2(Conch* Conch) {
    bool isCollision = false;

    // �Ҷ���� �� ���� ��ǥ�� Ȯ��
    int conchX = Conch->getX();
    int conchY = Conch->getY();

    // �ź����� ��ǥ
    int turtleX = this->getX();
    int turtleY = this->getY();

    // �Ҷ���� �� ���� ��ǥ �� �ϳ��� �ź����� ��ǥ�� ������ �浹
    if ((turtleX == conchX && turtleY == conchY) ||
        (turtleX == conchX + 1 && turtleY == conchY) ||
        (turtleX == conchX && turtleY == conchY + 1) ||
        (turtleX == conchX + 1 && turtleY == conchY + 1)) {
        isCollision = true;
    }

    return isCollision;
}

//�Ҹ�������
Turtle::~Turtle() {}

//�䳢----------------------------------------------------------------------------------------------------------------
Rabbit::Rabbit(int x, int y, int speed, double health) : bellAndRabbit(x, y, speed, health) {

}

void Rabbit::Draw() {
}

void Rabbit::GetAttackted(int damage) {
}

void Rabbit::move(int newX, int newY) {
}
void Rabbit::spawn() {
    // ������ �� �ִ� ��ġ ��� ����
    int rabbitSpawnTimer;
    vector<pair<int, int>> validPositions;

    for (int y = 0; y < SCREEN_HEIGHT_STAGE2; ++y) {
        for (int x = 0; x < SCREEN_WIDTH_STAGE2; ++x) {
            if (Maze::maze[y][x] == 0) { // ��ȣ�� �ƴ� ��ġ Ȯ��
                validPositions.push_back(make_pair(x, y));
            }
        }
    }

    if (!validPositions.empty()) {
        // �������� ��ȿ�� ��ġ ����
        uniform_int_distribution<int> distribution(0, validPositions.size() - 1);
        int index = distribution(generator);
        this->setXY(validPositions[index].first, validPositions[index].second);
    }


}


Rabbit::~Rabbit() {}
