#include "Phase_stage3Game.h"
#include <Windows.h>
#include <iomanip>
#include <string>

extern default_random_engine generator;

void Stage3::UpdateScoreTexture()
{
    if (myBell_ != 0)
    {
        SDL_DestroyTexture(myBell_);		// !!!�߿�!!!  �̹� �����Ǿ��ִ� texture �� ������ �ݵ�� �޸𸮿��� �������Ѵ�. !!!
        myBell_ = 0;
    }

    std::string str = std::to_string(bell->getCount());
    SDL_Surface* tmp_surface = TTF_RenderText_Blended(font, str.c_str(), { 255,255,255 });

    myBell_ = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);
}

Stage3::Stage3() {
    //1. ��ü ����
    //a. �� ����
    uniform_int_distribution<int> distributionX(1, screenWidth / GRID_STAGE3 - 2);
    uniform_int_distribution<int> distributionY(1, screenHeight / GRID_STAGE3 - 2);


    bell = new Bell(distributionX(generator), distributionY(generator), 0, 0);
    if (is_hard) {
        //b. ��ġ ����
        magpie = new Magpie(3, 3, 1, 30, 0,3); //(0,0)���� ����, speed�� 1,hp�� 30���� ����
        //c. ������ ����
        snake = new Snake(0, 0, 1, 100, 10, magpie->getX(), magpie->getY(), 8);
        //d. ��ź ����
        bombList.push_front(new Bomb(0, 0, 1, 100, 5, magpie->getX(), magpie->getY(), -20, 50, 75, 0));
    }
    else {
        //b. ��ġ ����
        magpie = new Magpie(3, 3, 1, 50, 0,5); //(0,0)���� ����, speed�� 1,hp�� 50���� ����
        //c. ������ ����
        snake = new Snake(0, 0, 1, 100, 10, magpie->getX(), magpie->getY(), 8);
        //d. ��ź ����
        bombList.push_front(new Bomb(0, 0, 1, 100, 5, magpie->getX(), magpie->getY(), -20, 50, 75, 0));
    }

    ////2. �ؽ��� ��������
    //a. �� �ؽ���
    SDL_Surface* temp_sheet_surface = IMG_Load("../../Resources/stage3/bell.png");
    bell_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�
    bell_destination_rect.x = bell->getX();
    bell_destination_rect.y = bell->getY();
    bell_destination_rect.w = GRID_STAGE3;
    bell_destination_rect.h = GRID_STAGE3;

    //b. ��ġ �ؽ���
    temp_sheet_surface = IMG_Load("../../Resources/stage3/magpie.png");
    magpie_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�
    magpie_destination_rect.x = magpie->getX() * GRID_STAGE3;
    magpie_destination_rect.y = magpie->getY() * GRID_STAGE3;
    magpie_destination_rect.w = GRID_STAGE3;
    magpie_destination_rect.h = GRID_STAGE3;


    //c. ������ �ؽ���
    temp_sheet_surface = IMG_Load("../../Resources/stage3/snakeHead.png");
    snakeHead_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�
    snake_destination_rect.x = snake->getSnakeList().front()->sX;
    snake_destination_rect.y = snake->getSnakeList().front()->sY;
    snake_destination_rect.w = GRID_STAGE3;
    snake_destination_rect.h = GRID_STAGE3;

    temp_sheet_surface = IMG_Load("../../Resources/stage3/snakeBody.png");
    snakeBody_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�
    temp_sheet_surface = IMG_Load("../../Resources/stage3/snakeTail.png");
    snakeTail_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�


    //��ź �ؽ��� 
    temp_sheet_surface = IMG_Load("../../Resources/stage3/bombAfter.png");
    bombAfter_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�
    bomb_source_rect.x = 0;
    bomb_source_rect.y = 0;
    bomb_source_rect.w = 32;
    bomb_source_rect.h = 32;

    bomb_destination_rect.w = GRID_STAGE3 * 3;
    bomb_destination_rect.h = GRID_STAGE3 * 3;

    //d. ��� �ؽ���
    temp_sheet_surface = IMG_Load("../../Resources/stage3/background.png");
    bg_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�
    bg_destination_rect.x = GRID_STAGE3;
    bg_destination_rect.y = GRID_STAGE3;
    bg_destination_rect.w = screenWidth - GRID_STAGE3 * 2;
    bg_destination_rect.h = screenHeight - GRID_STAGE3 * 2;

    temp_sheet_surface = IMG_Load("../../Resources/stage3/red.png");
    red_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�

    temp_sheet_surface = IMG_Load("../../Resources/translucent_black.png");
    wait_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�

    //��Ʈ �ؽ�ó
    temp_sheet_surface = IMG_Load("../../Resources/heart0.png");
    heartZero_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�

    temp_sheet_surface = IMG_Load("../../Resources/heart1.png");
    heartHalf_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�

    temp_sheet_surface = IMG_Load("../../Resources/heart2.png");
    heartOne_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�

    heart_destination_rect.w = GRID_STAGE3 - 15;
    heart_destination_rect.h = GRID_STAGE3 - 15;

    //��ư �ؽ���
    temp_sheet_surface = IMG_Load("../../Resources/btn_continue.png");
    button_continue = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�
    continue_destination_rect = { 490,270,100,100 };

    temp_sheet_surface = IMG_Load("../../Resources/btn_main.png");
    button_main = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�

    main_destination_rect = { 490,370,100,100 };



    //�۾� �ؽ��� �����,,
    myBell_destination.x = screenWidth - GRID_STAGE3 * 2;
    myBell_destination.y = GRID_STAGE3 + 5;
    myBell_destination.w = GRID_STAGE3 - 10;
    myBell_destination.h = GRID_STAGE3 - 5;

    ready_texture = SDL_CreateTextureFromSurface(g_renderer, TTF_RenderText_Blended(font, "READY", { 255,255,255 }));

    readyCount_destination.x = screenWidth / 2 - 100;
    readyCount_destination.y = screenHeight / 2 - 50;
    readyCount_destination.w = 200;
    readyCount_destination.h = 100;


    //���� ��������
    background_music = Mix_LoadMUS("../../Resources/stage3/stage3.mp3");
    Mix_VolumeMusic(90);

    bell_sound = Mix_LoadWAV("../../Resources/stage3/bell.wav");
    Mix_VolumeChunk(bell_sound, 128);


    bombPrev_sound = Mix_LoadWAV("../../Resources/stage3/bomb_prev.wav");
    Mix_VolumeChunk(bombPrev_sound, 128);
    bombAfter_sound = Mix_LoadWAV("../../Resources/stage3/bomb_After.wav");
    Mix_VolumeChunk(bombAfter_sound, 90);
    button_sound = Mix_LoadWAV("../../Resources/stage3/pauseSound.wav");
    Mix_VolumeChunk(button_sound, 128);

    //2. ��Ÿ ����
    f_state = STOP;//����Ű �� ����
    stop = true; //���� ��Ȳ���� �ʱ�ȭ
    key_pushed.clear();//Ű ���� �ʱ�ȭ



    flip = SDL_FLIP_HORIZONTAL;

    lastSpeedUpTime = 0;
    stage3_startTime = 0;
    lastBombTime = 0;

    stage3_status = 0;

    alpha = 0;

    pauseStartTime = 0;
    totalPauseTime = 0;
    totalPauseTime_2 = 0;

    magpie_init_health = magpie->getHealth();

    UpdateScoreTexture();

}


