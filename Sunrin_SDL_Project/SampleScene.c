#include "pch.h"
#include "SampleScene.h" // include!

// 필요한 변수는 전역 변수로 전언해서 사용합니다.
typedef struct SampleScene {
	// 씬에서 전역적으로 사용할 변수는 구조체로 랩핑해서 사용한다!
	int quit;
} SampleScene;
SampleScene sampleScene;

void SampleScene_Init()
{
	SDL_Renderer* renderer = Get_Renderer();
}

void SampleScene_Event()
{
	// SDL 이벤트를 확인하기 위한 객체 생성
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		// event의 타입이 SDL_QUIT면 트리거를 활성화 합니다.
		if (event.type == SDL_QUIT) {
			sampleScene.quit = EXIT_GAME;
			break;
		}
	}
}

void SampleScene_Update()
{
	// 오브젝트의 이동을 처리합니다.
	double dt = getDeltaTime();

	// 마우스 키가 눌렸는지 체크합니다.
	if (getButtonState(SDL_BUTTON_LEFT) == KEY_DOWN) {
		
	}
}

void SampleScene_Render()
{
	SDL_Renderer* renderer = Get_Renderer();

	// 파란색 배경을 칠합니다.
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}

void SampleScene_Release()
{
	// 사용한 자료를 해제합니다.

}

int SampleScene_Roop()
{
	// 필요한 변수를 초기화 합니다.
	sampleScene.quit = SCENE_LOOP;

	// 루프를 진행합니다.
	while (sampleScene.quit == SCENE_LOOP) {
		// 유틸 함수를 업데이트 합니다.
		// 이를 씬별로 수행해야, 여러 함수들을 정상적으로 사용할 수 있습니다.
		Update_Util();

		SampleScene_Event();
		SampleScene_Update();
		SampleScene_Render();
	}

	// 씬의 정보를 확인해서 내보냅니다.
	return sampleScene.quit;
}
