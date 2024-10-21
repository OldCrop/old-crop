#pragma once

#include "SDL.h"
#include "STAGE.h"

class MainMenu : public PhaseInterface
{
public:
	MainMenu();
	~MainMenu();
	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();
	virtual void Reset();

private:

	int current_frame;
	int frame_time;
	int frame_delay;
	int total_frame;

	SDL_Texture* select_stage1_texture_;
	SDL_Rect select_stage1_source_rectangle_;
	SDL_Rect select_stage1_destination_rectangle_;

	SDL_Texture* select_stage2_texture_;
	SDL_Rect select_stage2_source_rectangle_;
	SDL_Rect select_stage2_destination_rectangle_;

	SDL_Texture* select_stage3_texture_;
	SDL_Rect select_stage3_source_rectangle_;
	SDL_Rect select_stage3_destination_rectangle_;

	SDL_Texture* explain_to_start_texture_;
	SDL_Rect explain_to_start_source_rectangle_;
	SDL_Rect explain_to_start_destination_rectangle_;

	SDL_Texture* gallery_button_texture_; // the SDL_Texture
	SDL_Texture* exit_button_texture_; // the SDL_Texture

	SDL_Rect gallery_button_source_rectangle_; // the rectangle for source image
	SDL_Rect gallery_button_destination_rectangle_; // for destination

	SDL_Rect exit_button_source_rectangle_; // the rectangle for source image
	SDL_Rect exit_button_destination_rectangle_; // for destination

	SDL_Texture* hard_button_texture;
	SDL_Rect hard_button_dest_rectangle;
	SDL_Rect hard_button_source_rectangle;

	SDL_Texture* hard_button_texture2;
	SDL_Rect hard_button_source_rectangle2;
	SDL_Rect hard_button_dest_rectangle2;

	SDL_Texture* entering_anime_texture_;
	SDL_Rect entering_anime_source_rectangle_;
	SDL_Rect entering_anime_destination_rectangle_;

	Mix_Music* intro_bgm;
	Mix_Music* click_start;
	Mix_Music* click_gallery;
	Mix_Chunk* pause_Sound;

	bool is_entering_anime;
	int selected_stage;
	// 0: poop, 1: snake, 2: rabbit
};


