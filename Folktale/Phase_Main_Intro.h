#pragma once

#include "SDL.h"
#include "STAGE.h"



class Phase_Main_Intro : public PhaseInterface
{
public:
	Phase_Main_Intro();
	~Phase_Main_Intro();
	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();
	virtual void Reset();

private:
	SDL_Texture* texture_; // the SDL_Texture
	SDL_Rect source_rectangle_; // the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination
	
	SDL_Texture* face_texture_;
	SDL_Rect face_rect_;

	SDL_Texture* expression_texture_;
	SDL_Rect expression_rect_;

	Mix_Music* bgm;

	//SDL_Texture* text_texture_;
	//SDL_Rect text_rect_;

	// 더블 클릭 감지 변수
	int click_count_;
	Uint32 last_click_time_;
	bool show_face_and_expression_;
	Uint32 show_start_time_; // 이미지를 보여주기 시작한 시간

	//게임 처음 실행 여부
	bool is_first_click_;
};

class Intro : public PhaseInterface
{
public:
	Intro();
	~Intro();
	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();
	virtual void Reset();

private:
	SDL_Texture* texture_; // the SDL_Texture
	SDL_Rect source_rectangle_; // the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination

	SDL_Texture* text_texture_;
	SDL_Rect text_rect_;

	SDL_Texture* human_texture_;
	SDL_Rect human_source_rectangle_;
	SDL_Rect human_destination;

	SDL_Texture* book_texture_;
	SDL_Rect book_source_rectangle_;
	SDL_Rect book_destination;

	Mix_Music* bgm;

	int x;
	int speed;
	

};