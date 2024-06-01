#include<iostream>
#include "Phase_stage3Game.h"
#include "Phase_stage3Intro.h"
#include "Phase_stage3Ending.h"
#include "STAGE.h"

/////////////////////////////////////////////////
// Declaration
SDL_Window* g_window;
SDL_Renderer* g_renderer;
bool g_flag_running;
Uint32 g_last_time_ms;
int screenWidth, screenHeight;
int g_current_game_phase;
int g_prev_game_phase;
int game_result;

SDL_Texture* fame_texture;
SDL_Rect frame_destination;
TTF_Font* font;


int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }

    // Initializing SDL library
    g_window = SDL_CreateWindow("STAGE3", 100, 100, 1080, 720, 0);
    g_renderer = SDL_CreateRenderer(g_window, -1, 0);
    SDL_GetWindowSize(g_window, &screenWidth, &screenHeight);//크기 지정

    SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
   
    //frame 텍스쳐
    fame_texture = SDL_CreateTextureFromSurface(g_renderer, IMG_Load("../../Resources/frame.png"));
    frame_destination = { 0,0,screenWidth,screenHeight };
    font = TTF_OpenFont("../../Resources/PF.ttf", 100);

    g_flag_running = true;

    g_last_time_ms = SDL_GetTicks();
    game_result = 0;

    //페이즈 생성
    PhaseInterface* game_phases[3];

    game_phases[0] = new Phase_stage3Intro;
    game_phases[1] = new Stage3;
    game_phases[2] = new Phase_stage3Ending;

    g_current_game_phase = PHASE_INTRO;
    g_prev_game_phase = PHASE_INTRO;

    game_phases[g_prev_game_phase]->Reset(); //추가했더염,,, 노래때문에

    while (g_flag_running)
    {
        Uint32 cur_time_ms = SDL_GetTicks();


        // 게임 로직 업데이트 부분
        int currentTime = SDL_GetTicks();
        if (currentTime - g_last_time_ms < 33) {
            continue;
        }
        if (g_prev_game_phase != g_current_game_phase) {
            game_phases[g_prev_game_phase]->Reset();
            game_phases[g_current_game_phase]->Reset(); //추가했더염,,,노래링 시간 때문에
        }
        g_prev_game_phase = g_current_game_phase;
        game_phases[g_current_game_phase]->HandleEvents();
        game_phases[g_current_game_phase]->Update();
        game_phases[g_current_game_phase]->Render();

        g_last_time_ms = cur_time_ms;
        
        

    }

    delete game_phases[0];
    delete game_phases[1];
    delete game_phases[2];


    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}