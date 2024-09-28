#pragma once
#include "Creature_stage3.h"
#include "STAGE.h"


class Stage3 : public PhaseInterface
{
private:
    Bell* bell;
    Magpie* magpie;
    Snake* snake;
    list<Bomb*> bombList;
    int magpie_init_health;

    //����Ű ���� ������
    list<int> key_pushed;//���� Ű ���� ����
    int f_state;//���� ���� Ű ����
    bool stop;//���� ����

    //���� Ȯ�� ����
    SDL_RendererFlip flip;

    int lastSpeedUpTime;
    int stage3_startTime;
    int lastBombTime;
    Uint32 pauseStartTime;
    Uint32 totalPauseTime;
    Uint32 totalPauseTime_2;

    //�ƹ�Ű�� ������ ����
    int stage3_status; //0�̸� Ű ��� ����, 1�̸� ���� ��, 2�� ���� �Ͻ�����
    int alpha;

public:
    Stage3();
    ~Stage3();

    void HandleEvents();
    void Update();
    void Render();
    void Reset();

    void UpdateScoreTexture();




private:
    //�� �ؽ��� 
    SDL_Texture* bell_texture; // the SDL_Texture 
    SDL_Rect bell_destination_rect; // for destination
    //��ġ �ؽ���
    SDL_Texture* magpie_texture; // the SDL_Texture 
    SDL_Rect magpie_destination_rect; // for destination
    //������ �ؽ���
    SDL_Texture* snakeHead_texture; // the SDL_Texture 
    SDL_Texture* snakeBody_texture;
    SDL_Texture* snakeTail_texture;
    SDL_Rect snake_destination_rect; // for destination

    //��� �ؽ���
    SDL_Texture* bg_texture; // the SDL_Texture 
    SDL_Rect bg_destination_rect; // for destination
    SDL_Texture* red_texture; // the SDL_Texture 
    SDL_Texture* wait_texture; // the SDL_Texture 

    //��ź �ؽ���
    SDL_Texture* bombAfter_texture;
    SDL_Rect bomb_source_rect; // for destination
    SDL_Rect bomb_destination_rect;

    //��Ʈ �ؽ���
    SDL_Texture* heartZero_texture; // the SDL_Texture 
    SDL_Texture* heartHalf_texture; // the SDL_Texture 
    SDL_Texture* heartOne_texture; // the SDL_Texture 
    SDL_Rect heart_destination_rect; // for destination

    //��ư �ؽ���
    SDL_Texture* button_main; // the SDL_Texture 
    SDL_Texture* button_continue; // the SDL_Texture 
    SDL_Rect continue_destination_rect; // for destination
    SDL_Rect main_destination_rect; // for destination

    //���� 
    Mix_Music* background_music;
    Mix_Chunk* bell_sound;
    //Mix_Chunk* hit_sound; -> Creature_stage3.h�� ����
    Mix_Chunk* bombPrev_sound;
    Mix_Chunk* bombAfter_sound;
    Mix_Chunk* button_sound;

    //�۾� �ؽ���
    SDL_Texture* ready_texture;
    SDL_Rect readyCount_destination;

    SDL_Texture* myBell_; //���� �� ���� ���
    SDL_Rect myBell_destination;

};