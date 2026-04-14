#ifndef _LIST_H
#define _LIST_H

#define ListMkInc(T)                                                         \
T* ListInit##T();\
int ListEmpty##T(T* head);\
void ListInsertAfter##T(T* pos, T* node);\
void ListInsertAfter##T(T* pos, T* node);\
void ListInsertBefore##T(T* pos, T* node);\
void ListInsertHead##T(T* head, T* node);\
void ListInsertTail##T(T* head, T* node);\
void ListErase##T(T* node);\
void ListEraseTail##T(T* head);\
int ListSize##T(T* head);\
T* ListFind##T(T* head, int (*cmp)(T*, void*), void* key);\
void ListClear##T(T* head, void (*FreeData)(T*));\
void ListDestroy##T(T* head, void (*FreeData)(T*));\
void ListSwap##T(T* a, T* b);\
void ListSwapByPos##T(T* head, int i, int j);

#define ListTemp(T)		                                                            \
T* ListInit##T() {                                                                   \
    T* head = (T*)malloc(sizeof(T));	                                            \
    if (head == NULL) exit(1);	                                                \
    head->prev = head;                                                          \
    head->next = head;                                                           \
    return head;                                                            \
}                                                                             \
/* 判断链表是否为空 */                                                        \
int ListEmpty##T(T* head) {                                               \
    return head->next == head;                                              \
}                                                                           \
/* 在指定节点后插入新节点 */                                                \
void ListInsertAfter##T(T* pos, T* node) {                                \
    node->next = pos->next;                                                 \
    node->prev = pos;                                                       \
    pos->next->prev = node;                                                 \
    pos->next = node;                                                       \
}                                                                           \
/* 在指定节点前插入新节点 */            \
void ListInsertBefore##T(T* pos, T* node) {                               \
    node->prev = pos->prev;                                                 \
    node->next = pos;                                                       \
    pos->prev->next = node;                                                 \
    pos->prev = node;                                                       \
}                                                                           \
/* 头插法：在哨兵节点后插入（链表头部） */                                     \
void ListInsertHead##T(T* head, T* node) {                                 \
    ListInsertAfter##T(head, node);                                       \
}                                                                           \
/* 尾插法：在哨兵节点前插入（链表尾部） */                                     \
void ListInsertTail##T(T* head, T* node) {                                  \
    ListInsertBefore##T(head, node);                                      \
}                                                                           \
                                                                            \
/* 删除指定节点（假设节点一定存在且不是哨兵节点） */                           \
void ListErase##T(T* node) {                                              \
    node->prev->next = node->next;                                          \
    node->next->prev = node->prev;                                          \
    node->prev = NULL;                                                      \
    node->next = NULL;                                                      \
}                                                                           \
                                                                            \
/* 头删：删除第一个有效节点 */                                                \
void ListEraseHead##T(T* head) {                                           \
    if (!ListEmpty##T(head)) {                                            \
        ListErase##T(head->next);                                         \
    }                                                                       \
}                                                                           \
                                                                            \
/* 尾删：删除最后一个有效节点 */                                              \
void ListEraseTail##T(T* head) {                                            \
    if (!ListEmpty##T(head)) {                                            \
        ListErase##T(head->prev);                                         \
    }                                                                       \
}                                                                           \
                                                                            \
