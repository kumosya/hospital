#pragma once

#include "framework.h"

void ListTest();

// List
typedef void* DataType;

typedef struct Node {
    DataType data;
    struct Node* prev;  // 前驱指针
    struct Node* next;  // 后继指针
} Node;

Node* CreateNode(DataType val);
void SetNodeValue(Node* node, DataType val);
Node* CreateSentinelList();
void AddTail(Node* sentinel, DataType val);
void AddHead(Node* sentinel, DataType val);
int DeleteNode(Node* sentinel, DataType val);
void ClearList(Node* sentinel);
void ClearList(Node* sentinel);
void DestroyList(Node* sentinel);
int GetLength(Node* sentinel);
Node* FindNode(Node* sentinel, DataType val);
Node* FindNodeByPos(Node* sentinel, int pos);
void SwapNode(Node* a, Node* b);
int InsertByPos(Node* sentinel, int pos, DataType val);
int DeleteByPos(Node* sentinel, int pos);
void ReverseList(Node* sentinel);
Node* MergeSortedList(Node* list1, Node* list2, int (*cmp)(DataType, DataType));


// Queue

typedef struct {
    Node* sentinel;
    Node* rear;
} Queue;


Queue* CreateQueue();
int IsEmpty(Queue* q);
void EnQueue(Queue* q, DataType val);
DataType DeQueue(Queue* q);
DataType GetFront(Queue* q);
void DestroyQueue(Queue* q);


// File

FILE* FileOpen(const char* filename, const char* mode);
