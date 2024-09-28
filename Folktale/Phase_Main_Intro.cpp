#pragma once
#include "Game.h"
#include "Phase_Main_Intro.h"

Phase_Main_Intro::Phase_Main_Intro() : click_count_(0), last_click_time_(0), show_face_and_expression_(false), show_start_time_(0), is_first_click_(true)
{
	// Load the intro image
	SDL_Surface* mainIntroBG_surface = IMG_Load("../../Resources/Intro/Main/Main_mod.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, mainIntroBG_surface);
	SDL_FreeSurface(mainIntroBG_surface);
	if (texture_ == nullptr)
	{
		std::cout << "Failed to load texture: " << SDL_GetError() << std::endl;
	}
	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);
	source_rectangle_ = { 0, 0, source_rectangle_.w, source_rectangle_.h };
	destination_rectangle_ = { 0, 0, 1080, 720 };

	// Load the face image
	SDL_Surface* face_surface = IMG_Load("../../Resources/Intro/Main/Main_face.png");
	face_texture_ = SDL_CreateTextureFromSurface(g_renderer, face_surface);
	SDL_FreeSurface(face_surface);
	if (face_texture_ == nullptr)
	{
		std::cout << "Failed to load texture: " << SDL_GetError() << std::endl;
	}
	SDL_QueryTexture(face_texture_, NULL, NULL, &face_rect_.w, &face_rect_.h);
	face_rect_ = { 0, 0, face_rect_.w, face_rect_.h };

	// Load the expression image
	SDL_Surface* expression_surface = IMG_Load("../../Resources/Intro/Main/Main_exp.png");
	expression_texture_ = SDL_CreateTextureFromSurface(g_renderer, expression_surface);
	SDL_FreeSurface(expression_surface);
	if (expression_texture_ == nullptr)
	{
		std::cout << "Failed to load texture: " << SDL_GetError() << std::endl;
	}
	SDL_QueryTexture(expression_texture_, NULL, NULL, &expression_rect_.w, &expression_rect_.h);
	expression_rect_ = { 0, 0, expression_rect_.w, expression_rect_.h };

}

Phase_Main_Intro::~Phase_Main_Intro()
{
	SDL_DestroyTexture(texture_);
	SDL_DestroyTexture(face_texture_);
	SDL_DestroyTexture(expression_texture_);
	TTF_Quit();
}

void Phase_Main_Intro::HandleEvents()
{
	SDL_Event event;
	//if you click the mouse button, switch to the next phase = PHASE_INTRO
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			// If the mouse left button is pressed at the text position.
			Uint32 current_time = SDL_GetTicks();
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				if (event.button.x >= 301 && event.button.x <= 301 + 77 &&
					event.button.y >= 232 && event.button.y <= 232 + 72)
				{
					if (current_time - last_click_time_ < 500) // 500ms 이내에 두 번 클릭
					{
						click_count_++;
					}
					else
					{
						click_count_ = 1;
					}
					last_click_time_ = current_time;

					if (click_count_ == 2)
					{
						show_face_and_expression_ = true;
						show_start_time_ = current_time; // 타이머 초기화
					}
				}
				if (event.button.x >= 410 && event.button.x <= 410 + 252 &&
					event.button.y >= 444 && event.button.y <= 444 + 67)
				{
					if (is_first_click_)
					{
						g_current_game_phase = PHASE_INTRO;
						is_first_click_ = false; // 첫 클릭 이후로 플래그 변경
					}
					else
					{
						g_current_game_phase = PHASE_MAIN_MENU;
					}
				}
				if (event.button.x >= 475 && event.button.x <= 475 + 127 &&
					event.button.y >= 561 && event.button.y <= 561 + 62)
				{
					g_flag_running = false;
				}
			}
			//g_current_game_phase = PHASE_INTRO;
		}
		else if (event.type == SDL_QUIT)
		{
			g_flag_running = false;
		}
	}
}

void Phase_Main_Intro::Update()
{
	if (show_face_and_expression_)
	{
		Uint32 current_time = SDL_GetTicks();
		if (current_time - show_start_time_ > 2000) // 2초 후에 이미지 숨기기
		{
			show_face_and_expression_ = false;
		}
	}
}

void Phase_Main_Intro::Render()
{
	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);
	if (show_face_and_expression_)
	{
		SDL_RenderCopy(g_renderer, face_texture_, NULL, &face_rect_);
		SDL_RenderCopy(g_renderer, expression_texture_, NULL, &expression_rect_);
	}
	SDL_RenderPresent(g_renderer);
}

void Phase_Main_Intro::Reset()
{
	Mix_HaltMusic();
	Mix_HaltChannel(-1);
}