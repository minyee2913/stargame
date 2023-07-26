#pragma once

// 씬별 초기화 함수를 정의합니다.
// 여기서는 사용할 자료를 초기화 합니다.
void GameScene_Init();

// Event 함수를 정의합니다.
void GameScene_Event();

// Update 함수를 정의합니다.
void GameScene_Update();

// Render 함수를 정의합니다.
void GameScene_Render();

// Release 함수를 정의합니다.
void GameScene_Release();

// 메인 화면에서 시작할 게임 루프를 정의합니다.
int GameScene_Loop();

int getGameScore();