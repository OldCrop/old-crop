#include "Phase_stage2.h"
#include <Windows.h>
#include <SDL_image.h> // Add this line to include the SDL_image library
#include <iomanip>

using namespace std;

extern default_random_engine generator;


//미로

//배경 텍스쳐

SDL_Rect stage2_bg_source_rect;

Stage2::Stage2() {
    
    uniform_int_distribution<int> distributionX(0, SCREEN_WIDTH);
    uniform_int_distribution<int> distributionY(0, SCREEN_HEIGHT);
    rabbit = new Rabbit(distributionX(generator), distributionY(generator), 1, 3);
    turtle = new Turtle(1, 1, 0 ,3 , 0);
    coral = new Coral(0, 0, 0, 0, 1);

    // 배경 텍스쳐 로드
    SDL_Surface* stage2_bg_surface = IMG_Load("../../resources/stage2/stage2_bg.jpg");
    stage2_bg_texture = SDL_CreateTextureFromSurface(g_renderer, stage2_bg_surface);
    SDL_FreeSurface(stage2_bg_surface);
    stage2_bg_source_rect = { 0, 0, 500, 500 };
    stage2_bg_destination_rect = { 0, 0, 600, 600 };

    //거북이 텍스쳐 로드
    SDL_Surface*  turtle_surface = IMG_Load("../../resources/stage2/stage2_turtle.png");
    turtle_texture = SDL_CreateTextureFromSurface(g_renderer, turtle_surface);
    SDL_FreeSurface(turtle_surface);
    turtle_destination_rect.x = turtle->getX() * GRID;
    turtle_destination_rect.y = turtle->getY() * GRID;
    turtle_destination_rect.w = GRID;
    turtle_destination_rect.h = GRID;

    //토끼 텍스쳐 로드
    SDL_Surface*  rabbit_surface = IMG_Load("../../resources/stage2/stage2_rabbit.png");
    rabbit_texture = SDL_CreateTextureFromSurface(g_renderer, rabbit_surface);
    SDL_FreeSurface(rabbit_surface);
    rabbit_destination_rect.x = rabbit->getX() * GRID;
    rabbit_destination_rect.y = rabbit->getY() * GRID;
    rabbit_destination_rect.w = GRID;
    rabbit_destination_rect.h = GRID;

    //산호 텍스쳐 로드
    SDL_Surface*  coral_surface = IMG_Load("../../resources/stage2/stage2_coral2.png");
    coral_texture = SDL_CreateTextureFromSurface(g_renderer, coral_surface);
    SDL_FreeSurface(coral_surface);
    coral_destination_rect.x = coral->getX() * GRID;
    coral_destination_rect.y = coral->getY() * GRID;
    coral_destination_rect.w = GRID;
    coral_destination_rect.h = GRID;

    //간 텍스쳐 로드
    SDL_Surface* gan_surface = IMG_Load("../../resources/stage2/stage2_gan.png");
    gan_texture = SDL_CreateTextureFromSurface(g_renderer, gan_surface);
    SDL_FreeSurface(gan_surface);
    gan_destination_rect.x = 0;
    gan_destination_rect.y = 0;
    gan_destination_rect.w = GRID;
    gan_destination_rect.h = GRID;

    //하트0 텍스쳐 로드
    SDL_Surface* heart0_surface = IMG_Load("../../resources/stage2/stage2_heart0.png");
    heart0_texture = SDL_CreateTextureFromSurface(g_renderer, heart0_surface);
    SDL_FreeSurface(heart0_surface);
    heart0_destination_rect.x = 0;
    heart0_destination_rect.y = 0;
    heart0_destination_rect.w = GRID;
    heart0_destination_rect.h = GRID;

    //하트2 텍스쳐 로드
    SDL_Surface* heart2_surface = IMG_Load("../../resources/stage2/stage2_heart2.png");
    heart2_texture = SDL_CreateTextureFromSurface(g_renderer, heart2_surface);
    SDL_FreeSurface(heart2_surface);
    heart2_destination_rect.x = 0;
    heart2_destination_rect.y = 0;
    heart2_destination_rect.w = GRID;
    heart2_destination_rect.h = GRID;


    f_state = -1;
    stop = true;
    for (int i = 0; i < 4; i++) {
        f_list[i] = false;
    }
    game_result = 0;
    system("cls");
}

