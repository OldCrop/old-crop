#include "Phase_stage1Game.h"
#include "Creature.h"
#include <vector>

int g_input;

int g_X;
int g_Y;

bool g_key_up = false;
bool g_key_down = false;
bool g_key_left = false;
bool g_key_right = false;
bool g_key_space = false;
bool is_rock = false;
bool is_hard;

Direction g_direction = DOWN_;
Uint32 FIRE_COOLDOWN = 500;  // ����ü �߻� ��Ÿ��

const int monsterCount = 20;

// �귯�� �ð� ���
double g_elapsed_time_ms;


Stage1::Stage1() {
    //g_elapsed_time_ms = 0;

    g_key_up = false;
    g_key_down = false;
    g_key_left = false;
    g_key_right = false;
    g_key_space = false;
    is_rock = false;
    FIRE_COOLDOWN = 500;
    g_direction = DOWN_;
    g_elapsed_time_ms = 0;
    stg1_pause_btn_pushed = 0;
    gameStartTime = SDL_GetTicks();
    srand(time(NULL));

    items = new Item(0, 0, 0);
    items->items.clear();

    for (auto& monster : monsters) {
        delete monster;  // �����Ͱ� ����Ű�� �޸𸮸� �����մϴ�.
    }

    monsters.clear();  // ���͸� ���ϴ�.

    if (dogPoop != nullptr)
        delete dogPoop;  // �����Ͱ� ����Ű�� �޸𸮸� �����մϴ�.
    dogPoop = new DogPoop(0, 10, 5, 100.0, 10, 1, 10, 0);
    dogPoop->setXY(SCREEN_WIDTH / 2 + 20, SCREEN_HEIGHT / 2);
    dogPoop->setSpeed(5);
    dogPoop->setHealth(100.0);
    dogPoop->setProjectileSpeed(7);
    dogPoop->setProjectileDamage(10);




    if (dandelion != nullptr)
        delete dandelion;  // �����Ͱ� ����Ű�� �޸𸮸� �����մϴ�.

    dandelion = new Dandelion(50, 50, 0, 100.0, 10);
    dandelion->setXY(SCREEN_WIDTH / 2 - 25, SCREEN_HEIGHT / 2 - 25);
    dandelion->setSpeed(0);
    if (is_hard) {
        dandelion->setHealth(200.0);
    }
    else {
        dandelion->setHealth(100.0);
    }

    dogPoop->setInvincible(false);

    // 50���� ���͸� ���ͷ� �����մϴ�.
    //std::vector<Monster*> monsters;

    // projectiles ���͸� ���ϴ�.
    dogPoop->projectiles.clear();

    if (g_current_game_phase == PHASE_STAGE1_GAME) {
        //���� ���
        Mix_PlayMusic(stg1_music, -1);
    }
    else {
        //���� ����
        Mix_HaltMusic();
    }
    // ��� �̹��� �ε�
    bg_surface = IMG_Load("../../Resources/stage1/bg.png");
    bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
    SDL_FreeSurface(bg_surface);
    bg_source_rect = { 0, 0, 1080, 720 };
    bg_dest_rect = { 40, 40, 1000, 640 };

    bgframe_surface = IMG_Load("../../Resources/frame.png");
    bgframe_texture = SDL_CreateTextureFromSurface(g_renderer, bgframe_surface);
    SDL_FreeSurface(bgframe_surface);
    bgframe_source_rect = { 0, 0, 1080, 720 };
    bgframe_dest_rect = { 0, 0, 1080, 720 };

    // ������ �̹��� ��Ʈ �ε�
    i_surface = IMG_Load("../../Resources/stage1/item/items2_sheet.png");
    i_texture = SDL_CreateTextureFromSurface(g_renderer, i_surface);
    SDL_FreeSurface(i_surface);
    i_source_rect = { 0, 0, 32, 32 };
    i_dest_rect = { 0, 0, 50, 50 };

    // ������ �̹��� ��Ʈ�� �ִϸ��̼� �������� ����
    for (int i = 0; i < 4; i++) { // ������ ������ 4��
        std::vector<SDL_Rect> itemClip; // �� �������� �ִϸ��̼� �������� ������ ����
        for (int j = 0; j < 10; j++) { // �� �������� �ִϸ��̼� �������� 10��
            SDL_Rect clip;
            clip.x = j * 32;
            clip.y = i * 32;
            clip.w = 32;
            clip.h = 32;
            itemClip.push_back(clip);
        }
        itemClips.push_back(itemClip); // �� �������� �ִϸ��̼� ������ ���͸� ��ü ������ �ִϸ��̼� ������ ���Ϳ� �߰�
    }

    // ������ ���� �̹��� ��Ʈ�� �ε�
    dp_ani_surface = IMG_Load("../../Resources/stage1/creature/dogPoopMovesheet.png");
    dogPoopTexture = SDL_CreateTextureFromSurface(g_renderer, dp_ani_surface);
    SDL_FreeSurface(dp_ani_surface);
    dp_source_rect = { 0, 0, 32, 32 };
    dp_dest_rect = { 0, 0, 50, 50 };


    // ������ ���� �ִϸ��̼� �������� ����
    for (int i = 0; i < 4; ++i) {
        SDL_Rect clip;
        clip.x = i * 32;
        clip.y = 0;
        clip.w = 32;
        clip.h = 32;
        dogPoopClips.push_back(clip);
    }

    // ������ ���� �¾��� ���� �̹����� �ε�
    dp_hit_surface = IMG_Load("../../Resources/stage1/creature/dogPoopHitted.png");
    dogPoopHitTexture = SDL_CreateTextureFromSurface(g_renderer, dp_hit_surface);
    SDL_FreeSurface(dp_hit_surface);

    // �ε鷹 �̹��� �ε�
    d_surface = IMG_Load("../../Resources/stage1/creature/dandelion.png");
    d_texture = SDL_CreateTextureFromSurface(g_renderer, d_surface);
    SDL_FreeSurface(d_surface);
    d_source_rect = { 0, 0, 32, 32 };
    d_dest_rect = { 0, 0, 50, 50 };

    // �ε鷹�� �¾��� ���� �̹����� �ε�
    d_hit_surface = IMG_Load("../../Resources/stage1/creature/dandelionHitted1.png");
    d_hit_texture = SDL_CreateTextureFromSurface(g_renderer, d_hit_surface);
    SDL_FreeSurface(d_hit_surface);

    d_hit_surface2 = IMG_Load("../../Resources/stage1/creature/dandelionHitted2.png");
    d_hit_texture2 = SDL_CreateTextureFromSurface(g_renderer, d_hit_surface2);
    SDL_FreeSurface(d_hit_surface2);

    d_hit_surface3 = IMG_Load("../../Resources/stage1/creature/dandelionHitted3.png");
    d_hit_texture3 = SDL_CreateTextureFromSurface(g_renderer, d_hit_surface3);
    SDL_FreeSurface(d_hit_surface3);

    // ���Ƹ� �̹��� �ε�
    c_surface = IMG_Load("../../Resources/stage1/creature/chick.png");
    c_texture = SDL_CreateTextureFromSurface(g_renderer, c_surface);
    SDL_FreeSurface(c_surface);
    c_source_rect = { 0, 0, 32, 32 };
    c_dest_rect = { 0, 0, 32, 32 };

    // ���� �̹��� �ε�
    s_surface = IMG_Load("../../Resources/stage1/creature/sparrow.png");
    s_texture = SDL_CreateTextureFromSurface(g_renderer, s_surface);
    SDL_FreeSurface(s_surface);
    s_source_rect = { 0, 0, 32, 32 };
    s_dest_rect = { 0, 0, 32, 32 };

    // ����ü �̹��� �ε�
    p_surface = IMG_Load("../../Resources/stage1/item/projectile.png");
    p_texture = SDL_CreateTextureFromSurface(g_renderer, p_surface);
    SDL_FreeSurface(p_surface);
    p_rock_surface = IMG_Load("../../Resources/stage1/item/projectile_rock.png");
    p_rock_texture = SDL_CreateTextureFromSurface(g_renderer, p_rock_surface);
    SDL_FreeSurface(p_rock_surface);
    p_source_rect = { 0, 0, 32, 32 };
    p_dest_rect = { 0, 0, 40, 40 };

    // empty heart, half heart, full heart �̹��� �ε�
    h0_surface = IMG_Load("../../Resources/heart0.png");
    h0_texture = SDL_CreateTextureFromSurface(g_renderer, h0_surface);
    SDL_FreeSurface(h0_surface);
    h1_surface = IMG_Load("../../Resources/heart1.png");
    h1_texture = SDL_CreateTextureFromSurface(g_renderer, h1_surface);
    SDL_FreeSurface(h1_surface);
    h2_surface = IMG_Load("../../Resources/heart2.png");
    h2_texture = SDL_CreateTextureFromSurface(g_renderer, h2_surface);
    SDL_FreeSurface(h2_surface);

    // ###### �Ͻ� ���� �̹��� #######
    // main, continue ��ư �̹��� �ε�
    SDL_Surface* tmp_surface1 = IMG_Load("../../Resources/btn_continue.png");
    _stg1_continue_button_texture = SDL_CreateTextureFromSurface(g_renderer, tmp_surface1);
    SDL_FreeSurface(tmp_surface1);

    _stg1_continue_button_destination = { 490, 270, 100, 100 };

    SDL_Surface* tmp_surface2 = IMG_Load("../../Resources/btn_main.png");
    _stg1_home_button_texture = SDL_CreateTextureFromSurface(g_renderer, tmp_surface2);
    SDL_FreeSurface(tmp_surface2);

    _stg1_home_button_destination = { 490, 370, 100, 100 };

    // ������ ���� ���
    SDL_Surface* tmp_surface3 = IMG_Load("../../Resources/translucent_black.png");
    _stg1_pause_bg_texture = SDL_CreateTextureFromSurface(g_renderer, tmp_surface3);
    SDL_FreeSurface(tmp_surface3);
    _stg1_pause_bg_destination = { 0, 0, 1080, 720 };

    // ������� �ε�
    stg1_music = Mix_LoadMUS("../../Resources/stage1/sounds/stg1backgroundmusic.mp3");

    // ������ �Դ� ȿ���� �ε�
    stg1_eat_sound = Mix_LoadWAV("../../Resources/stage1/sounds/stgItemEat.wav");

    // �߻� ȿ���� �ε�
    stg1_shoot_sound = Mix_LoadWAV("../../Resources/stage1/sounds/stgShoot.wav");

    // �Ͻ����� ��ư ȿ���� �ε�
    stg1_pause_sound = Mix_LoadWAV("../../Resources/stage1/sounds/pauseSound.wav");

    //std::cout << dogPoop->getHealth() << std::endl;
    //std::cout << dogPoop->getKillcount() << std::endl;

}

