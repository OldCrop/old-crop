#include "Game.h"
#include "Phase_Gallery.h"

Gallery::Gallery()
{
    // Initialization code...
    std::cout << "Gallery phase initialized" << std::endl;

    //��� �̹��� �ҷ�����
    SDL_Surface* gallery_bg_surface = IMG_Load("../../Resources/main.png");
    if (!gallery_bg_surface) {
        std::cerr << "Failed to load gallery background: " << IMG_GetError() << std::endl;
        return;
    }
    gallery_bg_texture = SDL_CreateTextureFromSurface(g_renderer, gallery_bg_surface);
    SDL_FreeSurface(gallery_bg_surface);

    gallery_bg_source_rect = { 0, 0, 1080, 720 };
    gallery_bg_destination_rect = { 0, 0, 1080, 720 };

    //���� ���� �� �̹���
    SDL_Surface* ending_before_surface = IMG_Load("../../Resources/gallery/ending_before.png");
    if (!ending_before_surface) {
        std::cerr << "Failed to load ending_before: " << IMG_GetError() << std::endl;
        return;
    }
    ending_before11_texture = SDL_CreateTextureFromSurface(g_renderer, ending_before_surface);
    ending_before12_texture = SDL_CreateTextureFromSurface(g_renderer, ending_before_surface);
    ending_before13_texture = SDL_CreateTextureFromSurface(g_renderer, ending_before_surface);
    ending_before21_texture = SDL_CreateTextureFromSurface(g_renderer, ending_before_surface);
    ending_before22_texture = SDL_CreateTextureFromSurface(g_renderer, ending_before_surface);
    ending_before31_texture = SDL_CreateTextureFromSurface(g_renderer, ending_before_surface);
    ending_before32_texture = SDL_CreateTextureFromSurface(g_renderer, ending_before_surface);

    ending_before_source_rect = { 0, 0, ending_before_surface->w, ending_before_surface->h };
    SDL_FreeSurface(ending_before_surface);

    ending11_destination_rect = { 192, 140, ending_before_source_rect.w, ending_before_source_rect.h };
    ending12_destination_rect = { 85, 340, ending_before_source_rect.w, ending_before_source_rect.h };
    ending13_destination_rect = { 300, 340, ending_before_source_rect.w, ending_before_source_rect.h };
    ending21_destination_rect = { 625, 105, ending_before_source_rect.w, ending_before_source_rect.h };
    ending22_destination_rect = { 840, 105, ending_before_source_rect.w, ending_before_source_rect.h };
    ending31_destination_rect = { 625, 365, ending_before_source_rect.w, ending_before_source_rect.h };
    ending32_destination_rect = { 840, 365, ending_before_source_rect.w, ending_before_source_rect.h };

	SDL_Surface* ending11_surface = IMG_Load("../../Resources/stage1/IntroEnding/stg_ending1.png");
	SDL_Surface* ending11_resized_surface = SDL_CreateRGBSurface(0, ending_before_source_rect.w, ending_before_source_rect.h, 32, 0, 0, 0, 0);
	SDL_BlitScaled(ending11_surface, NULL, ending11_resized_surface, NULL);
	ending_after11_texture = SDL_CreateTextureFromSurface(g_renderer, ending11_resized_surface);
	SDL_FreeSurface(ending11_surface);
	SDL_FreeSurface(ending11_resized_surface);

	SDL_Surface* ending12_surface = IMG_Load("../../Resources/stage1/IntroEnding/stg_ending2.png");
	SDL_Surface* ending12_resized_surface = SDL_CreateRGBSurface(0, ending_before_source_rect.w, ending_before_source_rect.h, 32, 0, 0, 0, 0);
	SDL_BlitScaled(ending12_surface, NULL, ending12_resized_surface, NULL);
	ending_after12_texture = SDL_CreateTextureFromSurface(g_renderer, ending12_resized_surface);
	SDL_FreeSurface(ending12_surface);
	SDL_FreeSurface(ending12_resized_surface);

	SDL_Surface* ending13_surface = IMG_Load("../../Resources/stage1/IntroEnding/stg_ending3.png");
	SDL_Surface* ending13_resized_surface = SDL_CreateRGBSurface(0, ending_before_source_rect.w, ending_before_source_rect.h, 32, 0, 0, 0, 0);
	SDL_BlitScaled(ending13_surface, NULL, ending13_resized_surface, NULL);
	ending_after13_texture = SDL_CreateTextureFromSurface(g_renderer, ending13_resized_surface);
	SDL_FreeSurface(ending13_surface);
	SDL_FreeSurface(ending13_resized_surface);

	SDL_Surface* ending21_surface = IMG_Load("../../Resources/stage2/stage2/stage2_ending_sad1.png");
	SDL_Surface* ending21_resized_surface = SDL_CreateRGBSurface(0, ending_before_source_rect.w, ending_before_source_rect.h, 32, 0, 0, 0, 0);
	SDL_BlitScaled(ending21_surface, NULL, ending21_resized_surface, NULL);
	ending_after21_texture = SDL_CreateTextureFromSurface(g_renderer, ending21_resized_surface);
	SDL_FreeSurface(ending21_surface);
	SDL_FreeSurface(ending21_resized_surface);

	SDL_Surface* ending22_surface = IMG_Load("../../Resources/stage2/stage2/stage2_ending_happy.png");
	SDL_Surface* ending22_resized_surface = SDL_CreateRGBSurface(0, ending_before_source_rect.w, ending_before_source_rect.h, 32, 0, 0, 0, 0);
	SDL_BlitScaled(ending22_surface, NULL, ending22_resized_surface, NULL);
	ending_after22_texture = SDL_CreateTextureFromSurface(g_renderer, ending22_resized_surface);
	SDL_FreeSurface(ending22_surface);
	SDL_FreeSurface(ending22_resized_surface);

	SDL_Surface* ending31_surface = IMG_Load("../../Resources/stage3/sadEnding1.png");
	SDL_Surface* ending31_resized_surface = SDL_CreateRGBSurface(0, ending_before_source_rect.w, ending_before_source_rect.h, 32, 0, 0, 0, 0);
	SDL_BlitScaled(ending31_surface, NULL, ending31_resized_surface, NULL);
	ending_after31_texture = SDL_CreateTextureFromSurface(g_renderer, ending31_resized_surface);
	SDL_FreeSurface(ending31_surface);
	SDL_FreeSurface(ending31_resized_surface);

	SDL_Surface* ending32_surface = IMG_Load("../../Resources/stage3/happyEnding.png");
	SDL_Surface* ending32_resized_surface = SDL_CreateRGBSurface(0, ending_before_source_rect.w, ending_before_source_rect.h, 32, 0, 0, 0, 0);
	SDL_BlitScaled(ending32_surface, NULL, ending32_resized_surface, NULL);
	ending_after32_texture = SDL_CreateTextureFromSurface(g_renderer, ending32_resized_surface);
	SDL_FreeSurface(ending32_surface);
	SDL_FreeSurface(ending32_resized_surface);

	ending11_texture = ending_before11_texture;
	ending12_texture = ending_before12_texture;
	ending13_texture = ending_before13_texture;
	ending21_texture = ending_before21_texture;
	ending22_texture = ending_before22_texture;
	ending31_texture = ending_before31_texture;
	ending32_texture = ending_before32_texture;

    SDL_Surface* frame_surface = IMG_Load("../../Resources/frame.png");
    if (!frame_surface) {
        std::cerr << "Failed to load frame: " << IMG_GetError() << std::endl;
        return;
    }
    frame_texture_ = SDL_CreateTextureFromSurface(g_renderer, frame_surface);
    SDL_FreeSurface(frame_surface);

    SDL_QueryTexture(frame_texture_, NULL, NULL, &frame_source_rectangle_.w, &frame_source_rectangle_.h);
    frame_source_rectangle_ = { 0, 0, frame_source_rectangle_.w, frame_source_rectangle_.h };
    frame11_destination_rect = { 192, 140, ending_before_source_rect.w, ending_before_source_rect.h };
    frame12_destination_rect = { 85, 340, ending_before_source_rect.w, ending_before_source_rect.h };
    frame13_destination_rect = { 300, 340, ending_before_source_rect.w, ending_before_source_rect.h };
    frame21_destination_rect = { 625, 105, ending_before_source_rect.w, ending_before_source_rect.h };
    frame22_destination_rect = { 840, 105, ending_before_source_rect.w, ending_before_source_rect.h };
    frame31_destination_rect = { 625, 365, ending_before_source_rect.w, ending_before_source_rect.h };
    frame32_destination_rect = { 840, 365, ending_before_source_rect.w, ending_before_source_rect.h };

    //stage1 �۾� ����
    SDL_Surface* stagetext_surface = IMG_Load("../../Resources/gallery/stage_txt.png");
    stagetext_texture = SDL_CreateTextureFromSurface(g_renderer, stagetext_surface);
    SDL_FreeSurface(stagetext_surface);

    stagetext_source_rect = { 0, 0, stagetext_surface->w, stagetext_surface->h };
    stagetext_destination_rect = { 0, 0, stagetext_source_rect.w, stagetext_source_rect.h };

    //�������� ���ư��� ��ư
    SDL_Surface* back_to_main_unclicked_surface = IMG_Load("../../Resources/gallery/back_to_main.png");
    back_to_main_unclicked_texture = SDL_CreateTextureFromSurface(g_renderer, back_to_main_unclicked_surface);

	SDL_Surface* back_to_main_clicked_surface = IMG_Load("../../Resources/gallery/back_to_main_clicked.png");
	back_to_main_clicked_texture = SDL_CreateTextureFromSurface(g_renderer, back_to_main_clicked_surface);
	SDL_FreeSurface(back_to_main_clicked_surface);

	back_to_main_texture = back_to_main_unclicked_texture;
    back_to_main_source_rect = { 0, 0, back_to_main_unclicked_surface->w, back_to_main_unclicked_surface->h };
    back_to_main_destination_rect = { 620, 560, back_to_main_source_rect.w, back_to_main_source_rect.h };
    SDL_FreeSurface(back_to_main_unclicked_surface);

    if (back_to_main_texture == NULL) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
    }

    gallery_bgm = Mix_LoadMUS("../../Resources/gallery/gallery_background_bgm.mp3");
    click_main = Mix_LoadMUS("../../Resources/Intro/click_gallery.mp3");
    click_sound = Mix_LoadMUS("../../Resources/gallery/gallery_to_end.mp3");

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        std::cerr << "Mix_OpenAudio: " << Mix_GetError() << std::endl;
        return;
    }

}

