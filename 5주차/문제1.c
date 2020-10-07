#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node {
    int elem;
    struct node* next;
}NODE;

NODE* getNode() {
    NODE* node = (NODE*)malloc(sizeof(NODE));

    node->next = NULL;

    return node;
}

NODE* insertList(NODE* T, int elem);
NODE* mergeSort(NODE* L, int n);
void partition(NODE* L, int k, NODE** L1, NODE** L2);
NODE* merge(NODE* L1, NODE* L2);
void printList(NODE* L);
void freeNode(NODE** L);

int main(void) {
    NODE* L = getNode(), * T = L;
    int n, elem;
    int i;

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d", &elem);

        if (i == 0) {
            L->elem = elem;
            continue;
        }
        T = insertList(T, elem); //트레일러 노드 이용
    }

    L = mergeSort(L, n);

    printList(L);

    freeNode(&L);

    return 0;
}

NODE* insertList(NODE* T, int elem) {
    NODE* node = getNode();

    node->elem = elem;
    T->next = node;

    return node;
}

NODE* mergeSort(NODE* L, int n) {
    NODE* L1 = NULL, * L2 = NULL;

    if (n < 2) return L;

    partition(L, n / 2, &L1, &L2);

    L1 = mergeSort(L1, n / 2);
    L2 = mergeSort(L2, n - n / 2);

    L = merge(L1, L2);

    return L;
}

void partition(NODE* L, int k, NODE** L1, NODE** L2) {
    NODE* p = L;
    *L1 = p;

    for (int i = 0; i < k - 1; i++) {
        p = p->next;
    }

    *L2 = p->next;
    p->next = NULL;
}

NODE* merge(NODE* L1, NODE* L2) {
    NODE* L;
    NODE* l1, * l2, * p;

    if (L1 == NULL) return L2;
    if (L2 == NULL) return L1;

    l1 = L1; l2 = L2;

    if (l1->elem > l2->elem) { //초기화
        L = l2;
        l2 = l2->next;
    }
    else {
        L = l1;
        l1 = l1->next;
    }
    p = L;

    while (l1 != NULL && l2 != NULL) { //반복문
        if (l1->elem > l2->elem) {
            p->next = l2;
            l2 = l2->next;
        }
        else {
            p->next = l1;
            l1 = l1->next;
        }
        p = p->next;
    }
    while (l1 != NULL) {
        p->next = l1;
        l1 = l1->next;
        p = p->next;
    }

    while (l2 != NULL) {
        p->next = l2;
        l2 = l2->next;
        p = p->next;
    }

    return L;
}

void printList(NODE* L) {
    NODE* p = L;

    while (p != NULL) {
        printf(" %d", p->elem);
        p = p->next;
    }
    printf("\n");
}

void freeNode(NODE** L) {
    NODE* p, * q;

    p = *L;

    while (p != NULL) {
        q = p;
        p = p->next;
        free(q);
    }
}