#include "pch.h"
#include "timer.h"

Uint64 beforeTicks;
Uint64 currentTicks;
Uint64 elapsedTicks;
double deltaTime;

void initTimer()
{
	beforeTicks = SDL_GetPerformanceCounter();
	currentTicks = SDL_GetPerformanceCounter();
	elapsedTicks = 0;
	deltaTime = 0;
}

// 프레임 별 시간 간격은 한 번만 구합니다.
void updateTimer()
{
	beforeTicks = currentTicks;
	currentTicks = SDL_GetPerformanceCounter();
	elapsedTicks = currentTicks - beforeTicks;

	// 가변 프레임에 대응
	deltaTime = (double)elapsedTicks / SDL_GetPerformanceFrequency();
}

double getDeltaTime()
{
	return deltaTime;
}
