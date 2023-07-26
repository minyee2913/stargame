#pragma once
#include <SDL.h>

int checkCollision(SDL_Rect rect1, SDL_Rect rect2);

int checkCollisionWithPoint(SDL_Rect rect, int x, int y);