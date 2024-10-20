#include "Game.h"
#include "Phase_Main_Intro.h"

Intro::Intro()
{
	x = 30;
	speed = 0;
	current_frame = 0;
	current_frame_book = 0;
	frame_time = 0;
	frame_time_book = 0;
	frame_delay = 10;
	frame_delay_book = 20;
	total_frame = 4;
	moving_left = false;

	is_touching_book = false;
	bookAni_current_frame = 0;
	bookAni_frame_time = 0;
	bookAni_frame_delay = 3;
	bookAni_total_frame = 8;

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
	SDL_Surface* human_left_surface = IMG_Load("../../Resources/Intro/Main/HumanSheet_left.png");
	human_left_surface = IMG_Load("../../Resources/Intro/Main/HumanSheet_left.png");
	human_left_texture_ = SDL_CreateTextureFromSurface(g_renderer, human_left_surface);
	SDL_FreeSurface(human_left_surface);
	if (human_left_texture_ == nullptr)
	{
		std::cout << "Failed to load texture: " << SDL_GetError() << std::endl;
	}
	SDL_QueryTexture(human_left_texture_, NULL, NULL, &human_source_rectangle_.w, &human_source_rectangle_.h);
	human_source_rectangle_ = { 0, 0, human_source_rectangle_.w / 4, human_source_rectangle_.h };
	human_destination = { x, 300, human_source_rectangle_.w, human_source_rectangle_.h };
	
	SDL_Surface* human_right_surface = IMG_Load("../../Resources/Intro/Main/HumanSheet_right.png");
	human_right_surface = IMG_Load("../../Resources/Intro/Main/HumanSheet_right.png");
	human_right_texture_ = SDL_CreateTextureFromSurface(g_renderer, human_right_surface);
	SDL_FreeSurface(human_right_surface);
	if (human_right_texture_ == nullptr)
	{
		std::cout << "Failed to load texture: " << SDL_GetError() << std::endl;
	}
	SDL_QueryTexture(human_right_texture_, NULL, NULL, &human_source_rectangle_.w, &human_source_rectangle_.h);
	human_source_rectangle_ = { 0, 0, human_source_rectangle_.w / 4, human_source_rectangle_.h };
	human_destination = { x, 300, human_source_rectangle_.w, human_source_rectangle_.h };

	// Load the book image
	SDL_Surface* book_surface = IMG_Load("../../Resources/Intro/Main/BookSheet.png");
	book_texture_ = SDL_CreateTextureFromSurface(g_renderer, book_surface);
	SDL_FreeSurface(book_surface);
	if (book_texture_ == nullptr)
	{
		std::cout << "Failed to load texture: " << SDL_GetError() << std::endl;
	}

	SDL_Surface* textBox = IMG_Load("../../Resources/Intro/Main/TextBox.png");
	textBox_texture_ = SDL_CreateTextureFromSurface(g_renderer, textBox);
	SDL_FreeSurface(textBox);
	if (textBox_texture_ == nullptr)
	{
		std::cout << "Failed to load texture: " << SDL_GetError() << std::endl;
	}
	SDL_QueryTexture(textBox_texture_, NULL, NULL, &textBox_rect_.w, &textBox_rect_.h);
	textBox_rect_ = { 0, 0, textBox_rect_.w, textBox_rect_.h };
	textBox_destination = { 0, 0, textBox_rect_.w, textBox_rect_.h };

	SDL_QueryTexture(book_texture_, NULL, NULL, &book_source_rectangle_.w, &book_source_rectangle_.h);
	book_source_rectangle_ = { 0, 0, book_source_rectangle_.w / 4, book_source_rectangle_.h };
	book_destination = { 935, 295, book_source_rectangle_.w / 2, book_source_rectangle_.h / 2 };

	//Load Book Animation Image
	SDL_Surface* book_animation_surface = IMG_Load("../../Resources/Intro/Main/BookAnimeSheet.png");
	book_animation_texture_ = SDL_CreateTextureFromSurface(g_renderer, book_animation_surface);
	SDL_FreeSurface(book_animation_surface);
	if (book_animation_texture_ == nullptr)
	{
		std::cout << "Failed to load texture: " << SDL_GetError() << std::endl;
	}
	SDL_QueryTexture(book_animation_texture_, NULL, NULL, &book_animation_source_rectangle_.w, &book_animation_source_rectangle_.h);
	book_animation_source_rectangle_ = { 0, 0, book_animation_source_rectangle_.w / 8, book_animation_source_rectangle_.h };
	book_animation_destination = { 0, 0, book_animation_source_rectangle_.w, book_animation_source_rectangle_.h };


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
	
	//Load the book flipping sound
	book_sound = Mix_LoadWAV("../../Resources/Intro/Main/Sound_02.wav");
	if (book_sound == nullptr)
	{
		std::cout << "Failed to load music: " << Mix_GetError() << std::endl;
	}

}

