#include "Phase_stage1Ending.h"

Phase_stage1Ending::Phase_stage1Ending() {
    //�ε鷹�� HP�� 0�� �� �����̹���1
    SDL_Surface* temp_sheet_surface = IMG_Load("../../Resources/stage1/IntroEnding/stg_ending1.png");
    stg1_dandelion_ending_texture1 = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);

    // �����̹���1�� ���ӿ����̹���
    SDL_Surface* temp_sheet_surface2 = IMG_Load("../../Resources/stage1/IntroEnding/stg_ending1_1.png");
    stg1_dandelion_ending_texture2 = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface2);
    SDL_FreeSurface(temp_sheet_surface2);//���� �ʼ�

    //���������� HP�� 0�� �� �����̹���1
    temp_sheet_surface = IMG_Load("../../Resources/stage1/IntroEnding/stg_ending2.png");
    stg1_dogPoop_ending_texture1 = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�

    // �����̹���2�� ���ӿ����̹���
    SDL_Surface* temp_sheet_surface3 = IMG_Load("../../Resources/stage1/IntroEnding/stg_ending2_1.png");
    stg1_dogPoop_ending_texture2 = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface3);
    SDL_FreeSurface(temp_sheet_surface3);//���� �ʼ�

    //���ǿ��� �̹���
    temp_sheet_surface = IMG_Load("../../Resources/stage1/IntroEnding/stg_ending3.png");
    stg1_happy_ending_texture1 = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�

    stg1_ending_destination.x = 40;
    stg1_ending_destination.y = 40;
    stg1_ending_destination.w = screenWidth - 80;
    stg1_ending_destination.h = screenHeight - 80;


    //���忣�� ȿ���� �ε�
    stg1_gosad_sound = Mix_LoadWAV("../../Resources/stage1/sounds/sadEnding.wav");
    //���ǿ��� ȿ���� �ε�
    stg1_gohappy_sound = Mix_LoadWAV("../../Resources/stage1/sounds/happyEnding.wav");

    //��ư �ؽ���
    SDL_Surface* tmp_surface1 = IMG_Load("../../Resources/btn_retry.png");
    stg1_retry_button_texture = SDL_CreateTextureFromSurface(g_renderer, tmp_surface1);
    SDL_FreeSurface(tmp_surface1);

    stg1_retry_button_destination.x = 800;
    stg1_retry_button_destination.y = 580;
    stg1_retry_button_destination.w = 100;
    stg1_retry_button_destination.h = 100;

    SDL_Surface* tmp_surface2 = IMG_Load("../../Resources/btn_main.png");
    stg1_home_button_texture = SDL_CreateTextureFromSurface(g_renderer, tmp_surface2);
    SDL_FreeSurface(tmp_surface2);

    stg1_home_button_destination.x = stg1_retry_button_destination.x + 110;
    stg1_home_button_destination.y = stg1_retry_button_destination.y;
    stg1_home_button_destination.w = 100;
    stg1_home_button_destination.h = 100;


    stg1_button = false;
    stg1_endingPhaseStartTime = 0;
    stg1_buttonPushed = 0; //0�̸� ��ư �ȴ���, 1�̸� retry��ư ����, 2�̸� home��ư ����
    stg1_pageCheck = 0;

    game_result = 0;
}

void Phase_stage1Ending::HandleEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {

        case SDL_QUIT:
            g_flag_running = false;
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
                if (stg1_button) {//��ư�� ���������� ��ư�� ������ ����

                    int mouse_x = event.button.x;
                    int mouse_y = event.button.y;
                    //retry
                    if (mouse_x >= stg1_retry_button_destination.x && mouse_x <= stg1_retry_button_destination.x + stg1_retry_button_destination.w &&
                        mouse_y >= stg1_retry_button_destination.y && mouse_y <= stg1_retry_button_destination.y + stg1_retry_button_destination.h
                        )
                        stg1_buttonPushed = 1;
                    //main
                    else if (mouse_x >= stg1_home_button_destination.x && mouse_x <= stg1_home_button_destination.x + stg1_home_button_destination.w &&
                        mouse_y >= stg1_home_button_destination.y && mouse_y <= stg1_home_button_destination.y + stg1_home_button_destination.h
                        )
                        stg1_buttonPushed = 2;
                }

            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_RETURN) {
                stg1_pageCheck++;
            }

            break;
        }
    }
}

