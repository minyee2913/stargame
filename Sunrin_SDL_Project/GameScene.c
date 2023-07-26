#include "pch.h"
#include "GameScene.h" // include!
#include "sound.h"
#include "animation.h"

typedef struct Vec2 {
	float x;
	float y;
} Vec2;

// 필요한 변수는 전역 변수로 전언해서 사용합니다.
typedef struct GameScene {
	// 씬에서 전역적으로 사용할 변수는 구조체로 랩핑해서 사용한다!
	int quit;

	// 사용할 이미지 정보
	SDL_Texture* background;
	SDL_Texture* background2;
	SDL_Texture* background3;
	SDL_Texture* background4;

	SDL_Texture* oraora;

	TTF_Font* font;
	TTF_Font* font2;

	float delay;

	int score;

	Vec2 pointedBeforeOfBeforeOfBefore;
	Vec2 pointedBeforeOfBefore;
	Vec2 pointedBefore;
	Vec2 pointed;

	Vec2 pos[3];
	SDL_Rect pos_rect[3];

	List unpointed;

	double waiting;
	double cycle;

	double timeline;
	double oraCount;

	double SuccessTIme;

	Mix_Music* music;
	Mix_Chunk* star;

	Animation* explodeAnim;

} GameScene;
GameScene gameScene;

void GameScene_Init()
{
	SDL_Renderer* renderer = Get_Renderer();

	gameScene.background = loadTexture(renderer, "./resources/background/stars-train.gif");
	gameScene.background2 = loadTexture(renderer, "./resources/background/galaxy.jpg");
	gameScene.background3 = loadTexture(renderer, "./resources/background/night_sky.jpg");
	gameScene.background4 = loadTexture(renderer, "./resources/background/portal.jpg");
	gameScene.oraora = loadTexture(renderer, "./resources/oraora.png");

	gameScene.pointed.x = SCREEN_WIDTH / 2;
	gameScene.pointed.y = SCREEN_HEIGHT / 2;

	gameScene.pointedBefore.x = gameScene.pointed.x;
	gameScene.pointedBefore.y = gameScene.pointed.y;

	gameScene.pointedBeforeOfBefore.x = gameScene.pointed.x;
	gameScene.pointedBeforeOfBefore.y = gameScene.pointed.y;
	gameScene.pointedBeforeOfBeforeOfBefore.y = gameScene.pointed.y;

	gameScene.cycle = 0;
	gameScene.waiting = 0;
	gameScene.oraCount = 0;

	gameScene.timeline = 0;
	gameScene.SuccessTIme = 0;

	gameScene.font = TTF_OpenFont("./resources/Pretendard.otf", 38);
	gameScene.font2 = TTF_OpenFont("./resources/Pretendard.otf", 32);

	gameScene.music = Mix_LoadMUS("./resources/music/music.wav");
	gameScene.star = Mix_LoadWAV("./resources/Sound FX/star.wav");
}

void GameScene_Event()
{
	// SDL 이벤트를 확인하기 위한 객체 생성
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		// event의 타입이 SDL_QUIT면 트리거를 활성화 합니다.
		if (event.type == SDL_QUIT) {
			gameScene.quit = EXIT_GAME;
			break;
		}
	}
}