void Stage1::HandleEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {

        case SDL_QUIT:
            g_flag_running = false;
            break;

        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                g_is_paused = !g_is_paused;  // ������ �Ͻ����� ���¸� ����մϴ�.
                if (g_is_paused) {
                    g_pause_sound_played = false;  // �Ͻ����� ���·� ��ȯ�� �� ȿ���� ��� ���¸� �ʱ�ȭ�մϴ�.
                }
            }
            if (event.key.keysym.sym == SDLK_LEFT) {
                g_key_left = true;
            }
            if (event.key.keysym.sym == SDLK_RIGHT) {
                g_key_right = true;
            }
            if (event.key.keysym.sym == SDLK_UP) {
                g_key_up = true;
            }
            if (event.key.keysym.sym == SDLK_DOWN) {
                g_key_down = true;
            }
            if (event.key.keysym.sym == SDLK_SPACE) {
                g_key_space = true;
            }


            break;

        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_LEFT) {
                g_key_left = false;
            }
            if (event.key.keysym.sym == SDLK_RIGHT) {
                g_key_right = false;
            }
            if (event.key.keysym.sym == SDLK_UP) {
                g_key_up = false;
            }
            if (event.key.keysym.sym == SDLK_DOWN) {
                g_key_down = false;
            }
            if (event.key.keysym.sym == SDLK_SPACE) {
                g_key_space = false;
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                g_X = event.button.x;
                g_Y = event.button.y;
                if (g_X >= _stg1_continue_button_destination.x && g_X <= _stg1_continue_button_destination.x + _stg1_continue_button_destination.w &&
                    g_Y >= _stg1_continue_button_destination.y && g_Y <= _stg1_continue_button_destination.y + _stg1_continue_button_destination.h) {
                    Mix_PlayChannel(-1, stg1_pause_sound, 0);
                    stg1_pause_btn_pushed = 1; //continue ��ư ����
                }
                else if (g_X >= _stg1_home_button_destination.x && g_X <= _stg1_home_button_destination.x + _stg1_home_button_destination.w &&
                    g_Y >= _stg1_home_button_destination.y && g_Y <= _stg1_home_button_destination.y + _stg1_home_button_destination.h) {
                    Mix_PlayChannel(-1, stg1_pause_sound, 0);
                    stg1_pause_btn_pushed = 2; //home ��ư ����
                }
            }
            break;
        default:
            break;
        }
    }
}




