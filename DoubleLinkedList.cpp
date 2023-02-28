//Created By MasaHiroSaber
//Feb.27, 2023 17:12:34 GMT +08:00

#include <cstdio>
#include "stdlib.h"
#include "time.h"

typedef struct DuLNode {               //˫������ṹ��
    int data;
    DuLNode *prior;
    DuLNode *next;
} DuLNode, *DuLinkedList;

typedef struct DoubleLinkedList {     //˫����Ľṹ��
    DuLNode *head;
    DuLNode *tail;
    int length;
} DoubleLinkedList;


DuLNode *NewDuLNode(int value) {        //����һ���½��
    //struct DuLNode *node = (DuLNode *) malloc(sizeof (DuLNode));
    //IDE��ʾ:Use auto when initializing with a cast to avoid duplicating the type name
    auto *node = (DuLNode *) malloc(sizeof(DuLNode));
    if (!node) return NULL;
    node->data = value;
    node->prior = NULL;//IDE��ʾ:Use nullptr
    node->next = NULL;
    return node;
}

DoubleLinkedList *CreateDuLinkedList() {     //��ʼ��˫����
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

void InsertHead(DoubleLinkedList *list, int value) {    //����ͷ���
    DuLNode *newNode = NewDuLNode(value);

    if (list->length == 0) {       //����Ϊ��ʱ
        list->head = newNode;
        list->tail = newNode;
    } else {                           //����Ϊ��ʱ
        newNode->next = list->head;
        list->head->prior = newNode;
        list->head = newNode;
    }
    list->length++;
}

void InsertTail(DoubleLinkedList *list, int value) {    //����β���
    DuLNode *newNode = NewDuLNode(value);

    if (list->length == 0) {        //����Ϊ��ʱ
        list->head = newNode;
        list->tail = newNode;
    } else {                           //����Ϊ��ʱ
        list->tail->next = newNode;
        newNode->prior = list->tail;
        list->tail = newNode;
    }
    list->length++;
}

int Insert(DoubleLinkedList *list, int index, int value) {      //����λ�ò����㣬���а���ͷ�����β���
    if (!list) return 0;
    if (index < 0 || index > list->length) return 0;
    else if (index == 0) {        //����λ��index����0ʱ�൱�ڲ���ͷ���
        InsertHead(list, value);
        return 1;
    } else if (index == list->length) {        //  ����λ�õ����������൱�ڲ���β���
        InsertTail(list, value);
        return 1;
    }

    DuLNode *p = list->head;
    DuLNode *newNode = NewDuLNode(value);
    index -= 1;                   //��ͷ��㿪ʼ��������������ǰһ��λ�� //ERROR 1
    while (index--) p = p->next;
    p->next->prior = newNode;   //��һ������priorָ��newNode
    newNode->next = p->next;    //newNode��next����p��next������newNode��nextָ���һ�����
    p->next = newNode;          //p��nextָ��newNode,����newNode��ǰһ������nextָ��newNode
    newNode->prior = p;         //newNode��priorָ��ǰһ�����
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

void Output(DoubleLinkedList *list) {       //��ӡ��ǰ����
    DuLNode *node = list->head;
    printf("The LinkedList(%d):", list->length);
    for (int i = 0; i < list->length; ++i) {
        printf("%d->", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

void DeleteHead(DoubleLinkedList *list) {       //ɾ��ͷ���
    if (list->length == 0) {
        return;
    }
    if (list->length == 1) {
        free(list->head);
        //CreateDuLinkedList();     //���³�ʼ��˫����
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

void DeleteTail(DoubleLinkedList *list) {       //ɾ��β���
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

int Delete(DoubleLinkedList *list, int index) {     //ɾ������λ�ý��
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

int GetNodeValue(DoubleLinkedList *list, int index) {       //��ȡ�������������Value
    if (!list) return 0;
    if (index < 0 || index > list->length) return 0;
    DuLNode *p = NULL;
    if (index < (list->length) / 2) {             //��index��ֵ������ǰ��ʱ����ͷ��㿪ʼ����
        p = list->head;
        while (index--) p = p->next;
    } else {                                       //��index��ֵ�������ʱ����β��㿪ʼ����
        p = list->tail;
        int i = (list->length) - index - 1;
        while (i--) p = p->prior;
    }

    int value = p->data;
    return value;                               //����Valueֵ
}

//int ModifyNodeValue(DoubleLinkedList *list,int index,int value){
//    DuLNode *p =
//}

int DestroyDoubleLinkedList(DoubleLinkedList *list) {       //�ͷ�����
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



int main() {            //����������ʦ���ĵ������ļ�����������ù������ˣ��������Դ�����������
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

