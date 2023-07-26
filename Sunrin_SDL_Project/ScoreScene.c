#include "pch.h"
#include "ScoreScene.h" // include!

// 필요한 변수는 전역 변수로 전언해서 사용합니다.
typedef struct ScoreScene {
	// 씬에서 전역적으로 사용할 변수는 구조체로 랩핑해서 사용한다!
	int quit;
	TTF_Font* font;
	char str[50];
} ScoreScene;

ScoreScene scoreScene;

void ScoreScene_Init()
{
	SDL_Renderer* renderer = Get_Renderer();

	scoreScene.font = TTF_OpenFont("./resources/Pretendard.otf", 48);
}

void ScoreScene_Event()
{
	// SDL 이벤트를 확인하기 위한 객체 생성
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		// event의 타입이 SDL_QUIT면 트리거를 활성화 합니다.
		if (event.type == SDL_QUIT) {
			scoreScene.quit = EXIT_GAME;
			break;
		}
	}
}

void ScoreScene_Update()
{
	// 오브젝트의 이동을 처리합니다.
	double dt = getDeltaTime();

	// 마우스 키가 눌렸는지 체크합니다.
	if (getKeyState(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		scoreScene.quit = MAIN_SCENE;
	}
}

void ScoreScene_Render()
{
	SDL_Renderer* renderer = Get_Renderer();

	// 파란색 배경을 칠합니다.
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	SDL_Color textureColor = { 255, 255, 255, 255 };

	drawTextCenter(renderer, scoreScene.font, scoreScene.str, SCREEN_WIDTH / 2, 200, textureColor);
	drawTextCenter(renderer, scoreScene.font, u8"space 바를 눌러 메인 화면으로...", SCREEN_WIDTH / 2, 650, textureColor);

	SDL_RenderPresent(renderer);
}

void ScoreScene_Release()
{
	// 사용한 자료를 해제합니다.
	TTF_CloseFont(scoreScene.font);
}

int ScoreScene_Loop()
{
	// 필요한 변수를 초기화 합니다.
	scoreScene.quit = SCENE_LOOP;

	memset(scoreScene.str, 0, sizeof(scoreScene.str));

	sprintf_s(scoreScene.str, sizeof(scoreScene.str), u8"최종 스코어: %d", getGameScore());

	// 루프를 진행합니다.
	while (scoreScene.quit == SCENE_LOOP) {
		// 유틸 함수를 업데이트 합니다.
		// 이를 씬별로 수행해야, 여러 함수들을 정상적으로 사용할 수 있습니다.
		Update_Util();

		ScoreScene_Event();
		ScoreScene_Update();
		ScoreScene_Render();
	}

	// 씬의 정보를 확인해서 내보냅니다.
	return scoreScene.quit;
}
