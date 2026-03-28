#include "framework.h"
#include "lib.h"

Queue* CreateQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->sentinel = CreateSentinelList();
    q->rear = q->sentinel->prev;
    return q;
}

int IsEmpty(Queue* q) {
    return q->sentinel->next == q->sentinel;
}

void EnQueue(Queue* q, DataType val) {
    AddTail(q->sentinel, val);
    q->rear = q->sentinel->prev;
}

DataType DeQueue(Queue* q) {
    if (IsEmpty(q)) {
        //printf("队空，无法出队！\n");
        return NULL;
    }
    Node* temp = q->sentinel->next;
    DataType val = temp->data;

    q->sentinel->next = temp->next;
    temp->next->prev = q->sentinel;
    free(temp);

    if (q->sentinel->next == q->sentinel)
        q->rear = q->sentinel->prev;

    return val;
}

DataType GetFront(Queue* q) {
    if (IsEmpty(q)) return NULL;
    return q->sentinel->next->data;
}

void DestroyQueue(Queue* q) {
    DestroyList(q->sentinel);
    free(q);
}