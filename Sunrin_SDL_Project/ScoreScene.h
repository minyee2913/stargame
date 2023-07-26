#pragma once

// 씬별 초기화 함수를 정의합니다.
// 여기서는 사용할 자료를 초기화 합니다.
void ScoreScene_Init();

// Event 함수를 정의합니다.
void ScoreScene_Event();

// Update 함수를 정의합니다.
void ScoreScene_Update();

// Render 함수를 정의합니다.
void ScoreScene_Render();

// Release 함수를 정의합니다.
void ScoreScene_Release();

// 메인 화면에서 시작할 게임 루프를 정의합니다.
int ScoreScene_Loop();