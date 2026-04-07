#include "framework.h"
#include "lib.h"
#include "patient.h"

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} IntNode;

ListTemp(Patient);
ListTemp(IntNode);

void ListTest() {
    IntNode* list = ListInitIntNode();
    IntNode* node1 = malloc(sizeof(IntNode));
    node1->data = 10;

    IntNode* node2 = malloc(sizeof(IntNode));
    node2->data = 20;

    IntNode* node3 = malloc(sizeof(IntNode));
    node3->data = 30;
    IntNode* node4 = malloc(sizeof(IntNode));
    node4->data = 40;
    IntNode* node5 = malloc(sizeof(IntNode));
    node5->data = 50;
    IntNode* node6 = malloc(sizeof(IntNode));
    node6->data = 60;
    IntNode* node7 = malloc(sizeof(IntNode));
    node7->data = 70;
    IntNode* node8 = malloc(sizeof(IntNode));
    node8->data = 80;
    // 插入
    ListInsertTailIntNode(list, node1);   // 尾插 10
    ListInsertHeadIntNode(list, node2);  // 头插 20
    ListInsertTailIntNode(list, node3);
    ListInsertTailIntNode(list, node4);
    ListInsertTailIntNode(list, node5);
    ListInsertTailIntNode(list, node6);
    ListInsertTailIntNode(list, node7);
    ListInsertTailIntNode(list, node8);

    ListEraseIntNode(node7);
    printf("%d\n", ListSizeIntNode(list));

    // 遍历打印
    IntNode* cur = list->next;
    while (cur != list) {
        printf("%d ", cur->data);  // 输出: 20 10
        cur = cur->next;
    }
    
    ListSwapByPosIntNode(list, 5, 6);
    printf("\n");
    
    cur = list->next;
    while (cur != list) {
        printf("%d ", cur->data);  // 输出: 20 10
        cur = cur->next;
    }

    // 销毁
    ListDestroyIntNode(list, NULL);

    Patient* p = ListInitPatient();
    Patient* node9 = malloc(sizeof(Patient));
    node9->age = 80;
    ListInsertTailPatient(p, node9);
    printf("\n%d", ListSizePatient(p));
    ListDestroyPatient(p, NULL);
}
