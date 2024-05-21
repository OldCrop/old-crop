#include "Phase_stage1.h"
#include "Creature.h"
#include <windows.h>
#include <vector>

Stage1::Stage1() {

}

int g_input;

int g_X;
int g_Y;

bool g_key_up = false;
bool g_key_down = false;
bool g_key_left = false;
bool g_key_right = false;
bool g_key_space = false;
bool is_rock = false;
Direction g_direction = DOWN;
Uint32 FIRE_COOLDOWN = 1000;  // 투사체 발사 쿨타임

const int monsterCount = 50;

// 흘러간 시간 기록
double g_elapsed_time_ms;

void Stage1::HandleEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {

        case SDL_QUIT:
            g_flag_running = false;
            break;

        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_LEFT) {
                g_key_left = true;
            }
            if (event.key.keysym.sym == SDLK_RIGHT) {
                g_key_right = true;
            }
            if (event.key.keysym.sym == SDLK_UP) {
                g_key_up = true;
            }
            if (event.key.keysym.sym == SDLK_DOWN) {
                g_key_down = true;
            }
            if (event.key.keysym.sym == SDLK_SPACE) {
                g_key_space = true;
            }
            break;

        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_LEFT) {
                g_key_left = false;
            }
             if (event.key.keysym.sym == SDLK_RIGHT) {
                g_key_right = false;
            }
             if (event.key.keysym.sym == SDLK_UP) {
                g_key_up = false;
            }
             if (event.key.keysym.sym == SDLK_DOWN) {
                g_key_down = false;
            }
             if (event.key.keysym.sym == SDLK_SPACE) {
                    g_key_space = false;
                }
            break;

        default:
            break;
        }
    }
}

/*
    SDL_Event event;

    if (SDL_PollEvent(&event)) {

        switch (event.type) {

        case SDL_QUIT:
            g_flag_running = false;
            break;

        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_LEFT) {
                dogPoop->move(-1, 0);  // 왼쪽으로 이동
            }
            else if (event.key.keysym.sym == SDLK_RIGHT) {
                dogPoop->move(1, 0);
            }
            else if (event.key.keysym.sym == SDLK_UP) {
                dogPoop->move(0, -1);  // 위로 이동
            }
            else if (event.key.keysym.sym == SDLK_DOWN) {
                dogPoop->move(0, 1);  // 아래로 이동
            }
            else if (event.key.keysym.sym == SDLK_SPACE) {
                
            }
            break;

        case SDL_KEYUP:
            break;

        default:
            break;
        }
    }
    */
