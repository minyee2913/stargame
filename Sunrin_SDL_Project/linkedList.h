#pragma once

// 구조체 type 선언
typedef struct node Node;
typedef struct list List;

struct node {
    void* val;
    struct node* next;
};

struct list {
    struct node* head;
    struct node* tail;
    int len;
};

// 리스트를 초기화 합니다.
void list_init(List* list);

// 리스트 맨 뒤에 데이터를 추가합니다.
int list_push(List* list, void* data);

// 원하는 위치에 데이터를 추가합니다.
int list_insert(List* list, int index, void* data);

// 위치를 기반으로 Node를 제거합니다.
void* list_pop(List* list, int index);

// 데이터를 기반으로 Node를 제거합니다.
void* list_remove(List* list, void* data);

// 위치를 기반으로 탐색합니다.
void* list_search(List* list, int index);

// 리스트 전체를 해제하는 함수
void list_releaseList(List* list);

// 리스트 전체를 해제하는 함수
void list_releaseListWVal(List* list);
