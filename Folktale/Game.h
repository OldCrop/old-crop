#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <random>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_image.h"

// Game Phases
const int PHASE_MAIN_INTRO = 0;
const int PHASE_INTRO = 1;
const int PHASE_MAIN_MENU = 2;
const int PHASE_STAGE1_INTRO = 3;
const int PHASE_STAGE1_GAME = 4;
const int PHASE_STAGE1_ENDING = 5;
const int PHASE_STAGE2_INTRO = 6;
const int PHASE_STAGE2_GAME = 7;
const int PHASE_STAGE2_ENDING = 8;
const int PHASE_STAGE3_INTRO = 9;
const int PHASE_STAGE3_GAME = 10;
const int PHASE_STAGE3_ENDING = 11;
const int PHASE_GALLERY = 12;
const int PHASE_ENDING = 13;

class PhaseInterface
{
public:
    PhaseInterface() {};
    virtual ~PhaseInterface() {};

    virtual void HandleEvents() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void Reset() = 0;

};

void InitGame();
void ClearGame();

extern TTF_Font* font;
extern SDL_Texture* frame_texture;
extern SDL_Rect frame_destination;

extern int g_current_game_phase;
extern int g_prev_game_phase;

extern bool g_flag_running;
extern SDL_Renderer* g_renderer;
extern SDL_Window* g_window;
extern int screenWidth, screenHeight;
extern int game_result;

// �������� �� ������ ���� �����ϴ� ���
const int ENDINGS_PER_STAGE = 3;

// ���������� ���� �����ϴ� ���
const int NUMBER_OF_STAGES = 3; // ���� �������� ���� �����ϼ���

// �� ������������ �� ������ �����ϴ� �迭 ����
extern bool viewedEndings[NUMBER_OF_STAGES][ENDINGS_PER_STAGE];

