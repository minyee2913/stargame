#pragma once
#include <SDL_ttf.h>

// drawText
// renderer: 그릴 렌더러
// font: 그릴 폰트
// str: 그릴 텍스트
void drawText(SDL_Renderer* renderer, TTF_Font* font, const char* str, int x, int y, SDL_Color c);

void drawTextCenter(SDL_Renderer* renderer, TTF_Font* font, const char* str, int x, int y, SDL_Color c);

// 텍스트의 크기를 조절할 수 있습니다.
// ratio_x, ratio_y 모두 1.0 이면, 원본 입니다.
// ratio_x, ratio_y 모두 0.5 이면, 절반 크기로 출력됩니다.
void drawTextCenterWRatio(SDL_Renderer* renderer, TTF_Font* font, const char* str, int x, int y, SDL_Color c, double ratio_x, double ratio_y);