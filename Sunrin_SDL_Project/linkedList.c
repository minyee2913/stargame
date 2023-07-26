#include "pch.h"
#include "linkedList.h"
#include <stdlib.h>
#include <memory.h>

void list_init(List* list) {
    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
}

int list_push(List* list, void* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return -1; // 메모리 할당 실패
    }
    newNode->next = NULL;
    newNode->val = data;

    if (list->head == NULL) {
        // 리스트가 비어있을 경우
        list->head = newNode;
        list->tail = newNode;
    }
    else {
        // 맨 뒤에 노드를 추가하는 것이므로, tail의 다음 Node를 newNode로 설정합니다.
        // 
        list->tail->next = newNode;
        list->tail = newNode;
    }

    list->len++;
    return 1; // 데이터 추가 성공
}

int list_insert(List* list, int index, void* data) {
    if (index < 0 || index > list->len) {
        return 0; // 유효하지 않은 인덱스
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return 0; // 메모리 할당 실패
    }

    newNode->val = data;

    if (index == 0) {
        // 리스트의 맨 앞에 삽입
        newNode->next = list->head;
        list->head = newNode;

        if (list->tail == NULL) {
            // 리스트가 비어있는 경우
            list->tail = newNode;
        }
    }
    else {
        // 리스트의 중간이나 맨 뒤에 삽입
        Node* prevNode = list->head;

        // index까지 이전까지 이동
        for (int i = 1; i < index; i++) {
            prevNode = prevNode->next;
        }

        // 다음 node 설정
        newNode->next = prevNode->next;
        prevNode->next = newNode;

        if (newNode->next == NULL) {
            // 리스트의 맨 뒤에 삽입
            list->tail = newNode;
        }
    }

    list->len++;
    return 1; // 데이터 추가 성공
}

void* list_pop(List* list, int index) {
    if (index < 0 || index >= list->len) {
        return NULL; // 유효하지 않은 인덱스
    }

    // 지울 노드 선언
    Node* removedNode;

    if (index == 0) {
        // 리스트의 맨 앞 노드 삭제
        removedNode = list->head;
        list->head = removedNode->next;

        if (list->tail == removedNode) {
            // 리스트에 노드가 하나만 있었을 경우
            list->tail = NULL;
        }
    }
    else {
        // 리스트의 중간이나 맨 뒤 노드 삭제
        Node* prevNode = list->head;

        // 해당 인덱스 까지 이동
        for (int i = 1; i < index; i++) {
            prevNode = prevNode->next;
        }

        // 노드끼리 연결
        removedNode = prevNode->next;
        prevNode->next = removedNode->next;

        if (removedNode == list->tail) {
            // 리스트의 맨 뒤 노드 삭제
            list->tail = prevNode;
        }
    }

    void* val = removedNode->val;
    free(removedNode);
    list->len--;
    return val; // 노드 삭제 성공, val을 반환합니다.
}

void* list_remove(List* list, void* data) {
    Node* prevNode = NULL;
    Node* currentNode = list->head;

    while (currentNode != NULL) {
        if (currentNode->val == data) {
            if (prevNode == NULL) {
                // 지울 노드가 head인 경우
                // 리스트의 맨 앞 노드 삭제
                list->head = currentNode->next;

                if (list->tail == currentNode) {
                    // 리스트에 노드가 하나만 있었을 경우
                    list->tail = NULL;
                }
            }
            else {
                // 리스트의 중간이나 맨 뒤 노드 삭제
                prevNode->next = currentNode->next;

                if (currentNode == list->tail) {
                    // 리스트의 맨 뒤 노드 삭제
                    list->tail = prevNode;
                }
            }

            void* val = currentNode->val;
            free(currentNode);
            list->len--;
            return val; // 노드 삭제 성공, val을 반환합니다.
        }

        prevNode = currentNode;
        currentNode = currentNode->next;
    }

    return NULL; // 데이터를 찾지 못함
}

void* list_search(List* list, int index) {
    if (index < 0 || index >= list->len) {
        return NULL; // 유효하지 않은 인덱스
    }

    Node* currentNode = list->head;
    for (int i = 0; i < index; i++) {
        currentNode = currentNode->next;
    }

    return currentNode->val;
}

void list_releaseList(List* list) {
    Node* currentNode = list->head;
    while (currentNode != NULL) {
        Node* nextNode = currentNode->next;
        free(currentNode);
        currentNode = nextNode;
    }
    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
}

void list_releaseListWVal(List* list)
{
    Node* currentNode = list->head;
    while (currentNode != NULL) {
        Node* nextNode = currentNode->next;
        free(currentNode->val);
        free(currentNode);
        // free(currentNode->val);
        currentNode = nextNode;
    }
    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
}
