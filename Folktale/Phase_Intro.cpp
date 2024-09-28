#include "Game.h"
#include "Phase_Main_Intro.h"

Intro::Intro()
{
	x = 30;
	speed = 0;

	// Load the intro image
	SDL_Surface* mainIntroBG_surface = IMG_Load("../../Resources/Intro/Main/TreeRoad.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, mainIntroBG_surface);
	SDL_FreeSurface(mainIntroBG_surface);
	if (texture_ == nullptr)
	{
		std::cout << "Failed to load texture: " << SDL_GetError() << std::endl;
	}
	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);
	source_rectangle_ = { 0, 0, source_rectangle_.w, source_rectangle_.h };
	destination_rectangle_ = { 0, 0, 1080, 720 };

	// Load the human image
	SDL_Surface* human_surface = IMG_Load("../../Resources/Intro/Main/human.png");
	human_texture_ = SDL_CreateTextureFromSurface(g_renderer, human_surface);
	SDL_FreeSurface(human_surface);
	if (human_texture_ == nullptr)
	{
		std::cout << "Failed to load texture: " << SDL_GetError() << std::endl;
	}
	SDL_QueryTexture(human_texture_, NULL, NULL, &human_source_rectangle_.w, &human_source_rectangle_.h);
	human_source_rectangle_ = { 0, 0, human_source_rectangle_.w, human_source_rectangle_.h };
	human_destination = { x, 295, human_source_rectangle_.w, human_source_rectangle_.h };

	// Load the book image
	SDL_Surface* book_surface = IMG_Load("../../Resources/Intro/Main/book.png");
	book_texture_ = SDL_CreateTextureFromSurface(g_renderer, book_surface);
	SDL_FreeSurface(book_surface);
	if (book_texture_ == nullptr)
	{
		std::cout << "Failed to load texture: " << SDL_GetError() << std::endl;
	}
	SDL_QueryTexture(book_texture_, NULL, NULL, &book_source_rectangle_.w, &book_source_rectangle_.h);
	book_source_rectangle_ = { 0, 0, book_source_rectangle_.w, book_source_rectangle_.h };
	book_destination = { 935, 295, book_source_rectangle_.w, book_source_rectangle_.h };

	// Load font
	font = TTF_OpenFont("../../Resources/PF.ttf", 30);
	// Render text
	SDL_Color textColor = { 255, 255, 255, 255 }; // White color
	SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, "방향키 좌우", textColor);
	text_texture_ = SDL_CreateTextureFromSurface(g_renderer, textSurface);
	SDL_FreeSurface(textSurface);

	// Set text position
	text_rect_.x = 450; // X position
	text_rect_.y = 300; // Y position
	SDL_QueryTexture(text_texture_, NULL, NULL, &text_rect_.w, &text_rect_.h);

	// Load the background music
	bgm = Mix_LoadMUS("../../Resources/Intro/Main/treeRoad.mp3");
	if (bgm == nullptr)
	{
		std::cout << "Failed to load music: " << Mix_GetError() << std::endl;
	}
	
}

Intro::~Intro()
{
	SDL_DestroyTexture(texture_);
	SDL_DestroyTexture(human_texture_);
	SDL_DestroyTexture(book_texture_);
	SDL_DestroyTexture(text_texture_);
	Mix_FreeMusic(bgm);
	if (font != nullptr)
		TTF_CloseFont(font);
	TTF_Quit();
}

void Intro::HandleEvents()
{
	SDL_Event event;
	//if you click the mouse button, switch to the next phase = PHASE_INTRO
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			g_current_game_phase = PHASE_INTRO;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_LEFT:
				//x -= 10;
				speed = -5;
				break;
			case SDLK_RIGHT:
				//x += 10;
				speed = 5;
				break;
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_LEFT:
			case SDLK_RIGHT:
				speed = 0;
				break;
			}
			break;
		}
	}
}

void Intro::Update()
{
	x += speed;
	// human_destination의 x 좌표를 업데이트
	human_destination.x = x;
	// human_destination meet the book_destination -> change the phase
	if (human_destination.x + human_destination.w - 50 >= book_destination.x)
	{
		SDL_Delay(1000);
		g_current_game_phase = PHASE_MAIN_MENU;
	}
}

void Intro::Render()
{
	SDL_RenderClear(g_renderer); // 렌더러를 초기화
	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);
	SDL_RenderCopy(g_renderer, human_texture_, &human_source_rectangle_, &human_destination);
	SDL_RenderCopy(g_renderer, book_texture_, &book_source_rectangle_, &book_destination);
	SDL_RenderCopy(g_renderer, text_texture_, NULL, &text_rect_);
	SDL_RenderPresent(g_renderer); // 렌더러에 그려진 내용을 화면에 출력
}

void Intro::Reset()
{
	x = 30;
	speed = 0;

	Mix_HaltMusic();
	Mix_HaltChannel(-1);
	Mix_VolumeMusic(16);
	Mix_FadeInMusic(bgm, -1, 3000);
}