void Stage1::Update() {
    // 1.1. Ű���� �Է¿� ���� ���ΰ��� ��ġ�� �����Ѵ�.
    // �Ͻ����� �������� Ȯ��
    std::cout << dogPoop->getHealth();
    if (g_is_paused) {
        //����� �Ͻ� ����
        Mix_PauseMusic();
        if (!g_pause_sound_played) {
            Mix_PlayChannel(-1, stg1_pause_sound, 0);
            g_pause_sound_played = true;  // ȿ������ ����Ǿ����� ǥ��
        }

        if (stg1_pause_btn_pushed == 1) {
            g_is_paused = !g_is_paused;// ������ �Ͻ����� ���¸� ���
            g_pause_sound_played = false;  // "Continue" ��ư�� ������ ȿ���� ��� ���¸� �ʱ�ȭ
            stg1_pause_btn_pushed = 0;
        }
        else if (stg1_pause_btn_pushed == 2) {
            g_is_paused = !g_is_paused;  // ������ �Ͻ����� ���¸� ���
            g_current_game_phase = PHASE_INTRO;
            game_result = 0;
            stg1_pause_btn_pushed = 0;
        }

        return;  // ������ �Ͻ������� ���, ������Ʈ�� �������� �ʽ��ϴ�.
    }
    else {
        //����� ���
        Mix_ResumeMusic();
    }
    if (g_key_left && g_key_up) {
        dogPoop->move(-1, -1);  // ���� ���� �̵�
        g_direction = LEFT_UP;
    }
    else if (g_key_right && g_key_up) {
        dogPoop->move(1, -1);  // ������ ���� �̵�

        g_direction = RIGHT_UP;

    }
    else if (g_key_left && g_key_down) {
        dogPoop->move(-1, 1);  // ���� �Ʒ��� �̵�
        g_direction = LEFT_DOWN;
    }
    else if (g_key_right && g_key_down) {
        dogPoop->move(1, 1);  // ������ �Ʒ��� �̵�
        g_direction = RIGHT_DOWN;
    }
    // ���� �̵�
    else if (g_key_left) {
        dogPoop->move(-1, 0);  // �������� �̵�

        g_direction = LEFT_;
    }
    // ���� �̵�
    else if (g_key_right) {
        dogPoop->move(1, 0);

        g_direction = RIGHT_;
    }
    // ���� �̵�
    else if (g_key_up) {
        dogPoop->move(0, -1);  // ���� �̵�

        g_direction = UP_;
    }
    // �Ʒ��� �̵�
    else if (g_key_down) {
        dogPoop->move(0, 1);  // �Ʒ��� �̵�

        g_direction = DOWN_;
    }
    // ȭ�� ������ ������ ���� Ȯ���մϴ�.
    if (dogPoop->getX() < 40) {
        dogPoop->setX(40);
    }
    else if (dogPoop->getX() > bg_dest_rect.w + 40 - dp_dest_rect.w) {
        dogPoop->setX(bg_dest_rect.w + 40 - dp_dest_rect.w);
    }
    if (dogPoop->getY() < 40) {
        dogPoop->setY(40);
    }
    else if (dogPoop->getY() > bg_dest_rect.h + 40 - dp_dest_rect.h) {
        dogPoop->setY(bg_dest_rect.h + 40 - dp_dest_rect.h);
    }

    Uint32 currentTime = SDL_GetTicks();
    // �����̽��ٸ� ������, ����ü�� �߻��Ѵ�.
    if (g_key_space && currentTime >= lastFireTime + FIRE_COOLDOWN) {
        int dx = 0, dy = 0;
        switch (g_direction) {
        case LEFT_: dx = -1; break;
        case RIGHT_: dx = 1; break;
        case UP_: dy = -1; break;
        case DOWN_: dy = 1; break;
        case LEFT_UP: dx = -1; dy = -1; break;
        case RIGHT_UP: dx = 1; dy = -1; break;
        case LEFT_DOWN: dx = -1; dy = 1; break;
        case RIGHT_DOWN: dx = 1; dy = 1; break;
        }
        Mix_PlayChannel(-1, stg1_shoot_sound, 0);
        dogPoop->throwProjectile(dx, dy);
        lastFireTime = currentTime;
    }

    // 1.2. ����ü �̵�
    dogPoop->moveProjectiles();

    if (dogPoop->getKillcount() > monsterCount) {
        g_current_game_phase = PHASE_STAGE1_ENDING;
        game_result = 3;
        viewedEndings[0][2] = true;
    }

    //3�ʸ��� �� ����
    if (g_elapsed_time_ms >= 3000 && monsters.size() < 50) {
        // �� ��ü�� ���� ��ġ�� ȭ���� �ܺη� �����մϴ�.
        int x, y;
        int spawnSide = rand() % 4; // 0: ����, 1: ������, 2: ����, 3: �Ʒ���
        switch (spawnSide) {
        case 0: // ���ʿ��� ����
            x = -50;
            y = (rand() % SCREEN_HEIGHT + 50) - 100;
            break;
        case 1: // �����ʿ��� ����
            x = SCREEN_WIDTH + 50;
            y = (rand() % SCREEN_HEIGHT + 50) - 100;
            break;
        case 2: // ���ʿ��� ����
            x = (rand() % SCREEN_WIDTH + 50) - 100;
            y = -50;
            break;
        case 3: // �Ʒ��ʿ��� ����
            x = (rand() % SCREEN_WIDTH + 50) - 100;
            y = SCREEN_HEIGHT + 50;
            break;
        }
        // Chick or Sparrow
        if (rand() % 2 == 0) {
            monsters.push_back(new Chick(x, y, 1, 40, 10, dogPoop->getX(), dogPoop->getY()));
            monsters.back()->setTarget(dogPoop);
        }
        else {
            monsters.push_back(new Sparrow(x, y, 1, 60, 20, dogPoop->getX(), dogPoop->getY()));
            monsters.back()->setTarget(dandelion);
        }
        if (monsters.size() % 3 == 0) {
            //������ �����ֱ� = ���Ͱ� n�� ������ ������ 
            int x = rand() % (SCREEN_WIDTH - 120) + 40;
            int y = rand() % (SCREEN_HEIGHT - 120) + 40;
            int type;
            if (is_rock) {
                type = rand() % 3;
            }
            else {
                type = rand() % 4;
            }
            items->items.push_back(new Item(x, y, type));
        }
        // ��� �ð� �ʱ�ȭ
        g_elapsed_time_ms = 0;
    }
    //���͵� �̵� ����
    for (auto& monster : monsters) {
        monster->toTarget();
    }

    // 1.3. ����ü�� ���� �浹 ����
    dogPoop->updateProjectiles(monsters);

    // 1.4. ���� �ε鷹, ���ΰ��� �浹 ����
    for (auto& monster : monsters) {
        Uint32 currentTime = SDL_GetTicks();
        // ���� �ε鷹�� �浹 ����
        int dx1 = dandelion->getX() - monster->getX();
        int dy1 = dandelion->getY() - monster->getY();
        if (dx1 * dx1 + dy1 * dy1 < COLLISION_DISTANCE * COLLISION_DISTANCE) {
            //���� �� �ε鷹�� 2�ʰ� ����
            if (currentTime >= dandelionInvincibleStartTime + 2000) {
                dandelion->GetAttackted(monster->getAttackDamage());
                dandelionInvincibleStartTime = currentTime;
            }
        }
        // ���� ���ΰ��� �浹 ����
        int dx2 = dogPoop->getX() - monster->getX();
        int dy2 = dogPoop->getY() - monster->getY();
        //���� �� ���������� 2�ʰ� ����
        if (dx2 * dx2 + dy2 * dy2 < COLLISION_DISTANCE * COLLISION_DISTANCE) {
            if (currentTime >= dogPoopInvincibleStartTime + 2000) {
                dogPoop->setInvincible(true);
                dogPoop->GetAttackted(monster->getAttackDamage());
                dogPoopInvincibleStartTime = currentTime;
            }
        }
    }
    // ���� ���� ����
    Uint32 currentTimed = SDL_GetTicks();
    if (dogPoop->getInvincible() && currentTimed >= dogPoopInvincibleStartTime + 2000) {
        dogPoop->setInvincible(false);
    }

    //�����۰� ���������� �浹 ����
    for (int i = 0; i < items->items.size(); ++i) {
        Item* item = items->items[i];
        int dx = dogPoop->getX() - item->getX();
        int dy = dogPoop->getY() - item->getY();
        if (dx * dx + dy * dy < COLLISION_DISTANCE * COLLISION_DISTANCE) {
            Mix_PlayChannel(-1, stg1_eat_sound, 0);
            if (item->getType() == 0) {
                //0���̸� ü�� ȸ�� ������
                dogPoop->setHealth(dogPoop->getHealth() + 10);
            }
            else if (item->getType() == 1) {
                //1���̸� ���ݷ� ���� ������
                FIRE_COOLDOWN -= 50;
                if (FIRE_COOLDOWN <= 300)
                    FIRE_COOLDOWN = 300;
            }
            else if (item->getType() == 2) {
                //2���̸� �̵��ӵ� ���� ������
                dogPoop->setSpeed(dogPoop->getSpeed() + 1);
            }
            else if (item->getType() == 3) {
                //3���̸� �� ���� 
                is_rock = true;
                dogPoop->setProjectileDamage(15);
            }
            delete item;
            items->items.erase(items->items.begin() + i);
            --i;
        }
    }
    //����� ü���� 0���Ϸ� �������� ����
    if (dogPoop->getHealth() <= 0) {
        g_current_game_phase = PHASE_STAGE1_ENDING;
        game_result = 2;
        viewedEndings[0][1] = true;
    }
    //�ε鷹 ü���� 0���Ϸ� �������� ����
    if (dandelion->getHealth() <= 0) {
        g_current_game_phase = PHASE_STAGE1_ENDING;
        game_result = 1;
        viewedEndings[0][0] = true;
    }

    g_elapsed_time_ms += 33;
}

