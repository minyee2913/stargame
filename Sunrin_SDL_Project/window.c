#include "pch.h"
#include "window.h"

// 윈도우 객체를 담을 포인터를 정의합니다.
SDL_Window* window = NULL;

// 렌더링이 진행될 포인터를 정의합니다.
SDL_Surface* renderer = NULL;


int Init_Program()
{
    // SDL 초기화
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("SDL 초기화에 실패했습니다: %s\n", SDL_GetError());
        return 1;
    }

    // 이미지 초기화
    if (initImage() != 0) {
        SDL_Quit();
        return 1;
    }

    // 오디오 초기화를 진행합니다.
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096)) {
        printf("Audio 초기화에 실패했습니다: %s \n", Mix_GetError());
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // 폰트 라이브러리 초기화를 진행합니다.
    if (TTF_Init() < 0) {
        printf("폰트를 초기화할 수 없습니다: %s \n", TTF_GetError());
        IMG_Quit();
        SDL_Quit();
        Mix_Quit();
        return 1;
    }

    // 윈도우 생성
    // SDL_CreateWindow(u8"SDL 프로젝트", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0)
    // 생성한 창의 title, x, y, w, h, flag를 설정함.
    // Tips: u8"" 은 텍스트를 UTF-8 형식으로 인코딩 합니다.
    window = SDL_CreateWindow(u8"SDL 프로젝트", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window) {
        printf("윈도우를 생성할 수 없습니다: %s\n", SDL_GetError());
        IMG_Quit();
        Mix_Quit();
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // 렌더러 생성
    // 렌더링 작업을 수행할 렌더러를 생성합니다.
    // 창에서 렌더러를 생성합니다.
    // SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // -1: 가장 첫번째로 사용 가능한 그래픽 드라이버 사용
    // SDL_RENDERER_ACCELERATED: 하드웨어 가속
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("렌더러를 생성할 수 없습니다: %s\n", SDL_GetError());
        IMG_Quit();
        Mix_Quit();
        TTF_Quit();
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 타이머 초기화
    initTimer();

    // 랜덤 함수 초기화
    srand(time(NULL));

    return 0;
}

void Update_Util()
{
    // 입력 함수를 업데이트 합니다.
    updateKeyState();
    updateMouseState();

    // 타이머 함수를 업데이트 합니다.
    updateTimer();
}

SDL_Window* Get_Window()
{
    if (window == NULL) {
        printf("Window가 초기화되지 않았습니다.");
        return NULL;
    }

    return window;
}

SDL_Surface* Get_Renderer()
{
    if (renderer == NULL) {
        printf("Renderer가 초기화되지 않았습니다.");
        return NULL;
    }

    return renderer;
}

void Release_Program()
{
    // 	window, renderer, library 등을 해제합니다.
    // 창을 다 띄우고 나서는 사용한 메모리를 해제해주어야 합니다.
    // 만들어준 렌더러, 윈도우를 삭제하고, SDL도 종료시킵니다.
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}