#pragma once

// 키에 대한 상태를 정의합니다.
#define KEY_NONE -1
#define KEY_DOWN 0
#define KEY_PRESS 1
#define KEY_UP 2

// 키보드 정보를 업데이트 합니다.
void updateKeyState();

// 조건에 따른 키 정보를 가져옵니다.
int getKeyState(int keyCode);

// 마우스의 현재 상태로 업데이트 합니다.
void updateMouseState();

// 조건에 따른 마우스 버튼 정보를 가져옵니다.
int getButtonState(int buttonCode);

// 현재 프레임의 마우스 위치 정보를 가져옵니다.
void getCurrentMousePos(int* currentPosX, int* currentPosY);

// 이전 프레임의 마우스 위치 정보를 가져옵니다.
void getBeforeMousePos(int* beforePosX, int* beforePosY);

// 이전 프레임에서 마우스가 얼마나 이동했는지를 가져옵니다.
void getDeltaMousePos(int* deltaPosX, int* deltaPosY);