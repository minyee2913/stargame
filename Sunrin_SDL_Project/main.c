#include "pch.h"
#include "MainScene.h"
#include "GameScene.h"
#include "ScoreScene.h"

int main() {
	// 프로그램에서 사용할 라이브러리 초기화 진행
	Init_Program();

	// 씬에서 사용할 자료를 불러올 수 있도록, 씬별 Init 함수를 실행합니다.
	MainScene_Init();
	GameScene_Init();
	ScoreScene_Init();

	// 시작할 씬의 정보를 넣습니다.
	int scene_info = MAIN_SCENE;

	// 씬 사이의 연결 작업을 이곳에서 정의합니다.
	// -1이 반환되면, 프로그램 종료로 간주합니다.
	while (scene_info >= 0) {
		switch (scene_info)
		{
		case MAIN_SCENE:
			scene_info = MainScene_Loop();	// MainScene을 시작합니다.
			break;
		case GAME_SCENE:
			scene_info = GameScene_Loop();	// GameScene을 시작합니다.
			break;
		case SCORE_SCENE:
			scene_info = ScoreScene_Loop();	// ScoreScene을 시작합니다.
			break;
		default:
			scene_info = EXIT_GAME;
			break;
		}
	}
	
	// 씬에서 불러온 자료를 릴리스 합니다.
	MainScene_Release();

	// 릴리즈 진행
	Release_Program();
	return 0;
}