void Stage1::Update() {
    // 1.1. 키보드 입력에 따라 주인공의 위치를 변경한다.
    //일단 대각선 이동이 준내 빠를것.. 그래서 newX, newY의 파라미터값을 float로 바꾸어야 하는데
    //일단은 int로 해놓음
    /* 이건 루트 씌워서 동일하게 유지하는 코드
        if (g_key_left && g_key_up) {
        dogPoop->move(-1 / sqrt(2), -1 / sqrt(2));  // 왼쪽 위로 이동
        g_direction = LEFT;
    }
    else if (g_key_right && g_key_up) {
        dogPoop->move(1 / sqrt(2), -1 / sqrt(2));  // 오른쪽 위로 이동
        g_direction = RIGHT;
    }
    else if (g_key_left && g_key_down) {
        dogPoop->move(-1 / sqrt(2), 1 / sqrt(2));  // 왼쪽 아래로 이동
        g_direction = LEFT;
    }
    else if (g_key_right && g_key_down) {
        dogPoop->move(1 / sqrt(2), 1 / sqrt(2));  // 오른쪽 아래로 이동
        g_direction = RIGHT;
    }
    */
    if (g_key_left && g_key_up) {
        dogPoop->move(-1, -1);  // 왼쪽 위로 이동
        g_direction = LEFT_UP;
    }
    else if (g_key_right && g_key_up) {
        dogPoop->move(1, -1);  // 오른쪽 위로 이동
        
        g_direction = RIGHT_UP;

    }
    else if (g_key_left && g_key_down) {
        dogPoop->move(-1, 1);  // 왼쪽 아래로 이동
        g_direction = LEFT_DOWN;
    }
    else if (g_key_right && g_key_down) {
        dogPoop->move(1, 1);  // 오른쪽 아래로 이동
        g_direction = RIGHT_DOWN;
    }
    // 좌측 이동
    else if (g_key_left) {
        dogPoop->move(-1, 0);  // 왼쪽으로 이동

        g_direction = LEFT;
    }
    // 우측 이동
    else if (g_key_right) {
        dogPoop->move(1, 0);

        g_direction = RIGHT;
    }
    // 위로 이동
    else if (g_key_up) {
        dogPoop->move(0, -1);  // 위로 이동

        g_direction = UP;
    }
    // 아래로 이동
    else if (g_key_down) {
        dogPoop->move(0, 1);  // 아래로 이동

        g_direction = DOWN;
    }
    // 화면 밖으로 나가는 것을 확인합니다.
    if (dogPoop->getX() < 0) {
        dogPoop->setX(0);
    }
    else if (dogPoop->getX() > SCREEN_WIDTH - dp_dest_rect.w) {
        dogPoop->setX(SCREEN_WIDTH - dp_dest_rect.w);
    }
    if (dogPoop->getY() < 0) {
        dogPoop->setY(0);
    }
    else if (dogPoop->getY() > SCREEN_HEIGHT - dp_dest_rect.h) {
        dogPoop->setY(SCREEN_HEIGHT - dp_dest_rect.h);
    }
     Uint32 currentTime = SDL_GetTicks();

     // 스페이스바를 누르면, 투사체를 발사한다.
     if (g_key_space && currentTime >= lastFireTime + FIRE_COOLDOWN) {
         int dx = 0, dy = 0;
         switch (g_direction) {
         case LEFT: dx = -1; break;
         case RIGHT: dx = 1; break;
         case UP: dy = -1; break;
         case DOWN: dy = 1; break;
         case LEFT_UP: dx = -1; dy = -1; break;
         case RIGHT_UP: dx = 1; dy = -1; break;
         case LEFT_DOWN: dx = -1; dy = 1; break;
         case RIGHT_DOWN: dx = 1; dy = 1; break;
         }
         dogPoop->throwProjectile(dx, dy);
         lastFireTime = currentTime;
     }

     // 1.2. 투사체 이동
     dogPoop->moveProjectiles();


    //3초마다 적 생성
    if (g_elapsed_time_ms >= 3000 && monsters.size() < 50) {
        // 적 객체의 출현 위치를 화면의 외부로 설정합니다.
        int x, y;
        int spawnSide = rand() % 4; // 0: 왼쪽, 1: 오른쪽, 2: 위쪽, 3: 아래쪽
        switch (spawnSide) {
        case 0: // 왼쪽에서 출현
            x = -50; 
            y = (rand() % SCREEN_HEIGHT + 50) - 100;
            break;
        case 1: // 오른쪽에서 출현
            x = 50; 
            y = (rand() % SCREEN_HEIGHT + 50) - 100; 
            break;
        case 2: // 위쪽에서 출현
            x = (rand() % SCREEN_WIDTH + 50) - 100; 
            y = -50; 
            break;
        case 3: // 아래쪽에서 출현
            x = (rand() % SCREEN_WIDTH + 50 ) - 100;
            y = SCREEN_HEIGHT + 50; 
            break;
        }
        // Chick or Sparrow
        if (rand() % 2 == 0) {
            monsters.push_back(new Chick(x, y, 1, 30, 15, dogPoop->getX(), dogPoop->getY()));
            monsters.back()->setTarget(dogPoop);
        }
        else {
            monsters.push_back(new Sparrow(x, y, 1, 30, 20, dogPoop->getX(), dogPoop->getY()));
            monsters.back()->setTarget(dandelion);
            }

        // 경과 시간 초기화
        g_elapsed_time_ms = 0;
    }
    //몬스터들 이동 로직
    for (auto& monster : monsters) {
        monster->toTarget();
        }

    // 1.3. 투사체와 적의 충돌 판정
    dogPoop->updateProjectiles(monsters);

    // 1.4. 적과 민들레, 주인공의 충돌 판정
    for (auto& monster : monsters) {
        Uint32 currentTime = SDL_GetTicks();
        // 적과 민들레의 충돌 판정
        int dx1 = dandelion->getX() - monster->getX();
        int dy1 = dandelion->getY() - monster->getY();
        if (dx1 * dx1 + dy1 * dy1 < COLLISION_DISTANCE * COLLISION_DISTANCE) {

            if (currentTime >= dandelionInvincibleStartTime + 2000) {
                dandelion->GetAttackted(20);
                dandelionInvincibleStartTime = currentTime;
            }
        }
        // 적과 주인공의 충돌 판정
        int dx2 = dogPoop->getX() - monster->getX();
        int dy2 = dogPoop->getY() - monster->getY();
        //맞은 뒤 2초간 무적
        if (dx2 * dx2 + dy2 * dy2 < COLLISION_DISTANCE * COLLISION_DISTANCE) {
            if (currentTime >= dogPoopInvincibleStartTime + 2000) {
                dogPoop->GetAttackted(10);
                dogPoopInvincibleStartTime = currentTime;
            }
        }
    }

    //아이템 랜덤 생성
    now = SDL_GetTicks();
    if ((now - gameStartTime) / 1000 % 8 == 0) {
        int x = rand() % SCREEN_WIDTH;
        int y = rand() % SCREEN_HEIGHT;
        int type = rand() % 4;
        // 랜덤한 위치에 아이템을 생성한다.
        Item CreateItem(x, y, type);
    }
    
    g_elapsed_time_ms += 33;
}
void Stage1::Render() {

    //배경 출력하기
    SDL_RenderCopy(g_renderer, bg_texture, &bg_source_rect, &bg_source_rect);

    //민들레 출력하기
    d_dest_rect.x = dandelion->getX();
    d_dest_rect.y = dandelion->getY();
    SDL_RenderCopyEx(g_renderer, d_texture, &d_source_rect, &d_dest_rect, 0, NULL, SDL_FLIP_NONE);

    //강아지똥 출력하기
    dp_dest_rect.x = dogPoop->getX();
    dp_dest_rect.y = dogPoop->getY();
    SDL_RenderCopyEx(g_renderer, dp_texture, &dp_source_rect, &dp_dest_rect, 0, NULL, SDL_FLIP_NONE);

    
    for (auto& monster : monsters) {
        // Chick 객체일 경우
        if (dynamic_cast<Chick*>(monster)) {
            c_dest_rect.x = monster->getX();
            c_dest_rect.y = monster->getY();
            SDL_RenderCopyEx(g_renderer, c_texture, &c_source_rect, &c_dest_rect, 0, NULL, SDL_FLIP_NONE);
        }
        // Sparrow 객체일 경우
        else if (dynamic_cast<Sparrow*>(monster)) {
            s_dest_rect.x = monster->getX();
            s_dest_rect.y = monster->getY();
            SDL_RenderCopyEx(g_renderer, s_texture, &s_source_rect, &s_dest_rect, 0, NULL, SDL_FLIP_NONE);
            
        }

    }

    // 투사체 출력하기
    for (Projectile* projectile : dogPoop->projectiles) {
        if (!is_rock) {
            p_dest_rect.x = projectile->getX();
            p_dest_rect.y = projectile->getY();
            SDL_RenderCopyEx(g_renderer, p_texture, &p_source_rect, &p_dest_rect, 0, NULL, SDL_FLIP_NONE);
        }
    }
    SDL_RenderPresent(g_renderer);
}