void Stage3::HandleEvents() {
    SDL_Event event;

    if (SDL_PollEvent(&event)) {
        switch (event.type) {

        case SDL_QUIT:
            g_flag_running = false;
            break;

        case SDL_KEYDOWN:

            if (event.key.keysym.sym == SDLK_ESCAPE) {
                if (stage3_status == 1) {//���� ���� ���̾����� �Ͻ�������
                    stage3_status = 2;
                    pauseStartTime = SDL_GetTicks();
                    totalPauseTime = 0;

                    Mix_PauseMusic(); // ������� �Ͻ�����
                    for (int i = 0; i < MIX_CHANNELS; i++) {
                        Mix_Pause(i); // ��� ä���� ���� �Ͻ�����
                    }
                }

            }
            if (stage3_status == 2) {//�Ͻ����� ���¸� Ű �Է� ���� ����
                break;
            }
            /////////////����Ű ����

            if (event.key.keysym.sym == SDLK_LEFT) {
                f_state = LEFT; //���� ���� ���� LEFT
                stop = false;
                if (stage3_status == 0) {
                    stage3_status = 1;
                    stage3_startTime = SDL_GetTicks();
                    lastBombTime = SDL_GetTicks();
                    /// Mix_FadeInMusic(background_music, -1, 2000);//�뷡 ���̵������� �ٷ� ����
                }

            }
            else if (event.key.keysym.sym == SDLK_RIGHT) {
                f_state = RIGHT;

                stop = false;


                if (stage3_status == 0) {
                    stage3_status = 1;
                    stage3_startTime = SDL_GetTicks();
                    lastBombTime = SDL_GetTicks();
                    ///Mix_FadeInMusic(background_music, -1, 2000);//�뷡 ���̵������� �ٷ� ����
                }
            }
            else if (event.key.keysym.sym == SDLK_UP) {
                f_state = UP;

                stop = false;


                if (stage3_status == 0) {
                    stage3_status = 1;
                    stage3_startTime = SDL_GetTicks();
                    lastBombTime = SDL_GetTicks();

                }
            }
            else if (event.key.keysym.sym == SDLK_DOWN) {
                f_state = DOWN;

                stop = false;

                if (stage3_status == 0) {
                    stage3_status = 1;
                    stage3_startTime = SDL_GetTicks();
                    lastBombTime = SDL_GetTicks();
                    //Mix_FadeInMusic(background_music, -1, 2000);//�뷡 ���̵������� �ٷ� ����
                }
            }
            if (std::find(key_pushed.begin(), key_pushed.end(), f_state) == key_pushed.end())
                key_pushed.push_front(f_state);//���� Ű ���� ����

            break;

        case SDL_KEYUP:

            if (event.key.keysym.sym == SDLK_LEFT) {
                key_pushed.remove(LEFT);
            }
            else if (event.key.keysym.sym == SDLK_RIGHT) {
                key_pushed.remove(RIGHT);

            }
            else if (event.key.keysym.sym == SDLK_UP) {
                key_pushed.remove(UP);

            }
            else if (event.key.keysym.sym == SDLK_DOWN) {
                key_pushed.remove(DOWN);



            }

            if (key_pushed.empty())
                stop = true;


            break;

        case SDL_MOUSEBUTTONDOWN:

            if (event.button.button == SDL_BUTTON_LEFT)
            {
                if (stage3_status == 2) {//�Ͻ����� ���¶��

                    int mouse_x = event.button.x;
                    int mouse_y = event.button.y;

                    if (mouse_x >= continue_destination_rect.x && mouse_x <= continue_destination_rect.x + continue_destination_rect.w &&
                        mouse_y >= continue_destination_rect.y && mouse_y <= continue_destination_rect.y + continue_destination_rect.h
                        )//����ϱ� ��ư ����
                    {
                        Mix_PlayChannel(-1, button_sound, 0);//ȿ���� ���

                        stage3_status = 1;
                        totalPauseTime = SDL_GetTicks() - pauseStartTime;
                        totalPauseTime_2 += totalPauseTime;
                        Mix_ResumeMusic(); // ������� ��� �簳
                        for (int i = 0; i < MIX_CHANNELS; i++) {
                            Mix_Resume(i); // ��� ä���� ���� ��� �簳
                        }
                    }
                    else if (mouse_x >= main_destination_rect.x && mouse_x <= main_destination_rect.x + main_destination_rect.w &&
                        mouse_y >= main_destination_rect.y && mouse_y <= main_destination_rect.y + main_destination_rect.h
                        )//�������� ��ư ����
                    {
                        Mix_PlayChannel(-1, button_sound, 0);//ȿ���� ���
                        g_current_game_phase = PHASE_MAIN_MENU;
                        game_result = 0;
                        if (Mix_PlayingMusic()) {
                            Mix_HaltMusic();
                        }
                    }
                }

            }
            break;
        }
    }
}
void Stage3::Update() {
    /*cout << "����Ű : ";
    for (int i : key_pushed) {
        cout << i << " ";
    }
    cout << endl;*/
    if (stage3_status == 0 || stage3_status == 2) //Ű ��� Ȥ�� �Ͻ�����  == stage3_status == 2
        return;



    //1. ��ġ
    //1.1 ��ġ ��ǥ ������Ʈ
    int x = magpie->getX();
    int y = magpie->getY();
    if (!stop) { //������ �ƴ϶�� ��ġ �̵�
        if (key_pushed.front() == LEFT) { //�����̵�
            x -= 1;
            flip = SDL_FLIP_NONE;
        }
        else if (key_pushed.front() == RIGHT) {//�����̵�
            x += 1;
            flip = SDL_FLIP_HORIZONTAL;
        }
        else if (key_pushed.front() == UP) {//���� �̵�
            y -= 1;
        }
        else if (key_pushed.front() == DOWN) {//�Ʒ��� �̵�
            y += 1;
        }

    }

    //1.2 ��ġ ��ǥ ����
    if (x > screenWidth / GRID_STAGE3 - 2) {
        x = 1;
    }
    else if (x < 1) {
        x = screenWidth / GRID_STAGE3 - 2;
    }
    if (y > screenHeight / GRID_STAGE3 - 2) {
        y = 1;
    }
    else if (y < 1) {
        y = screenHeight / GRID_STAGE3 - 2;
    }
    //1.3 ��ġ �̵�
    magpie->move(x, y);

    //1.4 ��ġ ���� �ð� ������Ʈ
    if (magpie->getInvincible() && (SDL_GetTicks() - magpie->getLastDamageTime() >= 2000)) {
        magpie->setInvincible(false);
    }


    //2. ������ ������Ʈ
    //������ �ӵ� ����
    int time = SDL_GetTicks();
    if (snake->getN() > magpie->getN() && time - lastSpeedUpTime > 10000) { //������ �ӵ��� 5 �̻��̰� 10�ʰ� �����ٸ�
        //cout<<snake->getN()<<endl;
        snake->setN(snake->getN() - 1);
        lastSpeedUpTime = time;
    }
    //������ �̵�
    snake->move(magpie->getX(), magpie->getY());


    //3. ��ź ������Ʈ
    // ���ӽ��� �� 20�ʸ��� bomb �߰� -> �����ϰ� ������ �ֶ� ��ġ �Ѿƿ��� ��
    int currentTime = SDL_GetTicks() - totalPauseTime;
    if ((currentTime - lastBombTime) >= 7000 && bombList.size() < 10) {
        // bomb�� �߰��ϴ� �ڵ带 ���⿡ �ۼ��մϴ�.
        uniform_int_distribution<int> distribution(0, 2);
        bombList.push_back(new Bomb(0, 0, 1, 100, 5, magpie->getX(), magpie->getY(), -20, 50, 75, distribution(generator)));
        lastBombTime = currentTime;

    }

    for (const auto& bomb : bombList) {
        //cout<<i << ": checkCount: " << bomb->getCheckCount() << endl;
        if (bomb->getCheckCount() >= bomb->getLastCount())
            bomb->setCheckCount(bomb->getStartCount()); //�缳��
        bomb->setCheckCount(bomb->getCheckCount() + 1); //ī��Ʈ ���� ����
        if (bomb->getType() == 1) {
            bomb->move(magpie->getX(), magpie->getY()); //Ÿ�� ��ǥ ���� -> 0 ������ ���� �� �����
        }
        else {
            uniform_int_distribution<int> distributionX(1, screenWidth / GRID_STAGE3 - 2);
            uniform_int_distribution<int> distributionY(1, screenHeight / GRID_STAGE3 - 2);
            bomb->move(distributionX(generator), distributionY(generator)); //Ÿ�� ��ǥ ���� -> 0 ������ ���� �� �����
        }


    }

    //3. �浹 Ȯ��
    //3.1 �� �浹 Ȯ��
    if (magpie->isCollidingBell(bell)) {//bell�̶� �ε����ٸ�
        bell->setCount(bell->getCount() + 1); //count���� �ϳ� ����
        Mix_PlayChannel(3, bell_sound, 0);

    }
    //5�ʰ� �����ٸ� �� ��ġ ����
    int current = SDL_GetTicks() - totalPauseTime;
    if (current - bell->getLastEatenTime() > 5000) { // 5�ʰ� �����ٸ�
        bell->spawn();//�� ��ġ ����
        bell->setLastEatenTime(current); // ����� �ð� �ʱ�ȭ
    }

    //3.2 ������ �浹 Ȯ��
    if (magpie->isCollidingSnake(snake)) { //snake�� �ε����ٸ� hp ����
        //Mix_PlayChannel(-1, hit_sound, 0);
        magpie->GetAttackted(snake->getAttackPower());//������ ����

    }


    //3.3 ��ź �浹 Ȯ�� + ���� ���
    for (const auto& bomb : bombList) {
        //�浹 Ȯ��
        if (bomb->getCheckCount() >= bomb->getMiddleCount() && bomb->getCheckCount() < bomb->getLastCount()) {
            if (magpie->isCollidingBomb(bomb)) {
                magpie->GetAttackted(bomb->getAttackPower());
                //Mix_PlayChannel(-1, hit_sound, 0);
            }
        }
        //���� ���
        int b_count = bomb->getCheckCount();
        //ī��Ʈ�� 50�̸� Ÿ�ӽ���
        if (b_count == 0) {
            Mix_PlayChannel(-1, bombPrev_sound, 0);
        }
        else if (b_count == bomb->getMiddleCount()) {
            Mix_PlayChannel(-1, bombAfter_sound, 0);
        }

    }

    //4. ���� ���� Ȯ��
    //���������� �Ѿ�� �� ����� �ִ°� ���� ���⿡ �س��µ�
    //��ġ�� ���� ���ο��� prev�� current ���ؼ� �ؾ� �� �ڿ������� ��
    if (bell->getCount() == 5) {//�� 5�� ������� 
        game_result = 1; //�¸�
        g_current_game_phase = PHASE_STAGE3_ENDING;
        viewedEndings[2][1] = true;
        SDL_Delay(1000);
    }

    if (magpie->getHealth() <= 0) {
        game_result = 2; //����
        g_current_game_phase = PHASE_STAGE3_ENDING;
        viewedEndings[2][0] = true;
        SDL_Delay(1000);
    }


}
void Stage3::Render() {

    //// 1. ��� �׸���.
    // 1.1. Ŀ���� �ܼ� ȭ���� ���� �� �𼭸� �κ����� �ű��. ��ǥ(0, 0)
    // <windows.h>���� �����ϴ� �Լ��� ����Ѵ�

    //// 1.2. ��� �׸���

    // ���� ��� ���۽�Ƽ ����
    if (stage3_status == 1) {
        int time = SDL_GetTicks() - stage3_startTime - totalPauseTime_2;
        if (time < 60000) { // 1�� ���� ���� �Ӿ���
            alpha = time / 60000.0 * 255;
            if (alpha > 70)
                alpha = 70;
        }
    }

    SDL_RenderCopy(g_renderer, bg_texture, NULL, &bg_destination_rect);


    //// 2. ĳ���� �׸���.
    // �� �׸���
    bell_destination_rect.x = bell->getX() * GRID_STAGE3; //�׷��� ��ǥ ����
    bell_destination_rect.y = bell->getY() * GRID_STAGE3;
    SDL_RenderCopy(g_renderer, bell_texture, NULL, &bell_destination_rect);

    // ��ź �׸���
    for (const auto& bomb : bombList) {
        int b_count = bomb->getCheckCount();
        //ī��Ʈ�� 50���� �۰� 0 �̻��ε� ¦���� ? ���
        if (b_count < bomb->getMiddleCount() && b_count >= 0) {
            if (b_count % 2 == 0) {
                bell_destination_rect.x = bomb->getBombRange()[4].x * GRID_STAGE3;
                bell_destination_rect.y = bomb->getBombRange()[4].y * GRID_STAGE3;
                SDL_SetTextureColorMod(bell_texture, 200, 50, 50);
                SDL_RenderCopy(g_renderer, bell_texture, NULL, &bell_destination_rect);
                SDL_SetTextureColorMod(bell_texture, 255, 255, 255);

            }
        }

        //ī��Ʈ�� 100���� 150 ���̸� !���
        else if (b_count >= bomb->getMiddleCount() && b_count < bomb->getLastCount()) {
            bombAttack* b = bomb->getBombRange();

            if (b_count % 3 == 0) {
                int i = (b_count / 3) % 17;
                bomb_source_rect.x = 32 * i; // 0 32 64 
            }

            bomb_destination_rect.x = b[0].x * GRID_STAGE3;
            bomb_destination_rect.y = b[0].y * GRID_STAGE3;

            SDL_RenderCopy(g_renderer, bombAfter_texture, &bomb_source_rect, &bomb_destination_rect);

        }
    }

    //구렁이 그리기 => 머리, 몸통, 꼬리 순서대로 그림
    //머리면 방향에 맞춰 그리고, 꼬리면 이전 방향에 맞춰 그림
    //몸통일 경우 각 노드 사이에 한 번 더 그려주며 이어준다.
    auto snakeList = snake->getSnakeList();
    auto last = --snakeList.end();
    int angle = 0;
    int prevD = LEFT;
    int shiftX = 0, shiftY = 0;

    for (auto it = snakeList.begin(); it != snakeList.end(); ++it) {
        snake_destination_rect.x = (*it)->sX * (GRID_STAGE3); // �׷��� ��ǥ ����
        snake_destination_rect.y = (*it)->sY * (GRID_STAGE3);

        //���� ����
        switch ((*it)->dircetion) {
        case LEFT://��
            angle = -90;
            break;
        case RIGHT://��
            angle = 90;
            break;
        case UP://��
            angle = 0;
            break;
        case DOWN://�Ʒ�
            angle = 180;
            break;
        default:
            break;
        }


        // ���� ��� ����� ��쿡�� ��� �̹����� ����ϰ�, �׷��� ���� ��쿡�� ������ �� �̹����� ����մϴ�.
        if (it == snakeList.begin()) {
            SDL_RenderCopyEx(g_renderer, snakeHead_texture, NULL, &snake_destination_rect, angle, NULL, SDL_FLIP_NONE);
        }
        else if (it == last) {
            switch (prevD) {
            case LEFT://��
                angle = -90;
                break;
            case RIGHT://��
                angle = 90;
                break;
            case UP://��
                angle = -0;
                break;
            case DOWN://�Ʒ�
                angle = 180;

                break;
            default:
                break;
            }
            SDL_RenderCopyEx(g_renderer, snakeTail_texture, NULL, &snake_destination_rect, angle, NULL, SDL_FLIP_NONE);

        }
        else {
            auto prev = std::prev(it); // 이전 노드
            float midX = ((*it)->sX + (*prev)->sX) / 2.0; // 중간 위치 계산
            float midY = ((*it)->sY + (*prev)->sY) / 2.0;

            // 현재 노드와 이전 노드 사이도 추가로 그려 연결 부드럽게
            snake_destination_rect.x = midX * GRID_STAGE3;
            snake_destination_rect.y = midY * GRID_STAGE3;
            SDL_RenderCopyEx(g_renderer, snakeBody_texture, NULL, &snake_destination_rect, angle, NULL, SDL_FLIP_NONE);

            snake_destination_rect.x = (*it)->sX * GRID_STAGE3;
            snake_destination_rect.y = (*it)->sY * GRID_STAGE3;
            SDL_RenderCopyEx(g_renderer, snakeBody_texture, NULL, &snake_destination_rect, angle, NULL, SDL_FLIP_NONE);

        }

        prevD = (*it)->dircetion;
    }


    // ��ġ �׸���
    magpie_destination_rect.x = magpie->getX() * GRID_STAGE3; //�׷��� ��ǥ ����
    magpie_destination_rect.y = magpie->getY() * GRID_STAGE3;

    // ��ġ ������
    if (magpie->getInvincible()) {
        SDL_SetTextureColorMod(magpie_texture, 255, 120, 120); // ���������� ����
    }
    else {
        SDL_SetTextureColorMod(magpie_texture, 255, 255, 255); // ���� �������� ����
    }
    if (!magpie->getInvincible() || SDL_GetTicks() % 500 < 250) { // ���� ���°� �ƴϰų� 0.25�� �������� ����Ÿ�
        SDL_RenderCopyEx(g_renderer, magpie_texture, NULL, &magpie_destination_rect, 0, NULL, flip);
    }



    //��Ʈ ���
    int hp = (int)magpie->getHealth();
    // ��Ʈ ������
    for (int i = 0; i < magpie_init_health/10; i++) {

        heart_destination_rect.x = i * (GRID_STAGE3)+GRID_STAGE3 + 5;
        heart_destination_rect.y = 0 + GRID_STAGE3 + 5;

        if (magpie->getInvincible()) {
            int timeSinceDamage = SDL_GetTicks() - magpie->getLastDamageTime();
            if (timeSinceDamage < 100) {
                // 0.125�ʿ� 0.375�ʿ� ��Ʈ�� ���
                if ((timeSinceDamage % 100) < 20 || (timeSinceDamage % 100) > 80) {
                    heart_destination_rect.y += 10; // y ��ǥ�� ���
                }
            }

        }

        if (hp / 10 != 0) {
            SDL_RenderCopy(g_renderer, heartOne_texture, NULL, &heart_destination_rect);
        }
        else if (hp % 10 == 5) {
            SDL_RenderCopy(g_renderer, heartHalf_texture, NULL, &heart_destination_rect);
        }
        else if (hp <= 0) {
            SDL_RenderCopy(g_renderer, heartZero_texture, NULL, &heart_destination_rect);

        }
        if (hp <= 0)
            continue;
        hp -= 10;
    }

    //���� �� ���� ��� -> ���� �� ��
    UpdateScoreTexture();
    SDL_RenderCopy(g_renderer, myBell_, NULL, &myBell_destination);


    //// 3. ������ �ϼ�.
    // std::cout���� ����� ���� ��, ���� ȭ�鿡 ǥ�õ� �ʰ� ���ۿ� ���� �ִ� ���� �ִٸ�, ��� ȭ�鿡 ��µǵ��� �Ѵ�.
    //���� �̹��� ����
    SDL_SetTextureAlphaMod(red_texture, alpha);
    SDL_RenderCopy(g_renderer, red_texture, NULL, &bg_destination_rect);
    SDL_RenderCopy(g_renderer, frame_texture, NULL, &frame_destination);

    if (stage3_status != 1) {//�Ͻ����� ���� Ȥ�� ��� ����
        SDL_RenderCopy(g_renderer, wait_texture, NULL, &bg_destination_rect);
        switch (stage3_status)
        {
        case 0:
            //��� ����
            SDL_RenderCopy(g_renderer, ready_texture, NULL, &readyCount_destination);
            break;
        case 2:
            //��ư ����

            SDL_RenderCopy(g_renderer, button_continue, NULL, &continue_destination_rect);
            SDL_RenderCopy(g_renderer, button_main, NULL, &main_destination_rect);
            break;
        default:
            break;
        }
    }
    SDL_RenderPresent(g_renderer);

}


