#include "pch.h"
#include "MainScene.h" // include!

// 필요한 변수는 전역 변수로 전언해서 사용합니다.
typedef struct MainScene {
	// 씬에서 전역적으로 사용할 변수는 구조체로 랩핑해서 사용한다!
	int quit;

	// 사용할 이미지의 포인터를 의미합니다.
	SDL_Texture* img_startButton;

	// 충돌을 감지하기 위한 버튼 rect 정의
	SDL_Rect rect_startButton;
	SDL_Rect rect_exitButton;

	TTF_Font* font;

	// 충돌을 감지하기 위한 렉트에는
	// 이미지의 크기(width, height)와 이미지의 위치(x, y)가 들어 있어야 한다.
} MainScene;
MainScene mainScene;

void MainScene_Init()
{
	SDL_Renderer* renderer = Get_Renderer();

	// 사용할 이미지를 파일에서 불러옵니다.
	mainScene.font = TTF_OpenFont("./resources/Pretendard.otf", 48);
	
	mainScene.img_startButton = loadTexture(renderer,
		"./resources/start.jpg");

	// rect_startButton을 초기화 한다.
	getTextureSize(mainScene.img_startButton,
		&mainScene.rect_startButton.w, &mainScene.rect_startButton.h);
	mainScene.rect_startButton.x = 50;
	mainScene.rect_startButton.y = 100;
}

void MainScene_Event()
{
	// SDL 이벤트를 확인하기 위한 객체 생성
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		// event의 타입이 SDL_QUIT면 트리거를 활성화 합니다.
		if (event.type == SDL_QUIT) {
			mainScene.quit = EXIT_GAME;
			break;
		}
	}
}

void MainScene_Update()
{
	// 오브젝트의 이동을 처리합니다.
	double dt = getDeltaTime();

	// 마우스 위치를 가져옵니다.
	int mouseX, mouseY = 0;
	getCurrentMousePos(&mouseX, &mouseY);

	// 마우스 키가 눌렸는지 체크합니다.
	if (getButtonState(SDL_BUTTON_LEFT) == KEY_DOWN) {
		// startButton이 눌렸는지 체크한다.
		if (checkCollisionWithPoint(mainScene.rect_startButton, mouseX, mouseY)) {
			printf("GameScene으로 이동합니다. \n");
			mainScene.quit = GAME_SCENE;
		}
	}
}

void MainScene_Render()
{
	SDL_Renderer* renderer = Get_Renderer();
	// 배경을 칠합니다.
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	drawTexture(renderer, 50, 100, mainScene.img_startButton);

	SDL_Color textureColor = { 255, 255, 255, 255 };
	drawTextCenter(renderer, mainScene.font, u8". . .", SCREEN_WIDTH / 2, 350, textureColor);
	drawTextCenter(renderer, mainScene.font, u8"- music -", SCREEN_WIDTH / 2, 450, textureColor);
	drawTextCenter(renderer, mainScene.font, u8"Cjbeards - Burning In Hell", SCREEN_WIDTH / 2, 500, textureColor);

	SDL_RenderPresent(renderer);
}

void MainScene_Release()
{
	SDL_DestroyTexture(mainScene.img_startButton);
}

int MainScene_Loop()
{
	// 필요한 변수를 초기화 합니다.
	mainScene.quit = SCENE_LOOP;

	Mix_HaltMusic();
	Mix_HaltChannel(-1);

	// 루프를 진행합니다.
	while (mainScene.quit == SCENE_LOOP) {
		// 유틸 함수를 업데이트 합니다.
		// 이를 씬별로 수행해야, 여러 함수들을 정상적으로 사용할 수 있습니다.
		Update_Util();

		MainScene_Event();
		MainScene_Update();
		MainScene_Render();
	}

	// 씬의 정보를 확인해서 내보냅니다.
	return mainScene.quit;
}