Gallery::~Gallery()
{
    SDL_DestroyTexture(gallery_bg_texture);

    SDL_DestroyTexture(ending_before11_texture);
	SDL_DestroyTexture(ending_before12_texture);
	SDL_DestroyTexture(ending_before13_texture);
	SDL_DestroyTexture(ending_before21_texture);
	SDL_DestroyTexture(ending_before22_texture);
	SDL_DestroyTexture(ending_before31_texture);
	SDL_DestroyTexture(ending_before32_texture);

	SDL_DestroyTexture(ending_after11_texture);
	SDL_DestroyTexture(ending_after12_texture);
	SDL_DestroyTexture(ending_after13_texture);
	SDL_DestroyTexture(ending_after21_texture);
	SDL_DestroyTexture(ending_after22_texture);
	SDL_DestroyTexture(ending_after31_texture);
	SDL_DestroyTexture(ending_after32_texture);

    SDL_DestroyTexture(ending11_texture);
    SDL_DestroyTexture(ending12_texture);
    SDL_DestroyTexture(ending13_texture);
    SDL_DestroyTexture(ending21_texture);
    SDL_DestroyTexture(ending22_texture);
    SDL_DestroyTexture(ending31_texture);
    SDL_DestroyTexture(ending32_texture);

    SDL_DestroyTexture(frame_texture_);
    SDL_DestroyTexture(stagetext_texture);
    SDL_DestroyTexture(back_to_main_texture);
	SDL_DestroyTexture(back_to_main_unclicked_texture);
	SDL_DestroyTexture(back_to_main_clicked_texture);

    Mix_FreeMusic(gallery_bgm);
    Mix_FreeMusic(click_main);
    Mix_FreeMusic(click_sound);
    Mix_CloseAudio();

}

