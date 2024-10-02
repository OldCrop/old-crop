#pragma once
#ifndef PHASE_GALLERY_H
#define PHASE_GALLERY_H

#include "Game.h"

class Gallery : public PhaseInterface
{
public:
    Gallery();
    ~Gallery();
    virtual void HandleEvents();
    virtual void Update();
    virtual void Render();
    virtual void Reset();


private:
    SDL_Texture* gallery_bg_texture;
    SDL_Rect gallery_bg_source_rect;
    SDL_Rect gallery_bg_destination_rect;

    SDL_Texture* ending_before11_texture;
	SDL_Texture* ending_before12_texture;
	SDL_Texture* ending_before13_texture;
	SDL_Texture* ending_before21_texture;
	SDL_Texture* ending_before22_texture;
	SDL_Texture* ending_before31_texture;
	SDL_Texture* ending_before32_texture;

	SDL_Texture* ending_after11_texture;
	SDL_Texture* ending_after12_texture;
	SDL_Texture* ending_after13_texture;
	SDL_Texture* ending_after21_texture;
	SDL_Texture* ending_after22_texture;
	SDL_Texture* ending_after31_texture;
	SDL_Texture* ending_after32_texture;

    SDL_Texture* ending11_texture;
    SDL_Texture* ending12_texture;
    SDL_Texture* ending13_texture;
    SDL_Texture* ending21_texture;
    SDL_Texture* ending22_texture;
    SDL_Texture* ending31_texture;
    SDL_Texture* ending32_texture;

	SDL_Rect ending_before11_destination_rect;
	SDL_Rect ending_before12_destination_rect;
	SDL_Rect ending_before13_destination_rect;
	SDL_Rect ending_before21_destination_rect;
	SDL_Rect ending_before22_destination_rect;
	SDL_Rect ending_before31_destination_rect;
	SDL_Rect ending_before32_destination_rect;

    SDL_Rect ending_before_source_rect;
    SDL_Rect ending11_source_rect;
    SDL_Rect ending11_destination_rect;
    SDL_Rect ending12_source_rect;
    SDL_Rect ending12_destination_rect;
    SDL_Rect ending13_source_rect;
    SDL_Rect ending13_destination_rect;
    SDL_Rect ending21_source_rect;
    SDL_Rect ending21_destination_rect;
    SDL_Rect ending22_source_rect;
    SDL_Rect ending22_destination_rect;
    SDL_Rect ending31_source_rect;
    SDL_Rect ending31_destination_rect;
    SDL_Rect ending32_source_rect;
    SDL_Rect ending32_destination_rect;

    SDL_Texture* frame_texture_;
    SDL_Rect frame_source_rectangle_;
    SDL_Rect frame11_destination_rect;
    SDL_Rect frame12_destination_rect;
    SDL_Rect frame13_destination_rect;
    SDL_Rect frame21_destination_rect;
    SDL_Rect frame22_destination_rect;
    SDL_Rect frame31_destination_rect;
    SDL_Rect frame32_destination_rect;

    SDL_Texture* stagetext_texture;
    SDL_Rect stagetext_source_rect;
    SDL_Rect stagetext_destination_rect;

    SDL_Texture* back_to_main_texture;
	SDL_Texture* back_to_main_unclicked_texture;
    SDL_Texture* back_to_main_clicked_texture;
    SDL_Rect back_to_main_source_rect;
    SDL_Rect back_to_main_destination_rect;

    Mix_Music* gallery_bgm;
    Mix_Music* click_sound;
    Mix_Music* click_main;

};

#endif // PHASE_GALLERY_H