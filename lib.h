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

Node* CreateNode(DataType val); // 创建新节点
void SetNodeValue(Node* node, DataType val); // 给节点赋值
Node* CreateSentinelList();                  // 创建哨兵节点（双向链表）
void AddTail(Node* sentinel, DataType val); //  尾插
void AddHead(Node* sentinel, DataType val);  // 头插
int DeleteNode(Node* sentinel, DataType val);// 删除第一个值为 val 的节点，成功返回 1，失败返回 0
void ClearList(Node* sentinel);              // 清空链表
void DestroyList(Node* sentinel);           // 销毁链表
int GetLength(Node* sentinel);              // 获取链表长度
Node* FindNode(Node* sentinel, DataType val);// 找到返回节点指针，没找到返回 NULL
Node* FindNodeByPos(Node* sentinel, int pos);// 位置从 1 开始，找到返回节点，失败返回 NULL
void SwapNode(Node* a, Node* b);            // 交换两个节点的位置（直接交换节点，不交换值）
int InsertByPos(Node* sentinel, int pos, DataType val);// 位置从 1 开始，允许插入位置：1 ~ len+1（尾后），成功返回 1，失败返回 0
int DeleteByPos(Node* sentinel, int pos);               // 位置从 1 开始，成功返回 1，失败返回 0
void ReverseList(Node* sentinel);                       // 链表逆置 Reverse
Node* MergeSortedList(Node* list1, Node* list2, int (*cmp)(DataType, DataType));  // 合并两个有序链表（升序），返回新链表（不破坏原链表）


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