void Stage1::Render() {
    // Clear the renderer
    if (SDL_RenderClear(g_renderer) != 0) {
      //  std::cerr << "Error clearing renderer: " << SDL_GetError() << std::endl;
    }

    // Render the background
    if (SDL_RenderCopy(g_renderer, bg_texture, &bg_source_rect, &bg_dest_rect) != 0) {
       // std::cerr << "Error rendering background: " << SDL_GetError() << std::endl;
    }
    else {
      //  std::cout << "Background rendered successfully." << std::endl;
    }

    // Render the dandelion
    d_dest_rect.x = dandelion->getX();
    d_dest_rect.y = dandelion->getY();
    SDL_Texture* currentTexture = nullptr;

    if (dandelion->getHealth() >= 80) {
        currentTexture = d_texture;
    }
    else if (dandelion->getHealth() >= 50) {
        currentTexture = d_hit_texture;
    }
    else if (dandelion->getHealth() >= 20) {
        currentTexture = d_hit_texture2;
    }
    else {
        currentTexture = d_hit_texture3;
    }

    if (SDL_RenderCopy(g_renderer, currentTexture, &d_source_rect, &d_dest_rect) != 0) {
       // std::cerr << "Error rendering dandelion: " << SDL_GetError() << std::endl;
    }
    else {
       // std::cout << "Dandelion rendered successfully." << std::endl;
    }

    // Render the items
    for (Item* item : items->items) {
        int itemType = item->getType(); // �������� ����
        int frameIndex = item->getCurrentFrameIndex(); // ������ �ִϸ��̼� ������ �ε���
        SDL_Rect& clip = itemClips[itemType][frameIndex]; // ������ �ִϸ��̼� ������
        i_dest_rect.x = item->getX();
        i_dest_rect.y = item->getY();
        if (SDL_RenderCopy(g_renderer, i_texture, &clip, &i_dest_rect) != 0) {
            //std::cerr << "Error rendering item: " << SDL_GetError() << std::endl;
        }
        else {
           // /std::cout << "Item rendered successfully." << std::endl;
        }
        item->frameUpdate();
    }

    // Render the dogPoop
    dp_dest_rect.x = dogPoop->getX();
    dp_dest_rect.y = dogPoop->getY();
    SDL_Texture* dogPoopTexturetemp = nullptr;
    SDL_Rect* dogPoopCliptemp = nullptr;

    dogPoopTexturetemp = dogPoopTexture;
    dogPoopCliptemp = &dogPoopClips[dogPoop->getCurrentFrameIndex()];

    if (dogPoop->getInvincible()) {
        dogPoopTexturetemp = dogPoopHitTexture;
        dogPoopCliptemp = &dp_source_rect;
    }
    SDL_RenderCopy(g_renderer, dogPoopTexturetemp, dogPoopCliptemp, &dp_dest_rect);
    /*
    if (SDL_RenderCopy(g_renderer, dogPoopTexture, dogPoopClip, &dp_dest_rect) != 0) {
        std::cerr << "Error rendering dogPoop: " << SDL_GetError() << std::endl;
    }
    else {

        std::cout << "DogPoop rendered successfully." << std::endl;
    }
    */
    // Render the monsters
    for (auto& monster : monsters) {
        SDL_Texture* currentMonsterTexture = nullptr;
        SDL_Rect* currentMonsterRect = nullptr;

        if (dynamic_cast<Chick*>(monster)) {
            c_dest_rect.x = monster->getX();
            c_dest_rect.y = monster->getY();
            currentMonsterTexture = c_texture;
            currentMonsterRect = &c_source_rect;
        }
        else if (dynamic_cast<Sparrow*>(monster)) {
            s_dest_rect.x = monster->getX();
            s_dest_rect.y = monster->getY();
            currentMonsterTexture = s_texture;
            currentMonsterRect = &s_source_rect;
        }

        if (SDL_RenderCopyEx(g_renderer, currentMonsterTexture, currentMonsterRect, currentMonsterRect == &c_source_rect ? &c_dest_rect : &s_dest_rect, 0, NULL, SDL_FLIP_NONE) != 0) {
            //std::cerr << "Error rendering monster: " << SDL_GetError() << std::endl;
        }
        else {
            //std::cout << "Monster rendered successfully." << std::endl;
        }
    }

    // Render the projectiles
    for (Projectile* projectile : dogPoop->projectiles) {
        p_dest_rect.x = projectile->getX();
        p_dest_rect.y = projectile->getY();
        SDL_Texture* projectileTexture = is_rock ? p_rock_texture : p_texture;

        if (SDL_RenderCopyEx(g_renderer, projectileTexture, &p_source_rect, &p_dest_rect, 0, NULL, SDL_FLIP_NONE) != 0) {
           // std::cerr << "Error rendering projectile: " << SDL_GetError() << std::endl;
        }
        else {
           // std::cout << "Projectile rendered successfully." << std::endl;
        }
    }

    //draw photoframe.png 
    SDL_RenderCopy(g_renderer, bgframe_texture, &bgframe_source_rect, &bgframe_dest_rect);

    // Render the player's health
    int dp_health = dogPoop->getHealth();
    SDL_Rect heart_rect = { 10, 10, 30, 30 }; // Example position and size of the heart
    for (int i = 0; i < dp_health / 20; ++i) {
        if (SDL_RenderCopy(g_renderer, h2_texture, NULL, &heart_rect) != 0) {
            //std::cerr << "Error rendering heart (full): " << SDL_GetError() << std::endl;
        }
        else {
            //std::cout << "Heart (full) rendered successfully." << std::endl;
        }
        heart_rect.x += 40; // Setting the gap between hearts
    }
    if (dp_health % 20 >= 10) {
        if (SDL_RenderCopy(g_renderer, h1_texture, NULL, &heart_rect) != 0) {
            //std::cerr << "Error rendering heart (half): " << SDL_GetError() << std::endl;
        }
        else {
            //std::cout << "Heart (half) rendered successfully." << std::endl;
        }
        heart_rect.x += 40;
    }

    if (g_is_paused) {
        SDL_RenderCopy(g_renderer, _stg1_pause_bg_texture, NULL, &_stg1_pause_bg_destination);
        SDL_RenderCopy(g_renderer, _stg1_home_button_texture, NULL, &_stg1_home_button_destination);
        SDL_RenderCopy(g_renderer, _stg1_continue_button_texture, NULL, &_stg1_continue_button_destination);
    }
    SDL_RenderPresent(g_renderer);
}