void Stage3::Reset() {
    //��ü �ʱ�ȭ
    delete bell;
    delete magpie;
    delete snake;
    for (const auto& bomb : bombList) {
        delete bomb;
    }
    bombList.clear();

    //a. �� ����
    uniform_int_distribution<int> distributionX(1, screenWidth / GRID_STAGE3 - 2);
    uniform_int_distribution<int> distributionY(1, screenHeight / GRID_STAGE3 - 2);

    bell = new Bell(distributionX(generator), distributionY(generator), 0, 0);

    if (is_hard) {
        //b. ��ġ ����
        magpie = new Magpie(3, 3, 1, 30, 0, 3); //(0,0)���� ����, speed�� 1,hp�� 30���� ����
        //c. ������ ����
        snake = new Snake(0, 0, 1, 100, 10, magpie->getX(), magpie->getY(), 8);
        //d. ��ź ����
        bombList.push_front(new Bomb(0, 0, 1, 100, 5, magpie->getX(), magpie->getY(), -20, 50, 75, 0));
    }
    else {
        //b. ��ġ ����
        magpie = new Magpie(3, 3, 1, 50, 0, 5); //(0,0)���� ����, speed�� 1,hp�� 50���� ����
        //c. ������ ����
        snake = new Snake(0, 0, 1, 100, 10, magpie->getX(), magpie->getY(), 8);
        //d. ��ź ����
        bombList.push_front(new Bomb(0, 0, 1, 100, 5, magpie->getX(), magpie->getY(), -20, 50, 75, 0));
    }

    magpie_init_health = magpie->getHealth();

    //2. ��Ÿ ����
    f_state = STOP;//����Ű �� ����
    stop = true; //���� ��Ȳ���� �ʱ�ȭ
    key_pushed.clear();//Ű ���� �ʱ�ȭ

    flip = SDL_FLIP_HORIZONTAL;

    lastSpeedUpTime = 0;
    alpha = 0;
    stage3_status = 0;

    //���� ���
    Mix_HaltChannel(-1);//��� ���� ����

    //���� �ٽ� ����
    Mix_FadeInMusic(background_music, -1, 2000);//�뷡 ���̵������� �ٷ� ����


    //�Ͻ����� �ð� �ʱ�ȭ
    totalPauseTime = 0;
    stage3_startTime = 0;
    lastBombTime = 0;
    pauseStartTime = 0;
    totalPauseTime_2 = 0;
}


Stage3::~Stage3() {
    //�̹��� �ؽ��� ����
    SDL_DestroyTexture(snakeHead_texture);
    SDL_DestroyTexture(snakeBody_texture);
    SDL_DestroyTexture(snakeTail_texture);
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyTexture(bell_texture);
    SDL_DestroyTexture(magpie_texture);
    SDL_DestroyTexture(heartZero_texture);
    SDL_DestroyTexture(heartHalf_texture);
    SDL_DestroyTexture(heartOne_texture);
    SDL_DestroyTexture(bombAfter_texture);
    SDL_DestroyTexture(red_texture);
    SDL_DestroyTexture(ready_texture);
    SDL_DestroyTexture(wait_texture);
    SDL_DestroyTexture(button_continue);
    SDL_DestroyTexture(button_main);
    SDL_DestroyTexture(myBell_);


    //���� ����
    Mix_FreeMusic(background_music);
    Mix_FreeChunk(bell_sound);

    Mix_FreeChunk(bombPrev_sound);
    Mix_FreeChunk(bombAfter_sound);
    Mix_FreeChunk(button_sound);



    //��ü ����
    delete bell;
    delete magpie;
    delete snake;
    for (const auto& bomb : bombList) {
        delete bomb;
    }
    bombList.clear();

}