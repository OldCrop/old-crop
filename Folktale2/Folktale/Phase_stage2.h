#pragma once
#include <SDL.h>
#include "Creature_stage2.h"

extern SDL_Renderer* g_renderer;
extern SDL_Window* g_window;
extern bool g_flag_running;


class Stage2 {
public:
    Stage2();
    ~Stage2();

    void HandleEvents();
    void Update();
    void Render();
    void Reset();

    int getResult() {
        return this->game_result;
    }

private:
    Turtle* turtle;
    Rabbit* rabbit;
    Coral* coral;

    // 방향키 조작 변수들
    bool f_list[4];
    int f_state; // 현재 눌린 키 정보
    bool stop; // 정지 정보

    // 승패 확인 변수
    int game_result=0;

    //미로
  


    
    //텍스쳐
    SDL_Texture* stage2_bg_texture;
    SDL_Texture* turtle_texture;
    SDL_Texture* rabbit_texture;
    SDL_Texture* coral_texture;
    SDL_Texture* gan_texture;
    SDL_Texture* heart0_texture;
    SDL_Texture* heart2_texture;


    //텍스쳐 사각형
    SDL_Rect turtle_destination_rect;
    SDL_Rect rabbit_destination_rect;
    SDL_Rect coral_destination_rect;
    SDL_Rect stage2_bg_destination_rect;
    SDL_Rect gan_destination_rect;
    SDL_Rect heart0_destination_rect;
    SDL_Rect heart2_destination_rect;

};

