#pragma once
#include "Creature.h"
#include <vector>


class Item {
private:
    int x, y;  // 아이템의 위치
    int type;  // 아이템의 종류
    
public:
    Item(int x, int y, int type) : x(x), y(y), type(type) {}
    std::vector<Item*> items;
    int getX() const { return x; }
    int getY() const { return y; }
    int getType() const { return type; }
    void createItem(int x, int y, int type);
};
class Projectile {
private:
    int x, y;  // 투사체의 위치
    int dx, dy;  // 투사체의 이동 방향
    int speed; // 투사체의 이동 속도

public:
    Projectile(int x, int y, int dx, int dy, int speed)
        : x(x), y(y), dx(dx), dy(dy) {}

    void move(int projectileSpeed) {
        float speed = projectileSpeed;
        if (dx != 0 && dy != 0) { // 대각선 이동인 경우
            speed /= sqrt(2.0f);
        }
        x += dx * speed;
        y += dy * speed;
    }

    int getX() const { return x; }
    int getY() const { return y; }
};

//민들레
class Dandelion : public Ally {
public:
    Dandelion(int x, int y, int speed, double health, int attackPower) : Ally(x, y, speed, health, attackPower) {}

    void Draw();

    void GetAttackted(int damage);

    void move(int newX, int newY);
};

//강아지똥
class DogPoop :public Ally
{
private:
    int projectileSpeed; // 투사체 속도
    int projectileDamage; // 투사체 공격력
      // 던진 투사체들


public:
    std::vector<Projectile*> projectiles;
    DogPoop(int x, int y, int speed, double health, int attackPower, int projectileSpeed, int projectileDamage)
        : Ally(x, y, speed, health, attackPower), projectileSpeed(projectileSpeed), projectileDamage(projectileDamage) {}
    void throwProjectile(int dx, int dy);
    void moveProjectiles();
    void setProjectileSpeed(int projectileSpeed);
    void setProjectileDamage(int projectileDamage);
    void updateProjectiles(std::vector<Monster*>& monsters);
    void updateItems(std::vector<Item*>& items);
    void Draw();
    void GetAttackted(int damage);
    void move(int newX, int newY);
    void attackDamage(int attackPower);
};

//병아리
class Chick : public Monster {
private:
    int attack_damage;
    
public:
    DogPoop* target;
    Chick(int x, int y, int speed, double health, int attackPower, int targetX, int targetY)
        : Monster(x, y, speed, health, attackPower, targetX, targetY) {}

    void Draw();
    void GetAttackted(int damage);
    void move(int newX, int newY);
    void attackDamage(int attackPower);
    void setTarget(DogPoop* newTarget);
    void toTarget();

};

//참새
class Sparrow : public Monster {
private:
    int attack_damage;

public:
    Dandelion* target;
    Sparrow(int x, int y, int speed, double health, int attackPower, int targetX, int targetY)
        : Monster(x, y, speed, health, attackPower, targetX, targetY) {}

    void Draw();
    void GetAttackted(int damage);
    void move(int newX, int newY);
    void setTarget(Dandelion* newTarget);
    void attackDamage(int attackPower);
    void toTarget();
    

};

//attackDamage 안 씀