#pragma once
#include <SDL.h>

// drawFilledRectangle: 사각형을 그립니다.
// x, y: 그릴 좌표
// w, h: 그릴 크기
// r, g, b: 그릴 색상
void drawFilledRectangle(SDL_Surface* renderer,
	int x, int y, int w, int h,
	Uint8 r, Uint8 g, Uint8 b, Uint8 a);

// 삼각형 그리는 함수
void drawFilledTriangle(SDL_Surface* renderer,
	int x1, int y1,		// 첫 번째 점의 좌표
	int x2, int y2,		// 두 번째 점의 좌표
	int x3, int y3,		// 세 번째 점의 좌표
	Uint8 r, Uint8 g, Uint8 b, Uint8 a);

// 원 그리는 함수
void drawFilledCircle(SDL_Surface* renderer,
	int x, int y,
	int radius,
	Uint8 r, Uint8 g, Uint8 b, Uint8 a);