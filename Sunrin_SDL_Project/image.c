#include "pch.h"
#include "image.h"

int initImage()
{
	// IMG_INIT을 초기화 하기 위한 플래그 입니다.
	// 불러올 이미지 종류에 대한 정의입니다.
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;

	// IMG_INIT은 초기화된 플래그에 대한 정보를 리턴합니다.
	// 따라서 & 연산자로 정상적으로 초기화 되었는지 파악합니다.
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image를 초기화 하지 못했습니다! \nSDL_image Error: %s\n", IMG_GetError());
		return -1;
	}

    return 0;
}

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* file)
{
	SDL_Surface* surface;
	SDL_Texture* texture;

	// 파일을 읽어 SDL_Surface로 생성합니다.
	surface = IMG_Load(file);
	if (surface == NULL) {
		printf("파일을 읽을 수 없습니다: %s\n", file);
		return NULL;
	}

	// SDL_CreateTextureFromSurface를 통해 SDL_Texture를 생성합니다.
	// 주어진 Surface로 새로운 Texture를 생성합니다.
	// 화면에 그릴 renderer가 필요합니다.
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL) {
		printf("texture를 생성할 수 없습니다.\n");
	}

	// 이제 Texture를 만들었으니, 불필요한 surface는 해제합니다.
	SDL_FreeSurface(surface);

	return texture;
}

void drawTexture(SDL_Renderer* renderer, int x, int y, SDL_Texture* texture)
{
	SDL_Rect src;
	SDL_Rect dst;

	src.x = 0;
	src.y = 0;
	// 텍스쳐의 속성(format, width, height 등)을 가져옵니다.
	SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);

	// 렌더러에 그릴 텍스쳐의 위치 정보를 정의합니다.
	dst.x = x;
	dst.y = y;
	dst.w = src.w;
	dst.h = src.h;

	// dst에 정의한 위치 정보에 texture를 그립니다.
	SDL_RenderCopy(renderer, texture, NULL, &dst);
}

void drawTextureWithRatio(SDL_Renderer* renderer, int x, int y, double widthRatio, double heightRatio, SDL_Texture* texture)
{
	SDL_Rect src;
	SDL_Rect dst;

	src.x = 0;
	src.y = 0;
	// 텍스쳐의 속성(format, width, height 등)을 가져옵니다.
	SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);

	// 렌더러에 그릴 텍스쳐의 위치 정보를 정의합니다.
	// 그릴 비율을 통해 크기를 조절합니다.
	dst.x = x;
	dst.y = y;
	dst.w = (int)(src.w * widthRatio);
	dst.h = (int)(src.h * heightRatio);

	// dst에 정의한 위치 정보에 texture를 그립니다.
	SDL_RenderCopy(renderer, texture, NULL, &dst);
}

void drawTextureWithRect(SDL_Renderer* renderer, SDL_Rect* rect, SDL_Texture* texture)
{
	// dst에 정의한 위치 정보에 texture를 그립니다.
	SDL_RenderCopy(renderer, texture, NULL, rect);
}

void getTextureSize(SDL_Texture* texture, int* x, int* y)
{
	SDL_QueryTexture(texture, NULL, NULL, x, y);
}
