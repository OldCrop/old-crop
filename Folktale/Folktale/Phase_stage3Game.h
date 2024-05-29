#pragma once
#include "Creature_stage3.h"
#include "STAGE3.h"


class Stage3 : public PhaseInterface
{
private:
    Bell* bell;
    Magpie* magpie;
    Snake* snake;
	list<Bomb*> bombList;
	
	//방향키 조작 변수들
	bool f_list[4];
	int f_state;//현재 눌린 키 정보
	bool stop;//정지 정보

	//승패 확인 변수
	SDL_RendererFlip flip;

    int lastSpeedUpTime;
    int stage3_startTime;
    int lastBombTime;

    //아무키나 누르면 시작
    int stage3_status; //0이면 키 대기 상태, 1이면 게임 중, 2면 게임 일시정지
    int alpha;

public:
	Stage3();
	~Stage3();

	void HandleEvents();
	void Update();
	void Render();
	void Reset();


private:
	//종 텍스쳐 
	SDL_Texture* bell_texture; // the SDL_Texture 
	SDL_Rect bell_destination_rect; // for destination
	//까치 텍스쳐
	SDL_Texture* magpie_texture; // the SDL_Texture 
	SDL_Rect magpie_destination_rect; // for destination
	//구렁이 텍스쳐
	SDL_Texture* snakeHead_texture; // the SDL_Texture 
	SDL_Texture* snakeBody_texture;
	SDL_Texture* snakeTail_texture;
	SDL_Rect snake_destination_rect; // for destination

	//배경 텍스쳐
	SDL_Texture* bg_texture; // the SDL_Texture 
	SDL_Rect bg_destination_rect; // for destination
    SDL_Texture* red_texture; // the SDL_Texture 

	//폭탄 텍스쳐
	SDL_Texture* bombAfter_texture;
	SDL_Rect bomb_source_rect; // for destination
	SDL_Rect bomb_destination_rect;

	//하트 텍스쳐
	SDL_Texture* heartZero_texture; // the SDL_Texture 
	SDL_Texture* heartHalf_texture; // the SDL_Texture 
	SDL_Texture* heartOne_texture; // the SDL_Texture 
	SDL_Rect heart_destination_rect; // for destination

    //음향 
    Mix_Music* background_music;
    Mix_Chunk* bell_sound;
    Mix_Chunk* hit_sound;

};