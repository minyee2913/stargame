#pragma once
#include <SDL_image.h>
#include "linkedList.h"

#define ANIM_LOOP_OFF	0
#define ANIM_LOOP_ON	1

typedef struct Animatnion {
	List animList;		// 출력할 이미지 전체를 담아두는 곳 입니다.
	double animTimer;	// 출력할 이미지를 변환하기 위한 타이머 입니다.
	
	int currentFrame;		// 현재 출력할 이미지의 인덱스를 의미합니다.
	int fps;				// 1초에 이미지를 몇 번 넘길 것인지를 의미합니다.
	int isLoop;				// 반복 여부를 의미합니다.
	int end;				// 종료 여부를 의미합니다.
} Animation;

// Animation을 초기화 합니다.
// fps: 1초에 이미지를 몇 번 넘길 것인지 작성합니다.
// isLoop: 이미지를 반복할 것인지 작성합니다. (ANIM_LOOP_OFF, ON을 활용해 보세요.)
void initAnimation(Animation* anim, int fps, int isLoop);

// Animation을 재시작 합니다.
// currentFrameIndex, animTimer, end를 초기화 합니다.
void restartAnimation(Animation* anim);

// Animation을 복제 합니다.
// 미리 정의해 놓은 Animation을 새로운 객체에 복제하기 위해 사용합니다.
void copyAnimation(Animation* dst, Animation* src);

// Animation에 텍스쳐를 추가합니다.
void appendTexture(Animation* anim, SDL_Texture* texture);

// Animation의 타이머를 업데이트하여, 다음 이미지를 구합니다.
void updateAnimation(Animation* anim, double dt);
 
// 현재 렌더링할 이미지를 구합니다.
SDL_Texture* getCurrentFrame(Animation* anim);

// Animation을 해제합니다.
// 원본만 수행하면 됩니다.
void releaseAnimation(Animation* anim);

// Animationn을 해제합니다.
// 원본만 수행하면 됩니다.
// Texture 또한 여기서 해제하고 싶다면, 아래 함수를 사용해주세요.
void releaseAnimationWTexture(Animation* anim);