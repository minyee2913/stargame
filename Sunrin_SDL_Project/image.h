#pragma once
#include <SDL_image.h>

// SDL_image 라이브러리를 초기화 합니다.
int initImage();

// 이미지를 불러옵니다.
// renderer: 이미지를 출력할 타겟 렌더러
// file: 불러올 파일 경로
SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* file);

// 이미지를 출력합니다.
// renderer: 이미지를 출력할 타겟 렌더러
// x: 그릴 이미지의 x 위치
// y: 그릴 이미지의 y 위치
// texture: 그릴 이미지의 정보
void drawTexture(SDL_Renderer* renderer, int x, int y, SDL_Texture* texture);

// 이미지를 출력합니다.
// renderer: 이미지를 출력할 타겟 렌더러
// x: 그릴 이미지의 x 위치
// y: 그릴 이미지의 y 위치
// widthRatio: 원본 텍스처에서 렌더러에 그릴 가로 비율입니다.
// heightRatio: 원본 텍스처에서 렌더러에 그릴 세로 비율입니다.
// texture: 그릴 이미지의 정보
// example: widthRatio, heightRatio가 0.5이면 원본 텍스쳐의 0.5배 크기만큼 렌더링을 진행합니다.
void drawTextureWithRatio(SDL_Renderer* renderer, int x, int y, double widthRatio, double heightRatio, SDL_Texture* texture);

// 이미지를 출력합니다.
// renderer: 이미지를 출력할 타겟 렌더러
// rect: 이미지를 출력할 위치와 이미지의 크기
// texture: 그릴 이미지의 정보
void drawTextureWithRect(SDL_Renderer* renderer, SDL_Rect* rect, SDL_Texture* texture);

// 타겟 이미지의 width, height 정보를 가져옵니다.
// 기존의 SDL_QueryTexture 코드를 랩핑한 상태입니다.
void getTextureSize(SDL_Texture* texture, int* x, int* y);