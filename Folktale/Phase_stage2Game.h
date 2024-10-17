#pragma once
#include <SDL.h>
#include "Creature_stage2.h"
#include "STAGE.h"


class Stage2 : public PhaseInterface {
public:
    Stage2();
    ~Stage2();

    void HandleEvents();
    void Update();
    void Render();
    void Reset();




private:
    Turtle* turtle;
    Rabbit* rabbit;
    Coral* coral;
    Coral2* coral2;
    Conch* conch1;
    Conch* conch2;
    Conch* conch3;
    Conch* conch4;
    Conch* conch5;
    Conch* conch6;
    Conch* conch7;

    // ����Ű ���� ������
    bool f_list[4];
    int f_state; // ���� ���� Ű ����
    bool stop; // ���� ����
    //����Ű ���� ������
    //���� Ȯ�� ����
    SDL_RendererFlip flip;

    //�̷�

    int rabbitSpawnTimer;
    int coral2_spawn_timer; // coral2�� ��Ÿ���� ������� �ð��� �����ϴ� Ÿ�̸�
    int coral3_spawn_timer; // coral�� ��Ÿ���� ������� �ð��� �����ϴ� Ÿ�̸�=>�߰�
    bool coral2_visible;
    bool coral3_visible;//=>�߰�

    Uint32 pauseStartTime;
    Uint32 totalPauseTime;
    Uint32 totalPauseTime_2;

    //�ƹ�Ű�� ������ ����
    int stage2_startTime;
    int stage2_status; //0�̸� Ű ��� ����, 1�̸� ���� ��, 2�� ���� �Ͻ�����
    int alpha;

    //�ؽ���
    SDL_Texture* stage2_bg_texture;
    SDL_Texture* turtle_texture;
    SDL_Texture* rabbit_texture;
    SDL_Texture* coral_texture;
    SDL_Texture* coral2_texture;
    SDL_Texture* gan_texture;
    SDL_Texture* heart0_texture;
    SDL_Texture* heart2_texture;
    SDL_Texture* stage2_bgbgbg_texture;
    SDL_Texture* conch_texture;
    SDL_Texture* conch_texture2;
    SDL_Texture* turtle2_texture;


    //�ؽ��� �簢��
    SDL_Rect turtle_destination_rect;
    SDL_Rect rabbit_destination_rect;
    SDL_Rect coral_destination_rect;
    SDL_Rect coral2_destination_rect;
    SDL_Rect stage2_bg_destination_rect;
    SDL_Rect gan_destination_rect;
    SDL_Rect heart0_destination_rect;
    SDL_Rect heart2_destination_rect;
    SDL_Rect stage2_bgbgbg_destination_rect;
    SDL_Rect conch_destination_rect;
    SDL_Rect conch_destination_rect2;
    SDL_Rect wait_destination_rect;

    SDL_Texture* wait_texture; // the SDL_Texture
    SDL_Texture* bg_texture; // the SDL_Texture 
    SDL_Rect bg_destination_rect; // for destination
    //��ư �ؽ���
    SDL_Texture* button_main; // the SDL_Texture 
    SDL_Texture* button_continue; // the SDL_Texture 
    SDL_Rect continue_destination_rect; // for destination
    SDL_Rect main_destination_rect; // for destination

    //���� 
    Mix_Music* background_music;
    Mix_Chunk* conch_sound;
    Mix_Chunk* rabbit_sound;
    Mix_Chunk* coral_sound;
    Mix_Chunk* button_sound;
    //�۾� �ؽ���
    SDL_Texture* ready_texture;
    SDL_Rect readyCount_destination;

};