void GameScene_Update()
{
	double dt = getDeltaTime();

	gameScene.timeline += dt;

	if (gameScene.timeline >= 32 && gameScene.timeline <= 62 || gameScene.timeline >= 120) gameScene.oraCount += dt;

	if (gameScene.oraCount > 1.5) gameScene.oraCount = 0;

	if (gameScene.SuccessTIme > 0) gameScene.SuccessTIme -= dt;

	if (gameScene.timeline > 157) {
		gameScene.quit = SCORE_SCENE;

		return;
	}

	if (gameScene.waiting <= 0) {
		list_releaseList(&gameScene.unpointed);
		list_init(&gameScene.unpointed);
		gameScene.cycle += dt;

		float delay = 2;
		if (gameScene.timeline >= 32 && gameScene.timeline <= 62) delay = 1.5;
		else if (gameScene.timeline >= 66 && gameScene.timeline <= 145) delay = 1.8;
		else if (gameScene.timeline >= 120) delay = 1.5;

		if (gameScene.cycle > delay) {
			for (int i = 0; i < 3; i++) {

				gameScene.pos[i].x = rand() % SCREEN_WIDTH;
				gameScene.pos[i].y = rand() % SCREEN_HEIGHT;

				(gameScene.pos_rect[i]).x = gameScene.pos[i].x - 8;
				(gameScene.pos_rect[i]).y = gameScene.pos[i].y - 8;
				(gameScene.pos_rect[i]).w = 16;
				(gameScene.pos_rect[i]).h = 16;

				list_push(&gameScene.unpointed, &(gameScene.pos[i]));
			}
			
			if (gameScene.timeline >= 32 && gameScene.timeline <= 62) gameScene.waiting = 0.8;
			else if (gameScene.timeline >= 120) gameScene.waiting = 0.6;
			else gameScene.waiting = 1;
			gameScene.cycle = 0;
		}
	}
	else {
		int mouseX, mouseY = 0;
		getCurrentMousePos(&mouseX, &mouseY);

		if (getButtonState(SDL_BUTTON_LEFT) == KEY_DOWN) {
			for (int i = 0; i < 3; i++) {
				if (checkCollisionWithPoint(gameScene.pos_rect[i], mouseX, mouseY)) {
					int distance = (int)sqrt(pow(gameScene.pos_rect[i].x - gameScene.pointed.x, 2) + pow(gameScene.pos_rect[i].y - gameScene.pointed.y, 2));

					gameScene.score += distance / 10;

					gameScene.pointedBeforeOfBeforeOfBefore.x = gameScene.pointedBeforeOfBefore.x;
					gameScene.pointedBeforeOfBeforeOfBefore.y = gameScene.pointedBeforeOfBefore.y;
					gameScene.pointedBeforeOfBefore.x = gameScene.pointedBefore.x;
					gameScene.pointedBeforeOfBefore.y = gameScene.pointedBefore.y;
					gameScene.pointedBefore.y = gameScene.pointed.y;
					gameScene.pointedBefore.x = gameScene.pointed.x;
					gameScene.pointedBefore.y = gameScene.pointed.y;
					gameScene.pointed.x = gameScene.pos[i].x;
					gameScene.pointed.y = gameScene.pos[i].y;

					gameScene.waiting = 0;
					gameScene.SuccessTIme = 0.5;

					Mix_PlayChannel(-1, gameScene.star, 0);
				}
			}
		}
		gameScene.waiting -= dt;
	}
}

