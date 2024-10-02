#include "Phase_stage3Ending.h"

Phase_stage3Ending::Phase_stage3Ending() {
    // ��� �ؽ���
    SDL_Surface* temp_sheet_surface = IMG_Load("../../Resources/stage3/happyEnding.png");
    winEnding_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�

    temp_sheet_surface = IMG_Load("../../Resources/stage3/sadEnding1.png");
    loseEnding_texture1 = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�

    temp_sheet_surface = IMG_Load("../../Resources/stage3/sadEnding2.png");
    loseEnding_texture2 = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�

    //temp_sheet_surface = IMG_Load("../../Resources/stage3/sadEnding3.png");
    //loseEnding_texture3 = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    //SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�

    temp_sheet_surface = IMG_Load("../../Resources/stage3/sadEnding_gameover.png");
    loseEnding_texture_gameover = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�

    ending_destination.x = 40;
    ending_destination.y = 40;
    ending_destination.w = screenWidth - 80;
    ending_destination.h = screenHeight - 80;

    // ��ư �ؽ���
    SDL_Surface* tmp_surface = IMG_Load("../../Resources/btn_retry.png");
    retry_button_texture = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
    if (retry_button_texture == NULL)
        std::cout << "retry_button_texture is NULL\n" << std::endl;
    SDL_FreeSurface(tmp_surface);
    retry_button_destination = { 800,580,100,100 };

    tmp_surface = IMG_Load("../../Resources/btn_main.png");
    main_button_texture = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);
    main_button_destination = { 910,580,100,100 };

    win_music = Mix_LoadMUS("../../Resources/stage3/happyEnding.mp3");
    lose_music = Mix_LoadMUS("../../Resources/stage3/sadEnding.mp3");
    button_sound = Mix_LoadWAV("../../Resources/stage3/pauseSound.wav");

    Mix_VolumeMusic(128);

    button = false;
    endingPhaseStartTime = SDL_GetTicks();;
    buttonPushed = 0; //0�̸� ��ư �ȴ���, 1�̸� retry��ư ����, 2�̸� home��ư ����
    pageCheck = 0;

    if (!win_music)
    {
        printf(" %s\n", Mix_GetError());
        // this might be a critical error...
    }

    if (!lose_music)
    {
        printf(" %s\n", Mix_GetError());
        // this might be a critical error...
    }

    if (!button_sound)
    {
        printf(" %s\n", Mix_GetError());
        // this might be a critical error...
    }

    buttonToTime = 0;


}

void Phase_stage3Ending::HandleEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {

        case SDL_QUIT:
            g_flag_running = false;
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
                if (button) {//��ư�� ���������� ��ư�� ������ ����

                    int mouse_x = event.button.x;
                    int mouse_y = event.button.y;

                    if (mouse_x >= retry_button_destination.x && mouse_x <= retry_button_destination.x + retry_button_destination.w &&
                        mouse_y >= retry_button_destination.y && mouse_y <= retry_button_destination.y + retry_button_destination.h
                        )
                        buttonPushed = 1;
                    else if (mouse_x >= main_button_destination.x && mouse_x <= main_button_destination.x + main_button_destination.w &&
                        mouse_y >= main_button_destination.y && mouse_y <= main_button_destination.y + main_button_destination.h
                        )
                        buttonPushed = 2;
                }

            break;

        }
    }
}

void Phase_stage3Ending::Update() {
    int currentTime = SDL_GetTicks();

    if (game_result == 1) { //���ǿ����̸� �ٷ� ��ư ������ ����
        pageCheck = 2;

    }
    else if (game_result == 2) { //���¿����̸� 3�ʸ��� ������ �Ѿ��
        if (currentTime - endingPhaseStartTime > 3000 && pageCheck < 3) { // 3�ʰ� �����ٸ�

            pageCheck++;
            endingPhaseStartTime = currentTime;

        }
    }


    if (pageCheck == 2) {
        button = true;
        if (currentTime - endingPhaseStartTime > 3000) { // 3�ʰ� �����ٸ�

        }
    }
    else {
        button = false;
    }




    if (buttonPushed == 1) {
        Mix_PlayChannel(-1, button_sound, 0);//ȿ���� ���
        g_current_game_phase = PHASE_STAGE3_GAME;
    }
    else if (buttonPushed == 2) {
        Mix_PlayChannel(-1, button_sound, 0);//ȿ���� ���
        g_current_game_phase = PHASE_MAIN_MENU;
    }

}


void Phase_stage3Ending::Render() {

    if (game_result == 1) {
        SDL_RenderCopy(g_renderer, winEnding_texture, NULL, &ending_destination);

        //std::cout << "winEnding_texture" << std::endl;

    }
    else if (game_result == 2) {

        switch (pageCheck)
        {
        case 0:
            SDL_RenderCopy(g_renderer, loseEnding_texture1, NULL, &ending_destination);
            break;
        case 1:
            SDL_RenderCopy(g_renderer, loseEnding_texture2, NULL, &ending_destination);
            break;
        case 2:
            SDL_RenderCopy(g_renderer, loseEnding_texture_gameover, NULL, &ending_destination);
            break;

        default:
            break;
        }



    }

    if (button) {
        SDL_RenderCopy(g_renderer, retry_button_texture, NULL, &retry_button_destination);
        SDL_RenderCopy(g_renderer, main_button_texture, NULL, &main_button_destination);
    }


    SDL_RenderCopy(g_renderer, frame_texture, NULL, &frame_destination);
    SDL_RenderPresent(g_renderer);
}

void Phase_stage3Ending::Reset() {
    button = false;
    buttonPushed = 0; //0�̸� ��ư �ȴ���, 1�̸� retry��ư ����, 2�̸� home��ư ����

    endingPhaseStartTime = SDL_GetTicks();
    flag = true;
    pageCheck = 0;

    // std::cout << "game_result : " << game_result << std::endl;  
    if (game_result == 1)
        Mix_PlayMusic(win_music, 1);
    else if (game_result == 2)
        Mix_PlayMusic(lose_music, 1);

}

Phase_stage3Ending::~Phase_stage3Ending() {
    SDL_DestroyTexture(winEnding_texture);
    SDL_DestroyTexture(loseEnding_texture1);
    SDL_DestroyTexture(loseEnding_texture2);
    //SDL_DestroyTexture(loseEnding_texture3);
    SDL_DestroyTexture(loseEnding_texture_gameover);

    SDL_DestroyTexture(retry_button_texture);
    SDL_DestroyTexture(main_button_texture);

    Mix_FreeMusic(win_music);
    Mix_FreeMusic(lose_music);
    Mix_FreeChunk(button_sound);

}


