#include "pch.h"
#include "ScoreScene.h" // include!

// �ʿ��� ������ ���� ������ �����ؼ� ����մϴ�.
typedef struct ScoreScene {
	// ������ ���������� ����� ������ ����ü�� �����ؼ� ����Ѵ�!
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
	// SDL �̺�Ʈ�� Ȯ���ϱ� ���� ��ü ����
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		// event�� Ÿ���� SDL_QUIT�� Ʈ���Ÿ� Ȱ��ȭ �մϴ�.
		if (event.type == SDL_QUIT) {
			scoreScene.quit = EXIT_GAME;
			break;
		}
	}
}

void ScoreScene_Update()
{
	// ������Ʈ�� �̵��� ó���մϴ�.
	double dt = getDeltaTime();

	// ���콺 Ű�� ���ȴ��� üũ�մϴ�.
	if (getKeyState(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		scoreScene.quit = MAIN_SCENE;
	}
}

void ScoreScene_Render()
{
	SDL_Renderer* renderer = Get_Renderer();

	// �Ķ��� ����� ĥ�մϴ�.
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	SDL_Color textureColor = { 255, 255, 255, 255 };

	drawTextCenter(renderer, scoreScene.font, scoreScene.str, SCREEN_WIDTH / 2, 200, textureColor);
	drawTextCenter(renderer, scoreScene.font, u8"space �ٸ� ���� ���� ȭ������...", SCREEN_WIDTH / 2, 650, textureColor);

	SDL_RenderPresent(renderer);
}

void ScoreScene_Release()
{
	// ����� �ڷḦ �����մϴ�.
	TTF_CloseFont(scoreScene.font);
}

int ScoreScene_Loop()
{
	// �ʿ��� ������ �ʱ�ȭ �մϴ�.
	scoreScene.quit = SCENE_LOOP;

	memset(scoreScene.str, 0, sizeof(scoreScene.str));

	sprintf_s(scoreScene.str, sizeof(scoreScene.str), u8"���� ���ھ�: %d", getGameScore());

	// ������ �����մϴ�.
	while (scoreScene.quit == SCENE_LOOP) {
		// ��ƿ �Լ��� ������Ʈ �մϴ�.
		// �̸� ������ �����ؾ�, ���� �Լ����� ���������� ����� �� �ֽ��ϴ�.
		Update_Util();

		ScoreScene_Event();
		ScoreScene_Update();
		ScoreScene_Render();
	}

	// ���� ������ Ȯ���ؼ� �������ϴ�.
	return scoreScene.quit;
}
