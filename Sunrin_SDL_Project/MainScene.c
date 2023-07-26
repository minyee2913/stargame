#include "pch.h"
#include "MainScene.h" // include!

// �ʿ��� ������ ���� ������ �����ؼ� ����մϴ�.
typedef struct MainScene {
	// ������ ���������� ����� ������ ����ü�� �����ؼ� ����Ѵ�!
	int quit;

	// ����� �̹����� �����͸� �ǹ��մϴ�.
	SDL_Texture* img_startButton;

	// �浹�� �����ϱ� ���� ��ư rect ����
	SDL_Rect rect_startButton;
	SDL_Rect rect_exitButton;

	TTF_Font* font;

	// �浹�� �����ϱ� ���� ��Ʈ����
	// �̹����� ũ��(width, height)�� �̹����� ��ġ(x, y)�� ��� �־�� �Ѵ�.
} MainScene;
MainScene mainScene;

void MainScene_Init()
{
	SDL_Renderer* renderer = Get_Renderer();

	// ����� �̹����� ���Ͽ��� �ҷ��ɴϴ�.
	mainScene.font = TTF_OpenFont("./resources/Pretendard.otf", 48);
	
	mainScene.img_startButton = loadTexture(renderer,
		"./resources/start.jpg");

	// rect_startButton�� �ʱ�ȭ �Ѵ�.
	getTextureSize(mainScene.img_startButton,
		&mainScene.rect_startButton.w, &mainScene.rect_startButton.h);
	mainScene.rect_startButton.x = 50;
	mainScene.rect_startButton.y = 100;
}

void MainScene_Event()
{
	// SDL �̺�Ʈ�� Ȯ���ϱ� ���� ��ü ����
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		// event�� Ÿ���� SDL_QUIT�� Ʈ���Ÿ� Ȱ��ȭ �մϴ�.
		if (event.type == SDL_QUIT) {
			mainScene.quit = EXIT_GAME;
			break;
		}
	}
}

void MainScene_Update()
{
	// ������Ʈ�� �̵��� ó���մϴ�.
	double dt = getDeltaTime();

	// ���콺 ��ġ�� �����ɴϴ�.
	int mouseX, mouseY = 0;
	getCurrentMousePos(&mouseX, &mouseY);

	// ���콺 Ű�� ���ȴ��� üũ�մϴ�.
	if (getButtonState(SDL_BUTTON_LEFT) == KEY_DOWN) {
		// startButton�� ���ȴ��� üũ�Ѵ�.
		if (checkCollisionWithPoint(mainScene.rect_startButton, mouseX, mouseY)) {
			printf("GameScene���� �̵��մϴ�. \n");
			mainScene.quit = GAME_SCENE;
		}
	}
}

void MainScene_Render()
{
	SDL_Renderer* renderer = Get_Renderer();
	// ����� ĥ�մϴ�.
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
	// �ʿ��� ������ �ʱ�ȭ �մϴ�.
	mainScene.quit = SCENE_LOOP;

	Mix_HaltMusic();
	Mix_HaltChannel(-1);

	// ������ �����մϴ�.
	while (mainScene.quit == SCENE_LOOP) {
		// ��ƿ �Լ��� ������Ʈ �մϴ�.
		// �̸� ������ �����ؾ�, ���� �Լ����� ���������� ����� �� �ֽ��ϴ�.
		Update_Util();

		MainScene_Event();
		MainScene_Update();
		MainScene_Render();
	}

	// ���� ������ Ȯ���ؼ� �������ϴ�.
	return mainScene.quit;
}
