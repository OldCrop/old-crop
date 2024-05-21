#pragma once
#include <iostream>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <iomanip>
#include <sstream>
//#include <memory>
#include "Creature_stage1.h"
#include <vector>
#include <ctime>  // time 함수를 사용하기 위해 필요합니다.
#include <cstdlib>  // srand 함수를 사용하기 위해 필요합니다.

extern SDL_Renderer* g_renderer;
extern SDL_Window* g_window;
class Stage1
{
public:
    Stage1();
    ~Stage1();

    void HandleEvents();
    void Update();
    void Render();
    void Reset();


private:
    Uint32 lastFireTime = 0;  // 마지막으로 투사체를 발사한 시간
    Uint32 invincibleStartTime = 0;
    Uint32 invincibleTime = 0;
    Uint32 dandelionInvincibleStartTime = 0;
    Uint32 monsterDamage = 0;
    Uint32 dogPoopInvincibleStartTime = 0;
    Uint32 gameStartTime = 0;
    Uint32 now = 0;


    DogPoop* dogPoop;
    Dandelion* dandelion;
    Chick* chick;
    Sparrow* sparrow;
    SDL_Window* window;
    SDL_Renderer* renderer;
    //강아지똥 이미지 변수
    SDL_Surface* dp_surface;
    SDL_Texture* dp_texture;
    SDL_Rect dp_source_rect;
    SDL_Rect dp_dest_rect;

    //민들레 이미지 변수
    SDL_Surface* d_surface;
    SDL_Texture* d_texture;
    SDL_Rect d_source_rect;
    SDL_Rect d_dest_rect;

    //병아리 이미지 변수
    SDL_Surface* c_surface;
    SDL_Texture* c_texture;
    SDL_Rect c_source_rect;
    SDL_Rect c_dest_rect;
    
    //참새 이미지 변수
    SDL_Surface* s_surface;
    SDL_Texture* s_texture;
    SDL_Rect s_source_rect;
    SDL_Rect s_dest_rect;

    //배경 이미지 변수
    SDL_Surface* bg_surface;
    SDL_Texture* bg_texture;
    SDL_Rect bg_source_rect;
    SDL_Rect bg_dest_rect;

    //투사체 이미지 변수
    SDL_Surface* p_surface;
    SDL_Texture* p_texture;
    SDL_Rect p_source_rect;
    SDL_Rect p_dest_rect;

    std::vector<Monster*> monsters;
};


extern bool g_flag_running;
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;
const int COLLISION_DISTANCE = 20;
extern bool is_intro_initialized;

extern bool g_key_left;
extern bool g_key_right;
extern bool g_key_up;
extern bool g_key_down;
extern bool g_key_space;
extern Uint32 FIRE_COOLDOWN;  // 투사체 발사 쿨타임
extern bool is_rock;

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    LEFT_UP, 
    RIGHT_UP,
    LEFT_DOWN, 
    RIGHT_DOWN
};

extern Direction g_direction;