void Stage2::HandleEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            g_flag_running = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_LEFT) {
                f_state = 0;
                f_list[f_state] = true;
                stop = false;
            }
            else if (event.key.keysym.sym == SDLK_RIGHT) {
                f_state = 1;
                f_list[f_state] = true;
                stop = false;
            }
            else if (event.key.keysym.sym == SDLK_UP) {
                f_state = 2;
                f_list[f_state] = true;
                stop = false;
            }
            else if (event.key.keysym.sym == SDLK_DOWN) {
                f_state = 3;
                f_list[f_state] = true;
                stop = false;
            }
            break;
        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_LEFT) {
                f_list[0] = false;
            }
            else if (event.key.keysym.sym == SDLK_RIGHT) {
                f_list[1] = false;
            }
            else if (event.key.keysym.sym == SDLK_UP) {
                f_list[2] = false;
            }
            else if (event.key.keysym.sym == SDLK_DOWN) {
                f_list[3] = false;
            }

            if (f_list[0])
                f_state = 0;
            if (f_list[1])
                f_state = 1;
            if (f_list[2])
                f_state = 2;
            if (f_list[3])
                f_state = 3;
            if (f_list[0] != true && f_list[1] != true && f_list[2] != true && f_list[3] != true)
                stop = true;

            break;
        }
    }
}
void Stage2::Update() {
    if (!stop) {
        int x = turtle->getX();
        int y = turtle->getY();

        if (f_list[0]) {
            x -= 1;
            f_list[0] = false;
        }
        else if (f_list[1]) {
            x += 1;
            f_list[1] = false;
        }
        else if (f_list[2]) {
            y -= 1;
            f_list[2] = false;
        }
        else if (f_list[3]) {
            y += 1;
            f_list[3] = false;
        }

        if (x >= SCREEN_WIDTH) x = SCREEN_WIDTH - 1;
        if (x < 0) x = 0;
        if (y >= SCREEN_HEIGHT) y = SCREEN_HEIGHT - 1;
        if (y < 0) y = 0;

        turtle->setXY(x, y);
    }

    //충돌처리
    if (turtle->isCollision_Rabbit(rabbit)) {
        rabbit->setCount(rabbit->getCount() + 1);
        rabbit->spawn(); 
    }
    if (turtle->isCollision_Coral(coral)) {
        turtle->GetAttackted(1);
    }
    if (rabbit->getCount() == 5) {
        game_result = 1;
    }
    if (turtle->getHealth() <= 0) {
        game_result = 2;
    }
}

void Stage2::Render() {
    //배경 그리기
    SDL_RenderCopy(g_renderer, stage2_bg_texture, &stage2_bg_source_rect, &stage2_bg_destination_rect);
    

    COORD cur;
    cur.X = 0;
    cur.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);

    //0과 1로 20*20미로 maze위에, 산호는 1의 위치에 텍스쳐 그리기
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            if (Maze::maze[i][j] == 0) {
                cout << " ";
            }
            else if (Maze::maze[i][j] == 1) {
                coral_destination_rect.x = j * GRID;
                coral_destination_rect.y = i * GRID;
                SDL_RenderCopy(g_renderer, coral_texture, NULL, &coral_destination_rect);
                cout << " ";
            }
        }
        cout << endl;
    }
    
    //토끼개수 간 그리기
    for (int i = 0; i < rabbit->getCount(); i++) {
		gan_destination_rect.x = GRID*21 +i * GRID;
		gan_destination_rect.y = GRID+0;
		SDL_RenderCopy(g_renderer, gan_texture, NULL, &gan_destination_rect);
	}
    
      


    //캐릭터그리기
    //토끼 maze위에 0에만 텍스쳐 그려지도록
    rabbit_destination_rect.x = rabbit->getX() * GRID;
    rabbit_destination_rect.y = rabbit->getY() * GRID;
    SDL_RenderCopy(g_renderer, rabbit_texture, NULL, &rabbit_destination_rect);

    
    
    
    
    //거북이 그리기
    
    turtle_destination_rect.x = turtle->getX() * GRID;
    turtle_destination_rect.y = turtle->getY() * GRID;
    SDL_RenderCopy(g_renderer, turtle_texture, NULL, &turtle_destination_rect);
        
    
    //거북이 체력 그리기 
    for (int i = 0; i < turtle->getHealth(); i++) {
		heart2_destination_rect.x = GRID*21+i * GRID;
		heart2_destination_rect.y = 0;
		SDL_RenderCopy(g_renderer, heart2_texture, NULL, &heart2_destination_rect);
	}
   

    //게임 결과 출력 
    cur.X = SCREEN_WIDTH + 10;
    cur.Y = 5;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
    if (game_result == 1) {
        cout << "---승리---";
        cout.flush();
    }
    else if (game_result == 2) {
        cout << "---패배---";
        cout.flush();
    }

    cout.flush();

    SDL_RenderPresent(g_renderer);

}
void Stage2::Reset() {//재시작시 상태

}


Stage2::~Stage2() {
    delete turtle;
    delete rabbit;
    delete coral;


}