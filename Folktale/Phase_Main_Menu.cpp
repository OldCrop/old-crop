#include "Game.h"
#include "Phase_Main_Menu.h"

MainMenu::MainMenu()
{
	selected_stage = 1;

    current_frame = 0;
    frame_time = 0;
    frame_delay = 5;
    total_frame = 12;

    is_hard = false;
	is_entering_anime = false;

    // For Texture
	SDL_Surface* select_stage1_surface = IMG_Load("../../Resources/Intro/select_stage1.png");
	select_stage1_texture_ = SDL_CreateTextureFromSurface(g_renderer, select_stage1_surface);
	SDL_FreeSurface(select_stage1_surface);

	SDL_QueryTexture(select_stage1_texture_, NULL, NULL, &select_stage1_source_rectangle_.w, &select_stage1_source_rectangle_.h);
	select_stage1_source_rectangle_ = { 0, 0, select_stage1_source_rectangle_.w, select_stage1_source_rectangle_.h };
	select_stage1_destination_rectangle_ = { 0, 0, select_stage1_source_rectangle_.w, select_stage1_source_rectangle_.h };

	SDL_Surface* select_stage2_surface = IMG_Load("../../Resources/Intro/select_stage2.png");
	select_stage2_texture_ = SDL_CreateTextureFromSurface(g_renderer, select_stage2_surface);
	SDL_FreeSurface(select_stage2_surface);

	SDL_QueryTexture(select_stage2_texture_, NULL, NULL, &select_stage2_source_rectangle_.w, &select_stage2_source_rectangle_.h);
	select_stage2_source_rectangle_ = { 0, 0, select_stage2_source_rectangle_.w, select_stage2_source_rectangle_.h };
	select_stage2_destination_rectangle_ = { 0, 0, select_stage2_source_rectangle_.w, select_stage2_source_rectangle_.h };

	SDL_Surface* select_stage3_surface = IMG_Load("../../Resources/Intro/select_stage3.png");
	select_stage3_texture_ = SDL_CreateTextureFromSurface(g_renderer, select_stage3_surface);
	SDL_FreeSurface(select_stage3_surface);

	SDL_QueryTexture(select_stage3_texture_, NULL, NULL, &select_stage3_source_rectangle_.w, &select_stage3_source_rectangle_.h);
	select_stage3_source_rectangle_ = { 0, 0, select_stage3_source_rectangle_.w, select_stage3_source_rectangle_.h };
	select_stage3_destination_rectangle_ = { 0, 0, select_stage3_source_rectangle_.w, select_stage3_source_rectangle_.h };

	//Explain to Start
	SDL_Surface* explain_to_start_surface = IMG_Load("../../Resources/Intro/MainMenu_enter.png");
	explain_to_start_texture_ = SDL_CreateTextureFromSurface(g_renderer, explain_to_start_surface);
	SDL_FreeSurface(explain_to_start_surface);

	SDL_QueryTexture(explain_to_start_texture_, NULL, NULL, &explain_to_start_source_rectangle_.w, &explain_to_start_source_rectangle_.h);
	explain_to_start_source_rectangle_ = { 0, 0, explain_to_start_source_rectangle_.w, explain_to_start_source_rectangle_.h };
	explain_to_start_destination_rectangle_ = { 0, 0, explain_to_start_source_rectangle_.w, explain_to_start_source_rectangle_.h };

    //Gallery��ư
    SDL_Surface* gallery_button_surface = IMG_Load("../../Resources/Intro/gallery_button.png");
    gallery_button_texture_ = SDL_CreateTextureFromSurface(g_renderer, gallery_button_surface);
    SDL_FreeSurface(gallery_button_surface);

    SDL_QueryTexture(gallery_button_texture_, NULL, NULL, &gallery_button_source_rectangle_.w, &gallery_button_source_rectangle_.h);
    gallery_button_source_rectangle_ = { 0, 0, gallery_button_source_rectangle_.w, gallery_button_source_rectangle_.h };
    gallery_button_destination_rectangle_ = { 10, 10, gallery_button_source_rectangle_.w, gallery_button_source_rectangle_.h };

    //Exit��ư
    SDL_Surface* exit_button_surface = IMG_Load("../../Resources/Intro/exit.png");
    exit_button_texture_ = SDL_CreateTextureFromSurface(g_renderer, exit_button_surface);
    SDL_FreeSurface(exit_button_surface);

    SDL_QueryTexture(exit_button_texture_, NULL, NULL, &exit_button_source_rectangle_.w, &exit_button_source_rectangle_.h);
    exit_button_source_rectangle_ = { 0, 0, exit_button_source_rectangle_.w, exit_button_source_rectangle_.h };
    exit_button_destination_rectangle_ = { 885, 10, exit_button_source_rectangle_.w, exit_button_source_rectangle_.h };

    //Onoff ��ư �߰��ϱ�
    SDL_Surface* hard_button_surface = IMG_Load("../../Resources/intro/hard_false.png");
    hard_button_texture = SDL_CreateTextureFromSurface(g_renderer, hard_button_surface);
    SDL_FreeSurface(hard_button_surface);

    SDL_QueryTexture(hard_button_texture, NULL, NULL, &hard_button_source_rectangle.w, &hard_button_source_rectangle.h);
    hard_button_source_rectangle = { 0, 0, hard_button_source_rectangle.w, hard_button_source_rectangle.h };
    hard_button_dest_rectangle = { 12, 56, hard_button_source_rectangle.w, hard_button_source_rectangle.h };

	SDL_Surface* hard_button_surface2 = IMG_Load("../../Resources/intro/hard_true.png");
	hard_button_texture2 = SDL_CreateTextureFromSurface(g_renderer, hard_button_surface2);
	SDL_FreeSurface(hard_button_surface2);

	SDL_QueryTexture(hard_button_texture2, NULL, NULL, &hard_button_source_rectangle.w, &hard_button_source_rectangle.h);
	hard_button_source_rectangle2 = { 0, 0, hard_button_source_rectangle.w, hard_button_source_rectangle.h };
	hard_button_dest_rectangle2 = { 12, 56, hard_button_source_rectangle.w, hard_button_source_rectangle.h };


    //entering animation
	SDL_Surface* entering_animation_surface = IMG_Load("../../Resources/Intro/EnteringSheet.png");
	entering_anime_texture_ = SDL_CreateTextureFromSurface(g_renderer, entering_animation_surface);
	SDL_FreeSurface(entering_animation_surface);

	SDL_QueryTexture(entering_anime_texture_, NULL, NULL, &entering_anime_source_rectangle_.w, &entering_anime_source_rectangle_.h);
	entering_anime_source_rectangle_ = { 0, 0, entering_anime_source_rectangle_.w / 12, entering_anime_source_rectangle_.h };
	entering_anime_destination_rectangle_ = { 0, 0, entering_anime_source_rectangle_.w, entering_anime_source_rectangle_.h };

    //���� �ε�
	intro_bgm = Mix_LoadMUS("../../Resources/Gallery/gallery_background_bgm.mp3");
    click_start = Mix_LoadMUS("../../Resources/Intro/click_start.mp3");
    click_gallery = Mix_LoadMUS("../../Resources/Intro/click_gallery.mp3");
    pause_Sound = Mix_LoadWAV("../../Resources/Intro/pauseSound.wav");
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        std::cerr << "Mix_OpenAudio: " << Mix_GetError() << std::endl;
        return;
    }
}

