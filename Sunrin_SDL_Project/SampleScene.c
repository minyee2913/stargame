#include "pch.h"
#include "SampleScene.h" // include!

// �ʿ��� ������ ���� ������ �����ؼ� ����մϴ�.
typedef struct SampleScene {
	// ������ ���������� ����� ������ ����ü�� �����ؼ� ����Ѵ�!
	int quit;
} SampleScene;
SampleScene sampleScene;

void SampleScene_Init()
{
	SDL_Renderer* renderer = Get_Renderer();
}

void SampleScene_Event()
{
	// SDL �̺�Ʈ�� Ȯ���ϱ� ���� ��ü ����
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		// event�� Ÿ���� SDL_QUIT�� Ʈ���Ÿ� Ȱ��ȭ �մϴ�.
		if (event.type == SDL_QUIT) {
			sampleScene.quit = EXIT_GAME;
			break;
		}
	}
}

void SampleScene_Update()
{
	// ������Ʈ�� �̵��� ó���մϴ�.
	double dt = getDeltaTime();

	// ���콺 Ű�� ���ȴ��� üũ�մϴ�.
	if (getButtonState(SDL_BUTTON_LEFT) == KEY_DOWN) {
		
	}
}

void SampleScene_Render()
{
	SDL_Renderer* renderer = Get_Renderer();

	// �Ķ��� ����� ĥ�մϴ�.
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}

void SampleScene_Release()
{
	// ����� �ڷḦ �����մϴ�.

}

int SampleScene_Roop()
{
	// �ʿ��� ������ �ʱ�ȭ �մϴ�.
	sampleScene.quit = SCENE_LOOP;

	// ������ �����մϴ�.
	while (sampleScene.quit == SCENE_LOOP) {
		// ��ƿ �Լ��� ������Ʈ �մϴ�.
		// �̸� ������ �����ؾ�, ���� �Լ����� ���������� ����� �� �ֽ��ϴ�.
		Update_Util();

		SampleScene_Event();
		SampleScene_Update();
		SampleScene_Render();
	}

	// ���� ������ Ȯ���ؼ� �������ϴ�.
	return sampleScene.quit;
}