Intro::~Intro()
{
	SDL_DestroyTexture(texture_);
	SDL_DestroyTexture(human_left_texture_);
	SDL_DestroyTexture(human_right_texture_);
	SDL_DestroyTexture(book_texture_);
	SDL_DestroyTexture(book_animation_texture_);
	SDL_DestroyTexture(text_texture_);
	Mix_FreeMusic(bgm);
	Mix_FreeChunk(book_sound);
	if (font != nullptr)
		TTF_CloseFont(font);
	TTF_Quit();
}

void Intro::HandleEvents()
{
	SDL_Event event;
	//if you click the mouse button, switch to the next phase = PHASE_INTRO
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			//g_current_game_phase = PHASE_INTRO;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_LEFT:
				//x -= 10;
				speed = -5;
				moving_left = true;
				break;
			case SDLK_RIGHT:
				//x += 10;
				speed = 5;
				moving_left = false;
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
	static int bookAni_repeat_count = 0;

	if (is_touching_book)
	{
		Mix_PlayChannel(-1, book_sound, 0);
		bookAni_frame_time += 1; // Increment frame time (you may want to use SDL_GetTicks() for more accurate timing)
		if (bookAni_frame_time >= bookAni_frame_delay)
		{
			bookAni_frame_time = 0;
			bookAni_current_frame = (bookAni_current_frame + 1) % bookAni_total_frame;
			book_animation_source_rectangle_.x = bookAni_current_frame * book_animation_source_rectangle_.w;

			// Check if the animation has completed one full cycle
			if (bookAni_current_frame == 0)
			{
				bookAni_repeat_count++;
			}

			// Transition to the main menu after 3 repeats
			if (bookAni_repeat_count >= 3)
			{
				g_current_game_phase = PHASE_MAIN_MENU;
			}
		}
	}
	else {
		x += speed;
		human_destination.x = x;

		// Update frame time and current frame only if speed is not zero
		if (speed != 0)
		{
			frame_time += 1; // Increment frame time (you may want to use SDL_GetTicks() for more accurate timing)
			if (frame_time >= frame_delay)
			{
				frame_time = 0;
				current_frame = (current_frame + 1) % total_frame;
			}

			// Update the source rectangle to show the current frame
			human_source_rectangle_.x = current_frame * human_source_rectangle_.w;
		}
		else
		{
			current_frame = 0;
			human_source_rectangle_.x = current_frame * human_source_rectangle_.w;
		}

		// Update book animation frame time and current frame
		frame_time_book += 1; // Increment frame time (you may want to use SDL_GetTicks() for more accurate timing)
		if (frame_time_book >= frame_delay_book)
		{
			if (current_frame_book == 3)
			{
				frame_delay_book = 30;
			}
			else {
				frame_delay_book = 20;
			}

			frame_time_book = 0;
			current_frame_book = (current_frame_book + 1) % 4;
			book_source_rectangle_.x = current_frame_book * book_source_rectangle_.w;
		}

		// Change the phase if the human meets the book
		if (human_destination.x + human_destination.w - 50 >= book_destination.x)
		{
			Mix_FadeOutMusic(2000);
			SDL_Delay(2500);
			is_touching_book = true;
		}
	}
}

void Intro::Render()
{
	SDL_RenderClear(g_renderer); // 렌더러를 초기화
	
	if (is_touching_book)
	{
		SDL_RenderCopy(g_renderer, book_animation_texture_, &book_animation_source_rectangle_, &book_animation_destination);
	}
	else {
		SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);
		SDL_RenderCopy(g_renderer, text_texture_, NULL, &text_rect_);
		SDL_RenderCopy(g_renderer, book_texture_, &book_source_rectangle_, &book_destination);
		if (moving_left)
		{
			SDL_RenderCopy(g_renderer, human_left_texture_, &human_source_rectangle_, &human_destination);
		}
		else
		{
			SDL_RenderCopy(g_renderer, human_right_texture_, &human_source_rectangle_, &human_destination);
		}
	}
	SDL_RenderPresent(g_renderer); // 렌더러에 그려진 내용을 화면에 출력
}

void Intro::Reset()
{
	x = 30;
	speed = 0;

	Mix_HaltMusic();
	Mix_HaltChannel(-1);
	Mix_VolumeMusic(8);
	Mix_FadeInMusic(bgm, -1, 3000);
}