MainMenu::~MainMenu()
{
    SDL_DestroyTexture(select_stage1_texture_);
	SDL_DestroyTexture(select_stage2_texture_);
	SDL_DestroyTexture(select_stage3_texture_);
	SDL_DestroyTexture(explain_to_start_texture_);
	SDL_DestroyTexture(entering_anime_texture_);

    SDL_DestroyTexture(gallery_button_texture_);
    SDL_DestroyTexture(exit_button_texture_);
	SDL_DestroyTexture(hard_button_texture);
	SDL_DestroyTexture(hard_button_texture2);

	Mix_FreeMusic(intro_bgm);
    Mix_FreeMusic(click_start);
    Mix_FreeMusic(click_gallery);
    Mix_FreeChunk(pause_Sound);

}

void MainMenu::Update()
{
	if (viewedEndings[1][1])
	{
        selected_stage = 2;
	}
    if (viewedEndings[2][1])
	{
		selected_stage = 3;
	}

    if (is_entering_anime) {
        frame_time++;
        if (frame_time >= frame_delay) {
            frame_time = 0;
            current_frame++;
            if (current_frame >= total_frame) {
                is_entering_anime = false;
                // Transition to the selected stage
                if (selected_stage == 1) {
					Mix_PlayChannel(-1, pause_Sound, 0);
                    g_current_game_phase = PHASE_STAGE1_INTRO;
                }
                else if (selected_stage == 2) {
                    Mix_PlayChannel(-1, pause_Sound, 0);
                    g_current_game_phase = PHASE_STAGE2_INTRO;
                }
                else if (selected_stage == 3) {
                    Mix_PlayChannel(-1, pause_Sound, 0);
                    g_current_game_phase = PHASE_STAGE3_INTRO;
                }
            }
            entering_anime_source_rectangle_.x = current_frame * entering_anime_source_rectangle_.w;
        }
    }
}


