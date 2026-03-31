#include "framework.h"
#include "lib.h"

// 创建新节点
Node* CreateNode(DataType val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        exit(-1);
    }
    newNode->data = val;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// 给节点赋值
void SetNodeValue(Node* node, DataType val) {
    if (node) node->data = val;
}

// 创建哨兵节点（双向链表）
Node* CreateSentinelList() {
    Node* sentinel = CreateNode(NULL);  // 哨兵不存有效数据
    sentinel->prev = sentinel;       // 双向循环
    sentinel->next = sentinel;
    return sentinel;
}

// 尾插
void AddTail(Node* sentinel, DataType val) {
    Node* newNode = CreateNode(val);
    Node* tail = sentinel->prev;

    tail->next = newNode;
    newNode->prev = tail;
    newNode->next = sentinel;
    sentinel->prev = newNode;
}

// 头插
void AddHead(Node* sentinel, DataType val) {
    Node* newNode = CreateNode(val);
    Node* first = sentinel->next;

    sentinel->next = newNode;
    newNode->prev = sentinel;
    newNode->next = first;
    first->prev = newNode;
}

// 删除第一个值为 val 的节点
int DeleteNode(Node* sentinel, DataType val) {
    Node* p = sentinel->next;
    while (p != sentinel) {
        if (p->data == val) {
            p->prev->next = p->next;
            p->next->prev = p->prev;
            free(p);
            return 1;
        }
        p = p->next;
    }
    return 0;
}


// 清空链表
void ClearList(Node* sentinel) {
    Node* p = sentinel->next;
    while (p != sentinel) {
        Node* temp = p;
        p = p->next;
        free(temp);
    }
    sentinel->next = sentinel;
    sentinel->prev = sentinel;
}

// 销毁链表
void DestroyList(Node* sentinel) {
    ClearList(sentinel);
    free(sentinel);
}

// 获取链表长度
int GetLength(Node* sentinel) {
    int len = 0;
    Node* p = sentinel->next;
    while (p != sentinel) {
        len++;
        p = p->next;
    }
    return len;
}