void Gallery::Update()
{
    // viewedEndings 배열을 확인하여 텍스처를 선택합니다.
    if (viewedEndings[0][0]) {
        ending11_texture = ending_after11_texture;
    }
    else {
        ending11_texture = ending_before11_texture;
    }

	if (viewedEndings[0][1]) {
		ending12_texture = ending_after12_texture;
	}
	else {
		ending12_texture = ending_before12_texture;
	}

	if (viewedEndings[0][2]) {
		ending13_texture = ending_after13_texture;
	}
	else {
		ending13_texture = ending_before13_texture;
	}

	if (viewedEndings[1][0]) {
		ending21_texture = ending_after21_texture;
	}
	else {
		ending21_texture = ending_before21_texture;
	}

	if (viewedEndings[1][1]) {
		ending22_texture = ending_after22_texture;
	}
	else {
		ending22_texture = ending_before22_texture;
	}

	if (viewedEndings[2][0]) {
		ending31_texture = ending_after31_texture;
	}
	else {
		ending31_texture = ending_before31_texture;
	}

	if (viewedEndings[2][1]) {
		ending32_texture = ending_after32_texture;
	}
	else {
		ending32_texture = ending_before32_texture;
	}
}

void Gallery::Render()
{
    SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
    SDL_RenderClear(g_renderer); // clear the renderer to the draw color

    SDL_RenderCopy(g_renderer, gallery_bg_texture, &gallery_bg_source_rect, &gallery_bg_destination_rect);
    SDL_RenderCopy(g_renderer, ending11_texture, &ending_before_source_rect, &ending11_destination_rect);
    SDL_RenderCopy(g_renderer, ending12_texture, &ending_before_source_rect, &ending12_destination_rect);
    SDL_RenderCopy(g_renderer, ending13_texture, &ending_before_source_rect, &ending13_destination_rect);
    SDL_RenderCopy(g_renderer, ending21_texture, &ending_before_source_rect, &ending21_destination_rect);
    SDL_RenderCopy(g_renderer, ending22_texture, &ending_before_source_rect, &ending22_destination_rect);
    SDL_RenderCopy(g_renderer, ending31_texture, &ending_before_source_rect, &ending31_destination_rect);
    SDL_RenderCopy(g_renderer, ending32_texture, &ending_before_source_rect, &ending32_destination_rect);

    SDL_RenderCopy(g_renderer, frame_texture_, &frame_source_rectangle_, &frame11_destination_rect);
    SDL_RenderCopy(g_renderer, frame_texture_, &frame_source_rectangle_, &frame12_destination_rect);
    SDL_RenderCopy(g_renderer, frame_texture_, &frame_source_rectangle_, &frame13_destination_rect);
    SDL_RenderCopy(g_renderer, frame_texture_, &frame_source_rectangle_, &frame21_destination_rect);
    SDL_RenderCopy(g_renderer, frame_texture_, &frame_source_rectangle_, &frame22_destination_rect);
    SDL_RenderCopy(g_renderer, frame_texture_, &frame_source_rectangle_, &frame31_destination_rect);
    SDL_RenderCopy(g_renderer, frame_texture_, &frame_source_rectangle_, &frame32_destination_rect);

    SDL_RenderCopy(g_renderer, stagetext_texture, &stagetext_source_rect, &stagetext_destination_rect);

    SDL_RenderCopy(g_renderer, back_to_main_texture, &back_to_main_source_rect, &back_to_main_destination_rect);


    SDL_RenderPresent(g_renderer);
}

