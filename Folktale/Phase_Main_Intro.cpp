#pragma once
#include "Game.h"
#include "Phase_Main_Intro.h"

Phase_Main_Intro::Phase_Main_Intro()
{
	// Load the intro image
	SDL_Surface* mainIntroBG_surface = IMG_Load("../../Resources/Intro/Main/Main.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, mainIntroBG_surface);
	SDL_FreeSurface(mainIntroBG_surface);
	if (texture_ == nullptr)
	{
		std::cout << "Failed to load texture: " << SDL_GetError() << std::endl;
	}
	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);
	source_rectangle_ = { 0, 0, source_rectangle_.w, source_rectangle_.h };
	destination_rectangle_ = { 0, 0, 1080, 720 };

	if (TTF_Init() == -1)
	{
		std::cout << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
	}

	// Load font
	font = TTF_OpenFont("../../Resources/PF.ttf", 100);
	// Render text
	SDL_Color textColor = { 255, 255, 255, 255 }; // White color
	SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, "좌클릭", textColor);
	text_texture_ = SDL_CreateTextureFromSurface(g_renderer, textSurface);
	SDL_FreeSurface(textSurface);

	// Set text position
	text_rect_.x = 450; // X position
	text_rect_.y = 300; // Y position
	SDL_QueryTexture(text_texture_, NULL, NULL, &text_rect_.w, &text_rect_.h);

}

Phase_Main_Intro::~Phase_Main_Intro()
{
	SDL_DestroyTexture(texture_);
	SDL_DestroyTexture(text_texture_);
	if (font != nullptr)
		TTF_CloseFont(font);
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
			g_current_game_phase = PHASE_INTRO;
		}
	}
}

void Phase_Main_Intro::Update()
{

}

void Phase_Main_Intro::Render()
{
	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);
	SDL_RenderCopy(g_renderer, text_texture_, NULL, &text_rect_);

	SDL_RenderPresent(g_renderer);
}

void Phase_Main_Intro::Reset()
{

}