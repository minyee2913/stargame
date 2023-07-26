#pragma once
#include <SDL.h>

// 씬 간의 연결을 위해서, 아래에 씬 번호를 정의합니다.
#define SCENE_LOOP		-2

#define EXIT_GAME		-1
#define GAME_SCENE		0
#define SCORE_SCENE		1
#define MAIN_SCENE		2

// 화면의 크기를 정의합니다.
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


// 프로그램의 초기화는 여기서 진행합니다.
// 라이브러리 초기화 또한, 해당 함수에서 실행됩니다.
// 따라서, 다른 위치에서 라이브러리 초기화 함수를 실행할 필요가 없습니다.
int Init_Program();

// 유틸리티 등을 업데이트 합니다.
void Update_Util();

// 필요한 자료를 받아올 수 있는 Getter를 정의합니다.
SDL_Window* Get_Window();

SDL_Surface* Get_Renderer();

// 사용한 자료의 릴리즈를 진행합니다.
void Release_Program();