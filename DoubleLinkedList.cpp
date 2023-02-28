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


DuLNode *NewDuLNode(int value) {        //创建一个新结点
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

int Insert(DoubleLinkedList *list, int index, int value) {      //任意位置插入结点，其中包括头结点与尾结点
    if (!list) return 0;
    if (index < 0 || index > list->length) return 0;
    else if (index == 0) {        //插入位置index等于0时相当于插入头结点
        InsertHead(list, value);
        return 1;
    } else if (index == list->length) {        //  插入位置等于链表长度相当于插入尾结点
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

void Output(DoubleLinkedList *list) {       //打印当前链表
    DuLNode *node = list->head;
    printf("The LinkedList(%d):", list->length);
    for (int i = 0; i < list->length; ++i) {
        printf("%d->", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

void DeleteHead(DoubleLinkedList *list) {       //删除头结点
    if (list->length == 0) {
        return;
    }
    if (list->length == 1) {
        free(list->head);
        //CreateDuLinkedList();     //重新初始化双链表
        list->head = NULL;
        list->tail = NULL;
        list->length = 0;
        return;
    }

    DuLNode *p = list->head;
    list->head = p->next;
    list->head->prior = NULL;

    free(p);
    p = NULL;
    list->length--;
}

void DeleteTail(DoubleLinkedList *list) {       //删除尾结点
    if (list->length == 0) {
        return;
    }
    if (list->length == 1) {
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        list->length = 0;
        return;
    }

    DuLNode *p = list->tail;
    list->tail = p->prior;
    list->tail->next = NULL;

    free(p);
    p = NULL;
    list->length--;
}

int Delete(DoubleLinkedList *list, int index) {     //删除任意位置结点
    if (!list) return 0;
    if (index < 0 || index >= (list->length) - 1) return 0;     //0->Tail index = length - 1
    else if (index == 0) {
        DeleteHead(list);
        return 1;
    } else if (index == (list->length) - 1) {
        DeleteTail(list);
        return 1;
    }

    DuLNode *p = list->head;
    while (index--) p = p->next;
    p->prior->next = p->next;
    p->next->prior = p->prior;

    free(p);
    p = NULL;
    list->length--;
    return 1;

}

int GetNodeValue(DoubleLinkedList *list, int index) {       //获取链表内任意结点的Value
    if (!list) return 0;
    if (index < 0 || index > list->length) return 0;
    DuLNode *p = NULL;
    if (index < (list->length) / 2) {             //当index的值在链表前部时，从头结点开始遍历
        p = list->head;
        while (index--) p = p->next;
    } else {                                       //当index的值在链表后部时，从尾结点开始遍历
        p = list->tail;
        int i = (list->length) - index - 1;
        while (i--) p = p->prior;
    }

    int value = p->data;
    return value;                               //返回Value值
}

//int ModifyNodeValue(DoubleLinkedList *list,int index,int value){
//    DuLNode *p =
//}

int DestroyDoubleLinkedList(DoubleLinkedList *list) {       //释放链表
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

//int DestroyDoubleLinkedList_2(DoubleLinkedList *list) {
//    if (!list) return 0;
//    DuLNode *p = list->head->next;
//    while (p) {
//        list->head->next = p->next;
//        free(p);
//        list->length--;
//        p = list->head->next;
//    }
//    printf("Destroy the whole list!\n");
//    Output(list);
//    free(list);
//}



int main() {            //主函数从老师发的单链表文件里的主函数拿过来用了，用来测试代码有无问题
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
            case 3: {
                int code = Delete(list, index);
                if (code == 0) printf("ERROR: Delete at the wrong %d position!\n", index);
                else printf("SUCCESS: Delete a data at %d in the list!\n", index);
                break;
            }
        }
        Output(list);
    }
    int i;
    printf("Enter a position : ");
    scanf_s("%d", &i);
    printf("Value = %d in the position!\n", GetNodeValue(list, i));
    printf("***************************************************\n");
    DestroyDoubleLinkedList(list);
    return 0;
}

