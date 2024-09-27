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
	
	SDL_Texture* text_texture_;
	SDL_Rect text_rect_;
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

	int x;
	int speed;
	

};