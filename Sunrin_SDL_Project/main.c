#include "pch.h"
#include "MainScene.h"
#include "GameScene.h"
#include "ScoreScene.h"

int main() {
	// ���α׷����� ����� ���̺귯�� �ʱ�ȭ ����
	Init_Program();

	// ������ ����� �ڷḦ �ҷ��� �� �ֵ���, ���� Init �Լ��� �����մϴ�.
	MainScene_Init();
	GameScene_Init();
	ScoreScene_Init();

	// ������ ���� ������ �ֽ��ϴ�.
	int scene_info = MAIN_SCENE;

	// �� ������ ���� �۾��� �̰����� �����մϴ�.
	// -1�� ��ȯ�Ǹ�, ���α׷� ����� �����մϴ�.
	while (scene_info >= 0) {
		switch (scene_info)
		{
		case MAIN_SCENE:
			scene_info = MainScene_Loop();	// MainScene�� �����մϴ�.
			break;
		case GAME_SCENE:
			scene_info = GameScene_Loop();	// GameScene�� �����մϴ�.
			break;
		case SCORE_SCENE:
			scene_info = ScoreScene_Loop();	// ScoreScene�� �����մϴ�.
			break;
		default:
			scene_info = EXIT_GAME;
			break;
		}
	}
	
	// ������ �ҷ��� �ڷḦ ������ �մϴ�.
	MainScene_Release();

	// ������ ����
	Release_Program();
	return 0;
}