void Stage1::Reset() {

    g_key_up = false;
    g_key_down = false;
    g_key_left = false;
    g_key_right = false;
    g_key_space = false;
    is_rock = false;
    FIRE_COOLDOWN = 500;
    g_direction = DOWN_;
    g_elapsed_time_ms = 0;
    stg1_pause_btn_pushed = 0;
    gameStartTime = SDL_GetTicks();
    srand(time(NULL));

    items = new Item(0, 0, 0);
    items->items.clear();

    for (auto& monster : monsters) {
        delete monster;  // �����Ͱ� ����Ű�� �޸𸮸� �����մϴ�.
    }

    monsters.clear();  // ���͸� ���ϴ�.

    if (dogPoop != nullptr)
        delete dogPoop;  // �����Ͱ� ����Ű�� �޸𸮸� �����մϴ�.

    if (!is_hard) { //is_hard �� �����ϱ�
        //������� �� ��� �ǰ� 2�� ( �������� ISHARD�� )
        dogPoop = new DogPoop(0, 10, 5, 200.0, 10, 1, 10, 10);
        dogPoop->setXY(SCREEN_WIDTH / 2 + 20, SCREEN_HEIGHT / 2);
        dogPoop->setSpeed(5);
        dogPoop->setHealth(200.0);
        dogPoop->setKillcount(16);
        dogPoop->setHealth(100.0);
        dogPoop->setProjectileSpeed(7);
        dogPoop->setProjectileDamage(10);
    }
    else {
        dogPoop = new DogPoop(0, 10, 5, 100.0, 10, 1, 10, 0);
        dogPoop->setXY(SCREEN_WIDTH / 2 + 20, SCREEN_HEIGHT / 2);
        dogPoop->setSpeed(5);
        dogPoop->setHealth(200.0);
        dogPoop->setKillcount(10);
        dogPoop->setHealth(100.0);
        dogPoop->setProjectileSpeed(7);
        dogPoop->setProjectileDamage(10);
    }

    if (dandelion != nullptr)
        delete dandelion;  // �����Ͱ� ����Ű�� �޸𸮸� �����մϴ�.

    dandelion = new Dandelion(50, 50, 0, 100.0, 10);
    dandelion->setXY(SCREEN_WIDTH / 2 - 25, SCREEN_HEIGHT / 2 - 25);
    dandelion->setSpeed(0);
    if (is_hard) {
        dandelion->setHealth(200.0);
    }
    else {
        dandelion->setHealth(100.0);
    }

    dogPoop->setInvincible(false);

    // 50���� ���͸� ���ͷ� �����մϴ�.
    //std::vector<Monster*> monsters;

    // projectiles ���͸� ���ϴ�.
    dogPoop->projectiles.clear();

    if (g_current_game_phase == PHASE_STAGE1_GAME) {
        //���� ���
        Mix_PlayMusic(stg1_music, -1);
    }
    else {
        //���� ����
        Mix_HaltMusic();
    }


}


