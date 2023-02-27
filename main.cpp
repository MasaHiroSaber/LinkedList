//Created By MasaHiroSaber
//Feb.27, 2023 17:12:34 GMT +08:00

#include <cstdio>
#include "stdlib.h"
#include "time.h"

typedef struct DuLNode {               //双链表结点结构体
    int data;
    DuLNode *prior;
    DuLNode *next;
} DuLNode, *DuLinkedList;

typedef struct DoubleLinkedList {     //双链表的结构体
    DuLNode *head;
    DuLNode *tail;
    int length;
} DoubleLinkedList;


DuLNode *NewDuLNode(int value) {
    //struct DuLNode *node = (DuLNode *) malloc(sizeof (DuLNode));
    //IDE提示:Use auto when initializing with a cast to avoid duplicating the type name
    auto *node = (DuLNode *) malloc(sizeof(DuLNode));
    if (!node) return NULL;
    node->data = value;
    node->prior = NULL;//IDE提示:Use nullptr
    node->next = NULL;
    return node;
}

DoubleLinkedList *CreateDuLinkedList() {     //初始化双链表
    auto *list = (DoubleLinkedList *) malloc(sizeof(DoubleLinkedList));
    if (!list) return NULL;
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    return list;
}
//void init_list(DoubleLinkedList *list) {
//    list->head = NULL;
//    list->tail = NULL;
//    list->length = 0;
//}

void InsertHead(DoubleLinkedList *list, int value) {    //插入头结点
    DuLNode *newNode = NewDuLNode(value);

    if (list->length == 0) {       //链表为空时
        list->head = newNode;
        list->tail = newNode;
    } else {                           //链表不为空时
        newNode->next = list->head;
        list->head->prior = newNode;
        list->head = newNode;
    }
    list->length++;
}

void InsertTail(DoubleLinkedList *list, int value) {    //插入尾结点
    DuLNode *newNode = NewDuLNode(value);

    if (list->length == 0) {        //链表为空时
        list->head = newNode;
        list->tail = newNode;
    } else {                           //链表不为空时
        list->tail->next = newNode;
        newNode->prior = list->tail;
        list->tail = newNode;
    }
    list->length++;
}

int Insert(DoubleLinkedList *list, int index, int value) {
    if (!list) return 0;
    if (index < 0 || index > list->length) return 0;
    if (index == 0) {        //插入位置index等于0时相当于插入头结点
        InsertHead(list, value);
        return 1;
    }
    else if (index == list->length) {        //  插入位置等于链表长度相当于插入尾结点
        InsertTail(list, value);
        return 1;
    }

    DuLNode *p = list->head;
    DuLNode *newNode = NewDuLNode(value);
    index -= 1;                   //从头结点开始往后遍历到插入的前一个位置 //ERROR 1
    while (index--) p = p->next;
    p->next->prior = newNode;   //后一个结点的prior指向newNode
    newNode->next = p->next;    //newNode的next等于p的next，即让newNode的next指向后一个结点
    p->next = newNode;          //p的next指向newNode,即让newNode的前一个结点的next指向newNode
    newNode->prior = p;         //newNode的prior指向前一个结点
    list->length++;
    return 1;
}


//void Output(DoubleLinkedList* list)
//{
//    DuLNode* p = list->head->next;
//    printf("The LinkedList(%d):", list->length);
//    while (p)
//    {
//        printf("%d->", p->data);
//        p = p->next;
//    }
//    printf("NULL\n");
//}

void Output(DoubleLinkedList *list) {
    DuLNode *node = list->head;
    for (int i = 0; i < list->length; ++i) {
        printf("%d->", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

int DestroyDoubleLinkedList(DoubleLinkedList *list) {
    if (!list) return 0;
    while (list->length) {
        DuLNode *p = list->head;
        list->head = list->head->next;
        free(p);
        p = NULL;
        list->length--;
    }
    printf("Destroy the whole list!\n");
    Output(list);
    free(list);
}
int DestroyDoubleLinkedList_2(DoubleLinkedList *list) {
    if (!list) return 0;
    DuLNode *p = list->head->next;
    while (p) {
        list->head->next = p->next;
        free(p);
        list->length--;
        p = list->head->next;
    }
    printf("Destroy the whole list!\n");
    Output(list);
    free(list);
}

int main() {
    srand(time(0));
#define MAX_OP 20
    DoubleLinkedList *list = CreateDuLinkedList();
    for (auto i = 0; i < MAX_OP; i++) {
        int op = rand() % 4;
        int value = rand() % 100;
        int index = rand() % (list->length + 3);
        switch (op) {
            case 0:
            case 1:
            case 2: {
                int code = Insert(list, index, value);
                if (code == 0) printf("ERROR: Insert into the wrong %d position!\n", index);
                else printf("SUCCESS: Insert %d at %d in the list!\n", value, index);
                break;
            }
        }
        Output(list);
    }
    return 0;
}

