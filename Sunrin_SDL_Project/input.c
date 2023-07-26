#include "pch.h"
#include "SDL.h"
#include "input.h"

// 키보드 관리에 필요한 변수들을 정의합니다.
// SDL_NUM_SCANCODES: 스캔 코드의 수를 반환합니다. (512)
size_t memSize = sizeof(Uint8) * SDL_NUM_SCANCODES; // 배열의 키기를 저장합니다.
const Uint8* currentKeyState = NULL;                // 현재 키 정보를 저장할 포인터를 선언합니다. (API로 가져옵니다.)
// 동적 할당에 대한 해제를 제거하기 위해 정적 배열로 선언합니다.
const Uint8 beforeKeyState[SDL_NUM_SCANCODES];      // 이전 키 정보를 저장할 배열을 선언합니다.

// 마우스 정보와 관련된 변수들을 정의합니다.
int beforeMousePosX = 0;
int beforeMousePosY = 0;
int currentMousePosX = 0;
int currentMousePosY = 0;
Uint32 beforeMouseState = 0;
Uint32 currentMouseState = 0;

// 함수 정의를 진행합니다! ------------

void updateKeyState()
{
    // 키 상태를 초기화 합니다.
    if (currentKeyState == NULL) {
        currentKeyState = SDL_GetKeyboardState(NULL);
    }

    SDL_memcpy(beforeKeyState, currentKeyState, memSize);
}

int getKeyState(int keyCode)
{
    if (beforeKeyState[keyCode] == 0 && currentKeyState[keyCode] == 0)
        return KEY_NONE;
    if (beforeKeyState[keyCode] == 0 && currentKeyState[keyCode] == 1)
        return KEY_DOWN;
    if (beforeKeyState[keyCode] == 1 && currentKeyState[keyCode] == 1)
        return KEY_PRESS;
    if (beforeKeyState[keyCode] == 1 && currentKeyState[keyCode] == 0)
        return KEY_UP;
}

void updateMouseState() {
    beforeMousePosX = currentMousePosX;
    beforeMousePosY = currentMousePosY;

    beforeMouseState = currentMouseState;
    currentMouseState = SDL_GetMouseState(&currentMousePosX, &currentMousePosY);
}

int getButtonState(int buttonCode) {
    Uint32 buttonMask = SDL_BUTTON(buttonCode);
    int before = beforeMouseState & buttonMask;
    int current = currentMouseState & buttonMask;

    if (before == 0 && current == 0)
        return KEY_NONE;
    if (before == 0 && current == 1)
        return KEY_DOWN;
    if (before == 1 && current == 1)
        return KEY_PRESS;
    if (before == 1 && current == 0)
        return KEY_UP;
}

void getCurrentMousePos(int* currentPosX, int* currentPosY) {
    // *연산자로 포인터에 접근해서 값을 변경합니다.
    if (currentPosX != NULL) {
        *currentPosX = currentMousePosX;
    }
    if (currentPosY != NULL) {
        *currentPosY = currentMousePosY;
    }
}

void getBeforeMousePos(int* beforePosX, int* beforePosY) {
    // *연산자로 포인터에 접근해서 값을 변경합니다.
    if (beforePosX != NULL) {
        *beforePosX = beforeMousePosX;
    }
    if (beforePosY != NULL) {
        *beforePosY = beforeMousePosY;
    }
}

void getDeltaMousePos(int* deltaPosX, int* deltaPosY) {
    // *연산자로 포인터에 접근해서 값을 변경합니다.
    if (deltaPosX != NULL) {
        *deltaPosX = currentMousePosX - beforeMousePosX;
    }
    if (deltaPosY != NULL) {
        *deltaPosY = currentMousePosY - beforeMousePosY;
    }
}
