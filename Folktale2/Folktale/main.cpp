#include<iostream>
#include "Phase_stage2.h"
#include "Creature_stage2.h"


SDL_Window* g_window;
SDL_Renderer* g_renderer;
bool g_flag_running;
Uint32 g_last_time_ms;

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);

	Uint32 cur_time_ms = SDL_GetTicks();
	// Initializing SDL library
	g_window = SDL_CreateWindow("STAGE2", 100, 100, 1000, 800, 0);


	g_renderer = SDL_CreateRenderer(g_window, -1, 0);
	
	g_flag_running = true;
	g_last_time_ms = SDL_GetTicks();

	Stage2* stage2 = new Stage2();
	while (g_flag_running) {

		if (stage2->getResult() == 1 || stage2->getResult() == 2) { //승리로 게임 끝남
			g_flag_running = false;
		}

		stage2->HandleEvents();
		stage2->Update();
		stage2->Render();
		g_last_time_ms = cur_time_ms;
	}
	delete stage2;
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
	SDL_Quit();
    
	return 0;
}