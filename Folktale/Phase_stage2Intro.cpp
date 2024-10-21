#include "Phase_stage2Intro.h"
#include <iostream>

SDL_Rect stage2_intro_source_rect;

Phase_stage2Intro::Phase_stage2Intro() {
    // ��� �ؽ���
    SDL_Surface* temp_sheet_surface;

    bg_destination.x = 40;
    bg_destination.y = 40;
    bg_destination.w = screenWidth - 80;
    bg_destination.h = screenHeight - 80;

    background_music = Mix_LoadMUS("../../Resources/stage2/Intro.mp3");
    Mix_VolumeMusic(128);

    temp_sheet_surface = IMG_Load("../../Resources/stage2/stage2/stage2_intro1.png");
    first_intro_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�

    temp_sheet_surface = IMG_Load("../../Resources/stage2/stage2/stage2_intro2.png");
    second_intro_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�

    temp_sheet_surface = IMG_Load("../../Resources/stage2/stage2/stage2_intro3.png");
    third_intro_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        std::cerr << "Mix_OpenAudio: " << Mix_GetError() << std::endl;
        return;
    }

    bg_texture = first_intro_texture;
    count = 0; //0,1,2 ��� �̹��� ����� ��
}

void Phase_stage2Intro::HandleEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {

        case SDL_QUIT:
            g_flag_running = false;
            break;

        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_RETURN)
                count++;

            break;
        }
    }

}

void Phase_stage2Intro::Update() {
    if (count == 3) // 3�� �� ������ ���������� ��ȯ
        g_current_game_phase = PHASE_STAGE1_GAME;
}

void Phase_stage2Intro::Render() {
    SDL_RenderClear(g_renderer); // ������ �ʱ�ȭ

    if (count == 0) {
        bg_texture = first_intro_texture;
    }
    else if (count == 1) {
        bg_texture = second_intro_texture;
    }
    else if (count == 2) {
        bg_texture = third_intro_texture;
    }
    SDL_RenderCopy(g_renderer, bg_texture, NULL, &bg_destination);
    SDL_RenderCopy(g_renderer, frame_texture, NULL, &frame_destination);
    SDL_RenderPresent(g_renderer);
}

void Phase_stage2Intro::Reset() {
    count = 0;
    bg_texture = first_intro_texture;
    Mix_PlayMusic(background_music, -1);
}

Phase_stage2Intro::~Phase_stage2Intro() {
    SDL_DestroyTexture(first_intro_texture);
    SDL_DestroyTexture(second_intro_texture);
    SDL_DestroyTexture(third_intro_texture);
    SDL_DestroyTexture(bg_texture);
    Mix_FreeMusic(background_music);

}