Stage1::~Stage1() {

    delete dandelion;
    delete dogPoop;
    for (int i = 0; i < monsterCount; ++i) {
        delete monsters[i];
    }
    for (auto monster : monsters) {
        delete monster;
    }
    for (auto item : items->items) {
        delete item;
    }
    delete items;

    SDL_DestroyTexture(bg_texture);
    SDL_DestroyTexture(dogPoopTexture);
    SDL_DestroyTexture(dogPoopHitTexture);
    SDL_DestroyTexture(d_texture);
    SDL_DestroyTexture(c_texture);
    SDL_DestroyTexture(s_texture);
    SDL_DestroyTexture(p_texture);
    SDL_DestroyTexture(i_texture);
    SDL_DestroyTexture(h0_texture);
    SDL_DestroyTexture(h1_texture);
    SDL_DestroyTexture(h2_texture);
    SDL_DestroyTexture(p_rock_texture);
    SDL_DestroyTexture(d_hit_texture);
    SDL_DestroyTexture(d_hit_texture2);
    SDL_DestroyTexture(d_hit_texture3);
    SDL_DestroyTexture(_stg1_continue_button_texture);
    SDL_DestroyTexture(_stg1_home_button_texture);
    SDL_DestroyTexture(_stg1_pause_bg_texture);
    SDL_DestroyTexture(bgframe_texture);


    Mix_FreeMusic(stg1_music);
    Mix_FreeChunk(stg1_eat_sound);
    Mix_FreeChunk(stg1_shoot_sound);
    Mix_FreeChunk(stg1_pause_sound);


}