void Gallery::HandleEvents()
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            g_flag_running = false;
            break;
        case SDL_MOUSEMOTION:
        {
            int mouseX = event.motion.x;
            int mouseY = event.motion.y;

            if (mouseX >= back_to_main_destination_rect.x && mouseX <= back_to_main_destination_rect.x + back_to_main_destination_rect.w &&
                mouseY >= back_to_main_destination_rect.y && mouseY <= back_to_main_destination_rect.y + back_to_main_destination_rect.h)
            {
				back_to_main_texture = back_to_main_clicked_texture;
            }
            else
            {
				back_to_main_texture = back_to_main_unclicked_texture;
            }
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                if (event.button.x > back_to_main_destination_rect.x && event.button.x < back_to_main_destination_rect.x + back_to_main_destination_rect.w &&
                    event.button.y > back_to_main_destination_rect.y && event.button.y < back_to_main_destination_rect.y + back_to_main_destination_rect.h)
                {
                    Mix_PlayMusic(click_main, 0);
                    SDL_Delay(1000);
                    g_current_game_phase = PHASE_MAIN_MENU;
                }
                //ending11
                else if (event.button.x > ending11_destination_rect.x && event.button.x < ending11_destination_rect.x + ending11_destination_rect.w &&
                    event.button.y > ending11_destination_rect.y && event.button.y < ending11_destination_rect.y + ending11_destination_rect.h)
                {
                    if (viewedEndings[0][0] == true) {
                        game_result = 1;
                        Mix_PlayMusic(click_sound, 0);
                        SDL_Delay(1000);
                        g_current_game_phase = PHASE_STAGE1_ENDING;
                    }
                }
                //ending12
                else if (event.button.x > ending12_destination_rect.x && event.button.x < ending12_destination_rect.x + ending12_destination_rect.w &&
                    event.button.y > ending12_destination_rect.y && event.button.y < ending12_destination_rect.y + ending12_destination_rect.h)
                {
                    if (viewedEndings[0][1] == true) {
                        game_result = 2;
                        Mix_PlayMusic(click_sound, 0);
                        SDL_Delay(1000);
                        g_current_game_phase = PHASE_STAGE1_ENDING;
                    }
                }
                //ending13
                else if (event.button.x > ending13_destination_rect.x && event.button.x < ending13_destination_rect.x + ending13_destination_rect.w &&
                    event.button.y > ending13_destination_rect.y && event.button.y < ending13_destination_rect.y + ending13_destination_rect.h)
                {
                    if (viewedEndings[0][2] == true) {
                        game_result = 3;
                        Mix_PlayMusic(click_sound, 0);
                        SDL_Delay(1000);
                        g_current_game_phase = PHASE_STAGE1_ENDING;
                    }
                }
                //ending21
                else if (event.button.x > ending21_destination_rect.x && event.button.x < ending21_destination_rect.x + ending21_destination_rect.w &&
                    event.button.y > ending21_destination_rect.y && event.button.y < ending21_destination_rect.y + ending21_destination_rect.h)
                {
                    if (viewedEndings[1][0] == true) {
                        game_result = 2;
                        Mix_PlayMusic(click_sound, 0);
                        SDL_Delay(1000);
                        g_current_game_phase = PHASE_STAGE2_ENDING;
                    }
                }
                //ending22
                else if (event.button.x > ending22_destination_rect.x && event.button.x < ending22_destination_rect.x + ending22_destination_rect.w &&
                    event.button.y > ending22_destination_rect.y && event.button.y < ending22_destination_rect.y + ending22_destination_rect.h)
                {
                    if (viewedEndings[1][1] == true) {
                        game_result = 1;
                        Mix_PlayMusic(click_sound, 0);
                        SDL_Delay(1000);
                        g_current_game_phase = PHASE_STAGE2_ENDING;
                    }
                }
                //ending31
                else if (event.button.x > ending31_destination_rect.x && event.button.x < ending31_destination_rect.x + ending31_destination_rect.w &&
                    event.button.y > ending31_destination_rect.y && event.button.y < ending31_destination_rect.y + ending31_destination_rect.h)
                {
                    if (viewedEndings[2][0] == true) {
                        game_result = 2;
                        Mix_PlayMusic(click_sound, 0);
                        SDL_Delay(1000);
                        g_current_game_phase = PHASE_STAGE3_ENDING;
                    }
                }
                //ending32
                else if (event.button.x > ending32_destination_rect.x && event.button.x < ending32_destination_rect.x + ending32_destination_rect.w &&
                    event.button.y > ending32_destination_rect.y && event.button.y < ending32_destination_rect.y + ending32_destination_rect.h)
                {
                    if (viewedEndings[2][1] == true) {
                        game_result = 1;
                        Mix_PlayMusic(click_sound, 0);
                        SDL_Delay(1000);
                        g_current_game_phase = PHASE_STAGE3_ENDING;
                    }
                }
            }
            break;
        }
        default:
            break;
        }
    }
}

void Gallery::Reset()
{
    back_to_main_texture = back_to_main_unclicked_texture;

    Mix_HaltMusic();
    Mix_HaltChannel(-1);
    Mix_FadeInMusic(gallery_bgm, -1, 2000);
}