void MainMenu::Render()
{
    SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
    SDL_RenderClear(g_renderer); // clear the renderer to the draw color

    //������ ���������� ���� �׵θ��� �׷���
    if (selected_stage==2)
    {
        SDL_RenderCopy(g_renderer, select_stage2_texture_, &select_stage2_source_rectangle_, &select_stage2_destination_rectangle_);
	}
	else if (selected_stage==3)
	{
        SDL_RenderCopy(g_renderer, select_stage3_texture_, &select_stage3_source_rectangle_, &select_stage3_destination_rectangle_);
	}
    else
    {
        SDL_RenderCopy(g_renderer, select_stage1_texture_, &select_stage1_source_rectangle_, &select_stage1_destination_rectangle_);
    }

    SDL_RenderCopy(g_renderer, gallery_button_texture_, &gallery_button_source_rectangle_, &gallery_button_destination_rectangle_);
    SDL_RenderCopy(g_renderer, exit_button_texture_, &exit_button_source_rectangle_, &exit_button_destination_rectangle_);

    //hard btn
    if (is_hard == true)
    {
		SDL_RenderCopy(g_renderer, hard_button_texture2, &hard_button_source_rectangle2, &hard_button_dest_rectangle2);
	}
    else
    {
        SDL_RenderCopy(g_renderer, hard_button_texture, &hard_button_source_rectangle, &hard_button_dest_rectangle);
    }

	SDL_RenderCopy(g_renderer, explain_to_start_texture_, &explain_to_start_source_rectangle_, &explain_to_start_destination_rectangle_);

    if (is_entering_anime) {
        SDL_RenderCopy(g_renderer, entering_anime_texture_, &entering_anime_source_rectangle_, &entering_anime_destination_rectangle_);
    }

    SDL_RenderPresent(g_renderer); // draw to the screen
}



void MainMenu::HandleEvents()
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            g_flag_running = false;
            break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_RETURN)
            {
                Mix_PlayMusic(click_start, 0);
                is_entering_anime = true;
                current_frame = 0;
                frame_time = 0;
            }
			if (event.key.keysym.sym == SDLK_1)
			{
                viewedEndings[1][1] = false;
				viewedEndings[2][1] = false;
				selected_stage = 1;
			}
			if (event.key.keysym.sym == SDLK_2)
			{
				viewedEndings[1][1] = true;
                viewedEndings[2][1] = false;
			}
			if (event.key.keysym.sym == SDLK_3)
			{
                viewedEndings[2][1] = true;
			}
            break;
        case SDL_MOUSEBUTTONDOWN:
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                //Gallery��ư�� ������ Gallery�� �Ѿ
                if (event.button.x > gallery_button_destination_rectangle_.x && event.button.x < gallery_button_destination_rectangle_.x + gallery_button_source_rectangle_.w &&
                    event.button.y > gallery_button_destination_rectangle_.y && event.button.y < gallery_button_destination_rectangle_.y + gallery_button_source_rectangle_.h)
                {
                    // Transition to the gallery phase
                        std::cout << "Gallery button clicked" << std::endl;
                    // Assuming there's a method to change the phase

                    Mix_PlayMusic(click_gallery, 0);
                    SDL_Delay(1000);
                    g_current_game_phase = PHASE_GALLERY;
                }

                //Exit��ư�� ������ ������ �����
                else if (event.button.x > exit_button_destination_rectangle_.x && event.button.x < exit_button_destination_rectangle_.x + exit_button_source_rectangle_.w &&
                    event.button.y > exit_button_destination_rectangle_.y && event.button.y < exit_button_destination_rectangle_.y + exit_button_source_rectangle_.h)
                {
					g_current_game_phase = PHASE_MAIN_INTRO;
                }
                // Hard 버튼 클릭 시 is_hard 변수 설정
                if (x >= hard_button_dest_rectangle.x && x <= hard_button_dest_rectangle.x + hard_button_dest_rectangle.w &&
                    y >= hard_button_dest_rectangle.y && y <= hard_button_dest_rectangle.y + hard_button_dest_rectangle.h) {
                    is_hard = !is_hard;
                    std::cout << "is_hard toggled to " << is_hard << std::endl;
                }
            }

        case SDL_MOUSEMOTION:
            //gallery��ư ���� ���콺�� �ö󰡸� ���� ����
            if (event.motion.x > gallery_button_destination_rectangle_.x && event.motion.x < gallery_button_destination_rectangle_.x + gallery_button_source_rectangle_.w &&
                event.motion.y > gallery_button_destination_rectangle_.y && event.motion.y < gallery_button_destination_rectangle_.y + gallery_button_source_rectangle_.h)
            {
                SDL_SetTextureColorMod(gallery_button_texture_, 128, 128, 128);
            }
            else
            {
                SDL_SetTextureColorMod(gallery_button_texture_, 255, 255, 255);
            }
            //exit��ư ���� ���콺�� �ö󰡸� ���� ����
            if (event.motion.x > exit_button_destination_rectangle_.x && event.motion.x < exit_button_destination_rectangle_.x + exit_button_source_rectangle_.w &&
                event.motion.y > exit_button_destination_rectangle_.y && event.motion.y < exit_button_destination_rectangle_.y + exit_button_source_rectangle_.h)
            {
                SDL_SetTextureColorMod(exit_button_texture_, 128, 128, 128);
            }
            else
            {
                SDL_SetTextureColorMod(exit_button_texture_, 255, 255, 255);
            }
        default:
            break;
        }
    }
}

void MainMenu::Reset()
{
    if (is_hard) {
		std::cout << "Hard mode is on" << std::endl;
    }else {
        std::cout << "Hard mode is off" << std::endl;
    }

	is_entering_anime = false;

    //���� �ʱ�ȭ
    Mix_HaltMusic();
    Mix_HaltChannel(-1);
    Mix_VolumeMusic(64);
	Mix_FadeInMusic(intro_bgm, -1, 2000);
}