//
// Created by MasaHiroSaber on 2023/2/28.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node *next;
};

typedef struct LinkedList {
    struct Node head;
    int length;
};

LinkedList *CreateLinkedList() {
    struct LinkedList *p = (struct LinkedList *) malloc(sizeof(LinkedList));
    if (!p) return NULL;
    p->head.next = NULL;
    p->length = 0;
    return p;
}

struct Node *NewNode(int value) {
    struct Node *p = (Node *) malloc(sizeof(Node));
    if (!p) return NULL;
    p->data = value;
    p->next = NULL;
    return p;
}

int Insert(LinkedList *linkedlist, int index, int value) {
    if (!linkedlist)return 0;
    if (index < 0 || index > linkedlist->length) return 0;
    Node *p = &(linkedlist->head);
    //head不包含数据
    Node *newNode = NewNode(value);
    //找到待插入的位置index
    while (index--) p = p->next;
    newNode->next = p->next;
    p->next = newNode;
    linkedlist->length++;
    return 1;
}

int Delete(LinkedList *linkedlist, int index) {
    if (!linkedlist)return 0;
    if (index < 0 || index >= linkedlist->length) return 0;
    Node *p = &(linkedlist->head);
    while (index--) p = p->next;
    //实际删除的节点q
    Node *q = p->next;
    p->next = q->next;
    free(q);
    linkedlist->length--;
    return 1;
}

void Output(LinkedList *linkedlist) {
    Node *p = linkedlist->head.next;
    printf("The LinkedList(%d):", linkedlist->length);
    while (p) {
        printf("%d->", p->data);
        p = p->next;
    }
    printf("NULL\n");
}

int DestroyLinkedList(LinkedList *linkedlist) {
    if (!linkedlist)return 0;
    Node *p = linkedlist->head.next;
    while (p) {
        linkedlist->head.next = p->next;
        free(p);
        linkedlist->length--;
        p = linkedlist->head.next;
    }
    printf("Destroy the whole list!\n");
    Output(linkedlist);
    free(linkedlist);
}


int main() {
    srand(time(0));
#define MAX_OP 20
    LinkedList *linkedlist = CreateLinkedList();
    for (auto i = 0; i < MAX_OP; i++) {
        int op = rand() % 4;
        int value = rand() % 100;
        int index = rand() % (linkedlist->length + 3);
        switch (op) {
            case 0:
            case 1:
            case 2: {
                int code = Insert(linkedlist, index, value);
                if (code == 0) printf("ERROR: Insert into the wrong %d position!\n", index);
                else printf("SUCCESS: Insert %d at %d in the linkedlist!\n", value, index);
                break;
            }
            case 3: {
                int code = Delete(linkedlist, index);
                if (code == 0) printf("ERROR: Delete at the wrong %d position!\n", index);
                else printf("SUCCESS: Delete a data at %d in the linkedlist!\n", index);
                break;
            }
        }
        Output(linkedlist);
    }

    printf("\nFirst Data = %d\n:", linkedlist->head.next->data);
    printf("***************************************************\n");
    DestroyLinkedList(linkedlist);
    return 0;
}