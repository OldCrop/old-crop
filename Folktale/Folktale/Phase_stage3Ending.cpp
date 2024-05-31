#include "Phase_stage3Ending.h"

Phase_stage3Ending::Phase_stage3Ending() {
    // 배경 텍스쳐
    SDL_Surface* temp_sheet_surface = IMG_Load("../../Resources/winEnding.png");
    winEnding_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수

    temp_sheet_surface = IMG_Load("../../Resources/loseEnding.png");
    loseEnding_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수

    temp_sheet_surface = IMG_Load("../../Resources/loseEnding_gameover.png");
    loseEnding_texture_gameover = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수

    ending_destination.x = 40;
    ending_destination.y = 40;
    ending_destination.w = screenWidth-80;
    ending_destination.h = screenHeight-80;
    
    // 버튼 텍스쳐
    SDL_Surface* tmp_surface = IMG_Load("../../Resources/retry.png");
    retry_button_texture = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
    if (retry_button_texture == NULL)
        std::cout<<"retry_button_texture is NULL\n"<<std::endl;
    SDL_FreeSurface(tmp_surface);
    retry_button_destination = { 800,580,100,100 };

    tmp_surface = IMG_Load("../../Resources/main.png");
    main_button_texture = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);
    main_button_destination= { 910,580,100,100 };

    win_music = Mix_LoadMUS("../../Resources/happyEnding.mp3");
    lose_music = Mix_LoadMUS("../../Resources/sadEnding.mp3");
    button_sound = Mix_LoadWAV("../../Resources/pauseSound.wav");
    
    Mix_VolumeMusic(128);

    button = false;
    endingPhaseStartTime = SDL_GetTicks();;
    buttonPushed = 0; //0이면 버튼 안누름, 1이면 retry버튼 누름, 2이면 home버튼 누름
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
                if (button) {//버튼이 켜져있으면 버튼을 누르는 순간

                    int mouse_x = event.button.x;
                    int mouse_y = event.button.y;

                    if (mouse_x >= retry_button_destination.x && mouse_x <= retry_button_destination.x + retry_button_destination.w &&
                        mouse_y >= retry_button_destination.y && mouse_y <= retry_button_destination.y + retry_button_destination.h
                        )
                        buttonPushed= 1;
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
    /*if (game_result == 1) {
        std::cout << "승리"<< std::endl;
        Mix_PlayChannel(-1, win_music, 0);
        
        flag = false;
    }
    else if (game_result == 2 ) {
        std::cout << "패배" << std::endl;
        Mix_PlayChannel(-1, lose_music, 0);
        flag = false;
    }*/

    

    int currentTime = SDL_GetTicks();
    if (currentTime - endingPhaseStartTime > 3000) { // 3초가 지났다면
        // 버튼 보이게 함
        button = true;
    }else
        button = false;

    

    
    if (buttonPushed == 1) {
        Mix_PlayChannel(-1, button_sound, 0);//효과음 출력
        g_current_game_phase = PHASE_STAGE;
        //game_result = 0;
    }
    else if (buttonPushed == 2) {
        Mix_PlayChannel(-1, button_sound, 0);//효과음 출력
        g_current_game_phase = PHASE_INTRO;
        //game_result = 0;
    }
    
}

    
void Phase_stage3Ending::Render() {
    
    if (game_result == 1) {
        SDL_RenderCopy(g_renderer, winEnding_texture, NULL, &ending_destination);

        //std::cout << "winEnding_texture" << std::endl;

    }
    else if (game_result == 2) {
        if (button) {
            //std::cout << "loseEnding_texture_gameover" << std::endl;
            SDL_RenderCopy(g_renderer, loseEnding_texture_gameover, NULL, &ending_destination);
        }
        else
            SDL_RenderCopy(g_renderer, loseEnding_texture, NULL, &ending_destination);
    }

    if (button) {
        SDL_RenderCopy(g_renderer, retry_button_texture, NULL, &retry_button_destination);
        SDL_RenderCopy(g_renderer, main_button_texture, NULL, &main_button_destination);
    }
    
    
    SDL_RenderCopy(g_renderer, fame_texture, NULL, &frame_destination);
    SDL_RenderPresent(g_renderer);
}

void Phase_stage3Ending::Reset() {
    button = false;
    buttonPushed = 0; //0이면 버튼 안누름, 1이면 retry버튼 누름, 2이면 home버튼 누름
    
    endingPhaseStartTime = SDL_GetTicks();
    flag = true;

   // std::cout << "game_result : " << game_result << std::endl;  
    if (game_result == 1)
        Mix_PlayMusic(win_music, 1);
    else if(game_result == 2)
        Mix_PlayMusic(lose_music, 1);
    
}

Phase_stage3Ending::~Phase_stage3Ending() {
    SDL_DestroyTexture(winEnding_texture);
    SDL_DestroyTexture(loseEnding_texture);
    SDL_DestroyTexture(retry_button_texture);
    SDL_DestroyTexture(main_button_texture);

    
    Mix_FreeMusic(win_music);
    Mix_FreeMusic(lose_music);
    Mix_FreeChunk(button_sound);

}