void GameScene_Render()
{
	SDL_Renderer* renderer = Get_Renderer();

	// 파란색 배경을 칠합니다.
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	if (gameScene.timeline < 30) drawTextureWithRatio(renderer, 0, 0,
		2.0, 2.0, gameScene.background);
	else if (gameScene.timeline >= 32 && gameScene.timeline <= 62) drawTextureWithRatio(renderer, 0, rand() % -20 - 5, 0.7, 0.7, gameScene.background2);
	else if (gameScene.timeline >= 66 && gameScene.timeline <= 145) drawTextureWithRatio(renderer, 0, 0, 2.8, 2.8, gameScene.background3);
	else if (gameScene.timeline >= 120) drawTextureWithRatio(renderer, rand() % -10 - 5, rand() % -10 - 5, 3, 2.8, gameScene.background4);

	drawFilledCircle(renderer, gameScene.pointedBeforeOfBefore.x, gameScene.pointedBeforeOfBefore.y, 5, 207, 255, 243, 255);
	drawFilledCircle(renderer, gameScene.pointedBefore.x, gameScene.pointedBefore.y, 5, 207, 255, 243, 255);
	drawFilledCircle(renderer, gameScene.pointed.x, gameScene.pointed.y, 6, 115, 255, 156, 255);

	if (gameScene.oraCount >= 0.3) drawTextureWithRatio(renderer, SCREEN_WIDTH - 300, 100, 8, 8, gameScene.oraora);
	if (gameScene.oraCount >= 0.6) drawTextureWithRatio(renderer, SCREEN_WIDTH - 600, 500, 8, 8, gameScene.oraora);

	if (gameScene.oraCount >= 0.9) drawTextureWithRatio(renderer, 100, 300, 8, 8, gameScene.oraora);

	Node* pointNode = gameScene.unpointed.head;
	while (pointNode != NULL) {
		Vec2* pos = pointNode->val;
		
		drawFilledCircle(renderer, pos->x, pos->y, 10, 255, 255, 255, 255);

		pointNode = pointNode->next;
	}

	if (gameScene.pointed.x != gameScene.pointedBefore.x && gameScene.pointed.y != gameScene.pointedBefore.y) {
		SDL_RenderDrawLine(renderer, gameScene.pointedBefore.x, gameScene.pointedBefore.y, gameScene.pointed.x, gameScene.pointed.y);
	}
	if (gameScene.pointedBeforeOfBefore.x != gameScene.pointedBefore.x && gameScene.pointedBeforeOfBefore.y != gameScene.pointedBefore.y) {
		SDL_RenderDrawLine(renderer, gameScene.pointedBefore.x, gameScene.pointedBefore.y, gameScene.pointedBeforeOfBefore.x, gameScene.pointedBeforeOfBefore.y);
	}
	if (gameScene.pointedBeforeOfBefore.x != gameScene.pointedBeforeOfBeforeOfBefore.x && gameScene.pointedBeforeOfBefore.y != gameScene.pointedBeforeOfBeforeOfBefore.y) {
		SDL_RenderDrawLine(renderer, gameScene.pointedBeforeOfBeforeOfBefore.x, gameScene.pointedBeforeOfBeforeOfBefore.y, gameScene.pointedBeforeOfBefore.x, gameScene.pointedBeforeOfBefore.y);
	}

	SDL_Color textureColor = { 255, 255, 255, 255 };
	char str[50] = "My score: %d";
	sprintf_s(str, sizeof(str), "My score: %d", gameScene.score);
	drawText(renderer, gameScene.font, str, 0, 0, textureColor);

	if (gameScene.SuccessTIme > 0) drawText(renderer, gameScene.font2, "GOOD!", gameScene.pointed.x + 50, gameScene.pointed.y, textureColor);
       
	SDL_RenderPresent(renderer);
}

void GameScene_Release()
{
	// 사용한 자료를 해제합니다.
	SDL_DestroyTexture(gameScene.background);
}

int GameScene_Loop()
{
	// 필요한 변수를 초기화 합니다.
	gameScene.quit = SCENE_LOOP;
	gameScene.score = 0;

	list_init(&gameScene.unpointed);

	if (!Mix_PlayingMusic()) {
		// music을 재생합니다.
		// 어떤 음악을 재생할 지 입력합니다.
		// 몇 번 반복할 지 입력합니다.
		Mix_PlayMusic(gameScene.music, -1);
	}

	// 루프를 진행합니다.
	while (gameScene.quit == SCENE_LOOP) {
		// 유틸 함수를 업데이트 합니다.
		// 이를 씬별로 수행해야, 여러 함수들을 정상적으로 사용할 수 있습니다.
		Update_Util();

		GameScene_Event();
		GameScene_Update();
		GameScene_Render();
	}

	list_releaseList(&gameScene.unpointed);

	// 씬의 정보를 확인해서 내보냅니다.
	return gameScene.quit;
}

int getGameScore()
{
	return gameScene.score;
}
