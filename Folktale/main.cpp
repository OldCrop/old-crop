#include<iostream>
#include <SDL.h>
#include "SDL_image.h"
#include "Phase_stage1.h"
#include <windows.h>
SDL_Window* g_window;
SDL_Renderer* g_renderer;
Uint32 g_last_time_ms;
bool g_flag_running = true;
bool is_intro_initialized = false;

int main(int argc, char* argv[]) {
    Stage1 stage1;
    // Initializing SDL library
    SDL_Init(SDL_INIT_EVERYTHING);

    //ttf init
    //TTF_Init();

    //if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        //하드웨어에 잘 접근하지 못했다면 -1을 리턴함
        //std::cout << "Mix_OpenAudio " << Mix_GetError() << std::endl;
        //exit(1);
   // }

    g_window = SDL_CreateWindow("202221226", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    g_renderer = SDL_CreateRenderer(g_window, -1, 0);

    

    g_last_time_ms = SDL_GetTicks();

    while (g_flag_running)
    {
        Uint32 cur_time_ms = SDL_GetTicks();
        if (cur_time_ms - g_last_time_ms < 33)
            continue;
        if (!is_intro_initialized) {
            stage1.Reset();
            is_intro_initialized = true;
        }
        stage1.HandleEvents();
        stage1.Update();
        stage1.Render();

        
        Sleep(33);
        g_last_time_ms = cur_time_ms;

    }


    stage1.~Stage1();
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);

    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();

    return 0;
}