void Phase_stage1Ending::Update() {
    if (g_prev_game_phase != g_current_game_phase)
        stg1_endingPhaseStartTime = SDL_GetTicks();

    int currentTime = SDL_GetTicks();
    if (currentTime - stg1_endingPhaseStartTime > 3000) { // 3�ʰ� �����ٸ�
        // ��ư ���̰� ��
        stg1_button = true;
    }
    else
        stg1_button = false;
    /*
    if (stg1_pageCheck == 1) {
        g_current_game_phase = PHASE_INTRO;
        game_result = 0;
    }*/

    //retry ��ư ������ ��������
    if (stg1_buttonPushed == 1) {
        g_current_game_phase = PHASE_STAGE1_GAME;
    } //main ��ư ������ ��Ʈ��
    else if (stg1_buttonPushed == 2) {
        g_current_game_phase = PHASE_MAIN_MENU;
    }
}


void Phase_stage1Ending::Render() {
    SDL_RenderCopy(g_renderer, frame_texture, NULL, &frame_destination);

    SDL_Texture* stg1_ending_texturetemp = NULL;
    if (game_result == 1) {
        stg1_ending_texturetemp = stg1_dandelion_ending_texture1;
        //SDL_RenderCopy(g_renderer, stg1_dandelion_ending_texture1, NULL, &stg1_ending_destination);
        if (stg1_button) stg1_ending_texturetemp = stg1_dandelion_ending_texture2;
    }
    else if (game_result == 2) {
        stg1_ending_texturetemp = stg1_dogPoop_ending_texture1;
        //SDL_RenderCopy(g_renderer, stg1_dogPoop_ending_texture1, NULL, &stg1_ending_destination);
        if (stg1_button) stg1_ending_texturetemp = stg1_dogPoop_ending_texture2;
    }
    else if (game_result == 3) {
        stg1_ending_texturetemp = stg1_happy_ending_texture1;
        //SDL_RenderCopy(g_renderer, stg1_happy_ending_texture1, NULL, &stg1_ending_destination);
    }
    SDL_RenderCopy(g_renderer, stg1_ending_texturetemp, NULL, &stg1_ending_destination);

    if (stg1_button) {
        SDL_RenderCopy(g_renderer, stg1_retry_button_texture, NULL, &stg1_retry_button_destination);
        SDL_RenderCopy(g_renderer, stg1_home_button_texture, NULL, &stg1_home_button_destination);
    }

    SDL_RenderPresent(g_renderer);
}

void Phase_stage1Ending::Reset() {
    //������ �ٲ�� 3�ʼ���
    stg1_endingPhaseStartTime = SDL_GetTicks();
    //����� ����
    Mix_HaltMusic();
    stg1_button = false;
    stg1_buttonPushed = 0; //0�̸� ��ư �ȴ���, 1�̸� retry��ư ����, 2�̸� home��ư ����
    stg1_pageCheck = 0;
    //���� ȿ���� ���
    if (game_result == 1 || game_result == 2) {
        Mix_PlayChannel(-1, stg1_gosad_sound, 0);
    }
    else if (game_result == 3) {
        Mix_PlayChannel(-1, stg1_gohappy_sound, 0);
    }
    ///endingPhaseStartTime = 0;
}

Phase_stage1Ending::~Phase_stage1Ending() {

    SDL_DestroyTexture(stg1_retry_button_texture);
    SDL_DestroyTexture(stg1_home_button_texture);
    SDL_DestroyTexture(stg1_dandelion_ending_texture1);
    SDL_DestroyTexture(stg1_dogPoop_ending_texture1);
    SDL_DestroyTexture(stg1_happy_ending_texture1);
    SDL_DestroyTexture(stg1_dandelion_ending_texture2);
    SDL_DestroyTexture(stg1_dogPoop_ending_texture2);

    Mix_FreeChunk(stg1_gosad_sound);
    Mix_FreeChunk(stg1_gohappy_sound);

}

