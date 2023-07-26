#include "pch.h"
#include "animation.h"

void initAnimation(Animation* anim, int fps, int isLoop)
{
	list_init(&anim->animList);
	anim->animTimer = 0.0;
	anim->fps = fps;
	anim->isLoop = isLoop;
	anim->end = 0;
	anim->currentFrame = 0;
}

void restartAnimation(Animation* anim)
{
	anim->animTimer = 0.0;
	anim->currentFrame = 0;
	anim->end = 0;
}

void appendTexture(Animation* anim, SDL_Texture* texture)
{
	list_push(&anim->animList, texture);
}

void updateAnimation(Animation* anim, double dt)
{
	if (anim->end) return;

	// 타이머 갱신
	anim->animTimer += dt;

	if (anim->animTimer >= 1.0 / anim->fps) {
		anim->animTimer = 0.0;
		anim->currentFrame++;

		if (anim->isLoop) {
			anim->currentFrame %= anim->animList.len;
		}
		else if(anim->currentFrame > anim->animList.len) {
			anim->end = 1;
			anim->currentFrame = anim->animList.len;
		}
	}

}

SDL_Texture* getCurrentFrame(Animation* anim)
{
	return (SDL_Texture*)list_search(&anim->animList, anim->currentFrame);
}

void releaseAnimation(Animation* anim)
{
	list_releaseList(&anim->animList);
}

void releaseAnimationWTexture(Animation* anim)
{
	Node* textureNode = anim->animList.head;
	for (int i = 0; i < anim->currentFrame; i++) {
		SDL_Texture* texture = (SDL_Texture*)textureNode->val;

		// 순회하면서 모든 texture 해제하기
		SDL_DestroyTexture(texture);

		textureNode = textureNode->next;
	}

	list_releaseList(&anim->animList);
}
