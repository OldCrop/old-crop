// Creature_stage1.cpp
#include "Creature_stage1.h"
#include "Phase_stage1.h"

void Item::createItem(int x, int y, int type) {
    Item* item = new Item(x, y, type);
    items.push_back(item);
}
// #########Dandelion 클래스의 메서드 구현#########

void Dandelion::Draw() {
    // 민들레를 그리는 코드

}

void Dandelion::GetAttackted(int damage) {
    // 공격 받았을 때의 동작
        //체력 감소
    setHealth(getHealth() - damage);
    //체력이 0이하로 떨어지면
    if (getHealth() <= 0) {
        //엔딩~
    }

}

void Dandelion::move(int newX, int newY) {
    // 이동하는 코드
    //그러나 민들레는 움직이지 않으므로 SKIP
}


// #########DogPoop 클래스의 메서드 구현#########
void DogPoop::Draw() {
    // 강아지똥을 그리는 코드 
}

void DogPoop::GetAttackted(int damage) {
    // 공격 받았을 때의 동작
    //체력 감소
    setHealth(getHealth() - damage);
    //체력이 0이하로 떨어지면
    if (getHealth() <= 0) {
        //엔딩
    }
}
void DogPoop::updateItems(std::vector<Item*>& items) {
    for (int i = 0; i < items.size(); ++i) {
        Item* item = items[i];

        if (item->getX() == getX() && item->getY() == getY()) {
            if (item->getType() == 1) {
                //1번이면 물약 아이템
                setHealth(getHealth() + 10);
            }
            else if (item->getType() == 2) {
                //2번이면 쿨타임 감소
                FIRE_COOLDOWN -= 100;
            }
            else if (item->getType() == 3) {
                //3번이면 이동속도 증가 아이템
                setSpeed(getSpeed() + 1);
            }
            else if (item->getType() == 4) {
                //4번이면 돌 무기 
                is_rock = true;
            }
            delete item;
            items.erase(items.begin() + i);
            --i;
        }
    }
}
void DogPoop::throwProjectile(int dx, int dy){
    Projectile* projectile = new Projectile(getX(), getY(), dx, dy, projectileSpeed);
    projectiles.push_back(projectile);
}

void DogPoop::setProjectileSpeed(int projectileSpeed)
{
    this->projectileSpeed = projectileSpeed;
}

void DogPoop::setProjectileDamage(int projectileDamage)
{
    this->projectileDamage = projectileDamage;
}

void DogPoop::updateProjectiles(std::vector<Monster*>& monsters)
{
    for (int i = 0; i < projectiles.size(); ++i) {
        Projectile* projectile = projectiles[i];

        // 투사체를 이동시킨다.
        projectile->move(projectileSpeed);

        // 투사체가 화면 밖으로 나갔는지 확인한다.
        if (projectile->getX() < 0 || projectile->getX() > SCREEN_WIDTH ||
            projectile->getY() < 0 || projectile->getY() > SCREEN_HEIGHT) {
            // 투사체를 제거한다.
            delete projectile;
            projectiles.erase(projectiles.begin() + i);
            --i;
            continue;
        }

        // 각각의 적과 투사체가 충돌했는지 확인한다.
        for (Monster* monster : monsters) {
            if (monster == nullptr) continue;
            int dx = projectile->getX() - monster->getX();
            int dy = projectile->getY() - monster->getY();
            if (dx * dx + dy * dy < COLLISION_DISTANCE * COLLISION_DISTANCE) {
                // 적의 체력을 감소시킨다.
                monster->GetAttackted(projectileDamage);

                // 체력이 0 이하인 경우 적을 제거한다.
                if (monster->getHealth() <= 0) {
                    delete monster;
                    monsters.erase(monsters.begin() + i);
                    projectiles.erase(projectiles.begin() + i);
                    --i;
                    continue;
                }
                // 투사체를 제거한다.
                delete projectile;
                projectiles.erase(projectiles.begin() + i);
                --i;

                break;
            }
        }
    }
}

void DogPoop::moveProjectiles() {
    for (Projectile* projectile : projectiles) {
        projectile->move(projectileSpeed);
    }
}

void DogPoop::move(int newX, int newY) {
    // 이동하는 코드
    float speed = getSpeed();
    if (newX != 0 && newY != 0) {
        speed /= sqrt(2.0f);
    }
    setX(getX() + newX * speed);
    setY(getY() + newY * speed);
}

// #########Chick 클래스의 메서드 구현#########
void Chick::Draw() {
    // 병아리를 그리는 코드 SKIP
}

void Chick::GetAttackted(int damage) {
    // 공격 받았을 때의 동작
    setHealth(getHealth() - damage);

}


void Chick::move(int newX, int newY) {
    // 이동하는 코드 (주인공을 향해 다가오는 로직)
    
    if (getX() < getTargetX()) {
        setX(getX() + getSpeed());
    }
    else if (getX() > getTargetX()) {
        setX(getX() - getSpeed());
    }

    if (getY() < getTargetY()) {
        setY(getY() + getSpeed());
    }
    else if (getY() > getTargetY()) {
        setY(getY() - getSpeed());
    }

}


void Chick::attackDamage(int attackPower) {
    // 공격하는 코드 (주인공을 공격하는 로직)
    if (target != nullptr) {
        target->GetAttackted(attackPower);
    }

}
void Chick::setTarget(DogPoop* newTarget) {
    target = newTarget;
}

// #########Sparrow 클래스의 메서드 구현#########
void Sparrow::Draw() {
    // 참새를 그리는 코드
}

void Sparrow::GetAttackted(int damage) {
    // 공격 받았을 때의 동작
        //체력 감소
    setHealth(getHealth() - damage);
}

void Sparrow::move(int newX, int newY) {
    // 이동하는 코드 (주인공을 향해 다가오는 로직)

    if (getX() < getTargetX()) {
        setX(getX() + getSpeed());
    }
    else if (getX() > getTargetX()) {
        setX(getX() - getSpeed());
    }

    if (getY() < getTargetY()) {
        setY(getY() + getSpeed());
    }
    else if (getY() > getTargetY()) {
        setY(getY() - getSpeed());
    }
}
void Sparrow::setTarget(Dandelion* newTarget) {
    target = newTarget;
}

void Sparrow::attackDamage(int attackPower) {
    // 공격하는 코드 (주인공을 공격하는 로직)
}