// 找到返回节点指针，没找到返回 NULL
Node* FindNode(Node* sentinel, DataType val) {
    Node* p = sentinel->next;
    while (p != sentinel) {
        if (p->data == val) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

// 位置从 1 开始，找到返回节点，失败返回 NULL
Node* FindNodeByPos(Node* sentinel, int pos) {
    if (pos < 1 || pos > GetLength(sentinel)) {
        return NULL;
    }
    Node* p = sentinel->next;
    for (int i = 1; i < pos; i++) {
        p = p->next;
    }
    return p;
}

// 交换两个节点的位置（直接交换节点，不交换值）
void SwapNode(Node* a, Node* b) {
    if (!a || !b || a == b) return;

    Node* aPrev = a->prev;
    Node* aNext = a->next;
    Node* bPrev = b->prev;
    Node* bNext = b->next;

    // 相邻情况处理
    if (aNext == b) {
        aPrev->next = b;
        b->prev = aPrev;
        b->next = a;
        a->prev = b;
        a->next = bNext;
        bNext->prev = a;
    }
    else if (bNext == a) {
        SwapNode(b, a);
    }
    // 不相邻
    else {
        aPrev->next = b;
        b->prev = aPrev;
        b->next = aNext;
        aNext->prev = b;

        bPrev->next = a;
        a->prev = bPrev;
        a->next = bNext;
        bNext->prev = a;
    }
}


// 在第 pos 个位置插入 val，pos 从 1 开始
// 成功返回 1，失败返回 0
int InsertByPos(Node* sentinel, int pos, DataType val) {
    int len = GetLength(sentinel);
    // 允许插入位置：1 ~ len+1（尾后）
    if (pos < 1 || pos > len + 1)
        return 0;

    Node* newNode = CreateNode(val);
    Node* p;

    if (pos == len + 1) {
        // 尾插
        p = sentinel;
    }
    else {
        // 找到第 pos 个节点，插在它前面
        p = FindNodeByPos(sentinel, pos);
    }

    // 双向插入
    newNode->prev = p->prev;
    newNode->next = p;
    p->prev->next = newNode;
    p->prev = newNode;

    return 1;
}

int DeleteByPos(Node* sentinel, int pos) {
    int len = GetLength(sentinel);
    if (pos < 1 || pos > len)
        return 0;

    Node* p = FindNodeByPos(sentinel, pos);

    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(p);
    return 1;
}

// 链表逆置 Reverse
void ReverseList(Node* sentinel) {
    if (sentinel->next == sentinel) return;

    Node* cur = sentinel;
    Node* temp = NULL;

    // 交换所有节点的前后指针
    do {
        temp = cur->next;
        cur->next = cur->prev;
        cur->prev = temp;
        cur = temp;
    } while (cur != sentinel);
}

// 合并两个有序链表（升序），返回新链表（不破坏原链表）
Node* MergeSortedList(Node* list1, Node* list2, int (*cmp)(DataType, DataType)) {
    Node* newList = CreateSentinelList();
    Node* p1 = list1->next;
    Node* p2 = list2->next;

    while (p1 != list1 && p2 != list2) {
        if (cmp(p1->data, p2->data) <= 0) {
            AddTail(newList, p1->data);
            p1 = p1->next;
        }
        else {
            AddTail(newList, p2->data);
            p2 = p2->next;
        }
    }

    // 剩余节点
    while (p1 != list1) { AddTail(newList, p1->data); p1 = p1->next; }
    while (p2 != list2) { AddTail(newList, p2->data); p2 = p2->next; }

    return newList;
}


/* 示例： */

// helper macros to convert between int and DataType when storing integers
#define INT_TO_DATA(i) ((DataType)(intptr_t)(i))
#define DATA_TO_INT(p) ((int)(intptr_t)(p))

// helper print and compare for integer DataType
void PrintInt(DataType d) { printf("%d ", DATA_TO_INT(d)); }
int IntCmp(DataType a, DataType b) { return DATA_TO_INT(a) - DATA_TO_INT(b); }

// 遍历链表
static void TraverseList(Node* sentinel, void (*printFunc)(DataType)) {
    Node* p = sentinel->next;
    while (p != sentinel) {
        printFunc(p->data);
        p = p->next;
    }
    printf("\n");
}
void ListTest() {
    printf("=== 链表测试 ===\n");
    Node* list = CreateSentinelList();
    AddTail(list, INT_TO_DATA(10));
    AddTail(list, INT_TO_DATA(20));
    AddHead(list, INT_TO_DATA(5));
    printf("初始链表：");
    TraverseList(list, PrintInt);

    // 长度
    printf("链表长度：%d\n", GetLength(list));

    // 按值查找
    Node* find = FindNode(list, INT_TO_DATA(10));
    if (find) {
        printf("找到节点：%d\n", DATA_TO_INT(find->data));
    }

    // 按位置查找
    Node* posNode = FindNodeByPos(list, 2);
    if (posNode) {
        printf("第2个节点：%d\n", DATA_TO_INT(posNode->data));
    }

    InsertByPos(list, 2, INT_TO_DATA(15));
    printf("在第2位插入15后：");
    TraverseList(list, PrintInt);

    InsertByPos(list, 5, INT_TO_DATA(25));
    printf("在第5位插入25后：");
    TraverseList(list, PrintInt);

    // 逆置
    ReverseList(list);
    printf("逆置后：");
    TraverseList(list, PrintInt);

    // 交换第1个和第2个节点
    SwapNode(list->next, list->next->next);
    printf("交换后：");
    TraverseList(list, PrintInt);

    // 测试删除第2个节点
    DeleteByPos(list, 2);
    printf("删除第2个节点后：");
    TraverseList(list, PrintInt);

    // 插入后再删
    InsertByPos(list, 2, INT_TO_DATA(100));
    printf("在第2位插入100后：");
    TraverseList(list, PrintInt);

    DeleteByPos(list, 3);
    printf("删除第3个节点后：");
    TraverseList(list, PrintInt);

    // 合并链表
    Node* listA = CreateSentinelList();
    Node* listB = CreateSentinelList();
    AddTail(listA, INT_TO_DATA(1)); AddTail(listA, INT_TO_DATA(3)); AddTail(listA, INT_TO_DATA(5));
    AddTail(listB, INT_TO_DATA(2)); AddTail(listB, INT_TO_DATA(4)); AddTail(listB, INT_TO_DATA(6));
    Node* merged = MergeSortedList(listA, listB, IntCmp);
    printf("合并有序链表：");
    TraverseList(merged, PrintInt);

    DestroyList(list);
    DestroyList(listA);
    DestroyList(listB);
    DestroyList(merged);

    printf("\n=== 队列测试 ===\n");
    Queue* q = CreateQueue();
    EnQueue(q, INT_TO_DATA(1));
    EnQueue(q, INT_TO_DATA(2));
    EnQueue(q, INT_TO_DATA(3));
    printf("出队：");
    while (!IsEmpty(q)) printf("%d ", DATA_TO_INT(DeQueue(q)));
    printf("\n");

    DestroyQueue(q);
}