/* 获取链表长度（遍历计数） */                                                \
int ListSize##T(T* head) {                                                \
    int count = 0;                                                          \
    T* cur = head->next;                                                    \
    while (cur != head) {                                                   \
        count++;                                                            \
        cur = cur->next;                                                    \
    }                                                                       \
    return count;                                                           \
}                                                                           \
/* 查找节点：根据条件查找（使用函数指针比较） */                               \
T* ListFind##T(T* head, int (*cmp)(T*, void*), void* key) {               \
    T* cur = head->next;                                                    \
    while (cur != head) {                                                   \
        if (cmp(cur, key)) return cur;                                      \
        cur = cur->next;                                                    \
    }                                                                       \
    return NULL;                                                            \
}                                                                           \
/* 清空链表：删除所有有效节点，保留哨兵节点 */                                 \
void ListClear##T(T* head, void (*FreeData)(T*)) {                       \
    T* cur = head->next;                                                    \
    while (cur != head) {                                                   \
        T* next = cur->next;                                                \
        if (FreeData) FreeData(cur);                                      \
        free(cur);                                                          \
        cur = next;                                                         \
    }                                                                       \
    head->prev = head;                                                      \
    head->next = head;                                                      \
}                                                                           \
/* 销毁整个链表：包括哨兵节点 */                                              \
void ListDestroy##T(T* head, void (*FreeData)(T*)) {                     \
    ListClear##T(head, FreeData);                                        \
    free(head);                                                             \
}\
/* 交换链表中两个节点（自动处理相邻和不相邻情况） */                           \
void ListSwap##T(T* a, T* b) {                                            \
    if (a == NULL || b == NULL || a == b) return;                           \
                                                                            \
    /* 确保 a 在 b 前面（简化后续判断） */                                     \
    if (a->next == b) {                                                     \
        /* a 和 b 相邻，a 在前 */                                             \
        T* a_prev = a->prev;                                                \
        T* b_next = b->next;                                                \
                                                                            \
        a_prev->next = b;                                                   \
        b->prev = a_prev;                                                   \
                                                                            \
        b->next = a;                                                        \
        a->prev = b;                                                        \
                                                                            \
        a->next = b_next;                                                   \
        b_next->prev = a;                                                   \
    } else if (b->next == a) {                                              \
        /* b 和 a 相邻，b 在前，复用逻辑 */                                    \
        T* b_prev = b->prev;                                                \
        T* a_next = a->next;                                                \
                                                                            \
        b_prev->next = a;                                                   \
        a->prev = b_prev;                                                   \
                                                                            \
        a->next = b;                                                        \
        b->prev = a;                                                        \
                                                                            \
        b->next = a_next;                                                   \
        a_next->prev = b;                                                   \
    } else {                                                                \
        /* 不相邻情况：通用交换 */                                             \
        T* a_prev = a->prev;                                                \
        T* a_next = a->next;                                                \
        T* b_prev = b->prev;                                                \
        T* b_next = b->next;                                                \
                                                                            \
        /* 交换邻居的指向 */                                                   \
        a_prev->next = b;                                                   \
        a_next->prev = b;                                                   \
        b_prev->next = a;                                                   \
        b_next->prev = a;                                                   \
                                                                            \
        /* 交换 a 和 b 自身的指针 */                                           \
        a->prev = b_prev;                                                   \
        a->next = b_next;                                                   \
        b->prev = a_prev;                                                   \
        b->next = a_next;                                                   \
    }                                                                       \
}                                                                           \
                                                                            \
/* 按位置交换：交换链表中的第 i 个和第 j 个节点（从1开始计数） */               \
void ListSwapByPos##T(T* head, int i, int j) {                            \
    if (i == j || i < 1 || j < 1) return;                                   \
                                                                            \
    /* 找到第 i 个节点 */                                                      \
    T* node_i = head->next;                                                 \
    int pos = 1;                                                            \
    while (node_i != head && pos < i) {                                     \
        node_i = node_i->next;                                              \
        pos++;                                                              \
    }                                                                       \
    if (node_i == head) return;                                             \
                                                                            \
    /* 找到第 j 个节点 */                                                      \
    T* node_j = head->next;                                                 \
    pos = 1;                                                                \
    while (node_j != head && pos < j) {                                     \
        node_j = node_j->next;                                              \
        pos++;                                                              \
    }                                                                       \
    if (node_j == head) return;                                             \
                                                                            \
    ListSwap##T(node_i, node_j);                                          \
}                       

#endif /* _LIST_H */
