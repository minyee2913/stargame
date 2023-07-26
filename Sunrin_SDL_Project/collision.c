#include "collision.h"

int checkCollision(SDL_Rect rect1, SDL_Rect rect2)
{
    // 두 개의 사각형이 충돌하는지 여부를 확인
    if (rect1.x + rect1.w >= rect2.x &&       // rect1 우측 경계가 rect2 좌측 경계를 넘지 않고
        rect1.x <= rect2.x + rect2.w &&       // rect1 좌측 경계가 rect2 우측 경계를 넘지 않으며
        rect1.y + rect1.h >= rect2.y &&       // rect1 하단 경계가 rect2 상단 경계를 넘지 않고
        rect1.y <= rect2.y + rect2.h) {       // rect1 상단 경계가 rect2 하단 경계를 넘지 않으면 충돌
        return 1;
    }

    return 0;  // 충돌하지 않음
}

int checkCollisionWithPoint(SDL_Rect rect, int x, int y)
{
    // 주어진 위치 (x, y)가 사각형 내에 있는지 확인
    if (x >= rect.x && x <= rect.x + rect.w &&   // x 좌표가 사각형 범위 내에 있고
        y >= rect.y && y <= rect.y + rect.h) {  // y 좌표가 사각형 범위 내에 있으면 충돌
        return 1;
    }

    return 0;  // 충돌하지 않음
}