void Stage1::Reset() {

    g_elapsed_time_ms = 0;
    gameStartTime = SDL_GetTicks();
    srand(time(NULL));

    dogPoop = new DogPoop(0, 10, 5, 100.0, 10, 1, 10);
    dogPoop->setXY(SCREEN_WIDTH/2 + 20, SCREEN_HEIGHT/2);
    dogPoop->setSpeed(5);
    dogPoop->setHealth(100.0);
    dogPoop->setProjectileSpeed(7);
    dogPoop->setProjectileDamage(10);

    dandelion = new Dandelion(50, 50, 0, 100.0, 10);
    dandelion->setXY(SCREEN_WIDTH/2 -25 , SCREEN_HEIGHT/2 -25);
    dandelion->setSpeed(0);
    dandelion->setHealth(100.0);


    // 50개의 몬스터를 벡터로 생성합니다.
    //std::vector<Monster*> monsters;
   

    // projectiles 벡터를 비웁니다.
    dogPoop->projectiles.clear();
    
    // 배경 이미지 로드 
    bg_surface = IMG_Load("../Resources/bg.jpg");
    bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
    SDL_FreeSurface(bg_surface);
    bg_source_rect = { 0,0,600,600 };
    bg_dest_rect = { 0, 0, 600, 600 };

    //강아지똥 이미지 로드
    dp_surface = IMG_Load("../Resources/dogPoop.png");
    dp_texture = SDL_CreateTextureFromSurface(g_renderer, dp_surface);
    SDL_FreeSurface(dp_surface);
    dp_source_rect = { 0,0, 32, 32 };
    dp_dest_rect = { 0, 0, 50,50 };

    //민들레 이미지 로드
    d_surface = IMG_Load("../Resources/dandelion.png");
    d_texture = SDL_CreateTextureFromSurface(g_renderer, d_surface);
    SDL_FreeSurface(d_surface);
    d_source_rect = { 0,0, 32, 32 };
    d_dest_rect = { 0, 0, 50,50 };

    //병아리 이미지 로드
    c_surface = IMG_Load("../Resources/chick.png");
    c_texture = SDL_CreateTextureFromSurface(g_renderer, c_surface);
    SDL_FreeSurface(c_surface);
    c_source_rect = { 0,0, 32, 32 };
    c_dest_rect = { 0, 0, 32,32 };

    //참새 이미지 로드
    s_surface = IMG_Load("../Resources/sparrow.png");
    s_texture = SDL_CreateTextureFromSurface(g_renderer, s_surface);
    SDL_FreeSurface(s_surface);
    s_source_rect = { 0,0, 32, 32 };
    s_dest_rect = { 0, 0, 32,32 };

    //투사체 이미지 로드
    p_surface = IMG_Load("../Resources/projectile.png");
    p_texture = SDL_CreateTextureFromSurface(g_renderer, p_surface);
    SDL_FreeSurface(p_surface);
    p_source_rect = { 0,0, 32, 32 };
    p_dest_rect = { 0, 0, 40,40 };

}


Stage1::~Stage1() {
    delete dandelion;
    delete dogPoop;
    for (int i = 0; i < monsterCount; ++i) {
        delete monsters[i];
    }
    for (auto monster : monsters) {
        delete monster;
    }
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyTexture(dp_texture);
    SDL_DestroyTexture(d_texture);
    SDL_DestroyTexture(c_texture);
    SDL_DestroyTexture(s_texture);
    SDL_DestroyTexture(p_texture);
} 

