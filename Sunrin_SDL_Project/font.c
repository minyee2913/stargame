#include "pch.h"
#include "font.h"
#include <SDL.h>

void drawText(SDL_Renderer* renderer, TTF_Font* font, const char* str, int x, int y, SDL_Color c)
{
    // 폰트를 렌더링 해서 Surface에 그립니다.
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, str, c);

    // SDL_Texture로 변환하여, renderer에 그릴 수 있도록 준비합니다.
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    // 텍스트의 위치를 지정합니다.
    SDL_Rect r = { x, y, surface->w, surface->h };

    // 더 이상 사용하지 않는 surface는 제거합니다.
    SDL_FreeSurface(surface);

    // renderer에 texture의 정보를 복사합니다.
    SDL_RenderCopy(renderer, texture, NULL, &r);

    // 정보를 복사한 texture의 정보는 더이상 필요하지 않습니다.
    // 제거!
    SDL_DestroyTexture(texture);
}

void drawTextCenter(SDL_Renderer* renderer, TTF_Font* font, const char* str, int x, int y, SDL_Color c)
{
    // 폰트를 렌더링 해서 Surface에 그립니다.
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, str, c);

    // SDL_Texture로 변환하여, renderer에 그릴 수 있도록 준비합니다.
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    // 텍스트의 위치를 지정합니다.
    SDL_Rect r = { x - surface->w/2, y - surface->h/2, surface->w, surface->h };

    // 더 이상 사용하지 않는 surface는 제거합니다.
    SDL_FreeSurface(surface);

    // renderer에 texture의 정보를 복사합니다.
    SDL_RenderCopy(renderer, texture, NULL, &r);

    // 정보를 복사한 texture의 정보는 더이상 필요하지 않습니다.
    // 제거!
    SDL_DestroyTexture(texture);
}

void drawTextCenterWRatio(SDL_Renderer* renderer, TTF_Font* font, const char* str, int x, int y, SDL_Color c, double ratio_x, double ratio_y)
{
    // 폰트를 렌더링 해서 Surface에 그립니다.
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, str, c);

    // SDL_Texture로 변환하여, renderer에 그릴 수 있도록 준비합니다.
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    int w = surface->w * ratio_x;
    int h = surface->h * ratio_y;

    // 텍스트의 위치를 지정합니다.
    SDL_Rect r = { x - w / 2, y - h / 2, w, h };

    // 더 이상 사용하지 않는 surface는 제거합니다.
    SDL_FreeSurface(surface);

    // renderer에 texture의 정보를 복사합니다.
    SDL_RenderCopy(renderer, texture, NULL, &r);

    // 정보를 복사한 texture의 정보는 더이상 필요하지 않습니다.
    // 제거!
    SDL_DestroyTexture(texture);
}
