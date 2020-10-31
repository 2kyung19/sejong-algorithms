#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node {
    int e;
    struct Node* next;
    struct Node* knext;
}Node;

Node* getNode(int e) {
    Node* new = (Node*)malloc(sizeof(Node));

    new->e = e;
    new->next = NULL;
    new->knext = NULL;

    return new;
}

void insert(Node* L, int k, int e)
{
    Node* p = L;
    Node* new;

    for (int i = 0; i < k; i++) {
        p = p->next;
    }

    new = getNode(e);
    new->knext = p->knext;
    p->knext = new;
}

int removeE(Node* L, int k, int e)
{
    int n = 0;
    Node* p = L;

    for (int i = 0; i < k; i++) {
        p = p->next;
    }

    do {
        n++;
        if (p->knext->e == e) {
            p->knext = p->knext->knext;

            return n;
        }
        p = p->knext;
    } while (p->knext);

    return 0;
}

int find(Node* L, int k, int e)
{
    int n = 0;
    Node* p = L;

    for (int i = 0; i < k; i++) {
        p = p->next;
    }

    while (p = p->knext) {
        n++;
        if (p->e == e)
            return n;
    }

    return 0;
}

void print(Node* L, int M)
{
    Node* p = L;
    Node* q;

    for (int i = 0; i < M; i++) {
        q = p;
        while (q = q->knext) {
            printf(" %d", q->e);
        }
        p = p->next;
    }
    printf("\n");
}

int main()
{
    Node* L, * node;
    int M, x, i;

    scanf("%d", &M);

    L = getNode(M - 1);

    for (i = M - 2; i >= 0; i--) {
        node = getNode(i);
        node->next = L;
        L = node;
    }

    char cmd;

    while (1) {
        scanf("%c", &cmd);

        switch (cmd) {
        case 'i':
            scanf("%d", &x);
            insert(L, x % M, x);
            break;
        case 's':
            scanf("%d", &x);
            printf("%d\n", find(L, x % M, x));
            break;
        case 'd':
            scanf("%d", &x);
            printf("%d\n", removeE(L, x % M, x));
            break;
        case 'p':
            print(L, M);
            break;
        case 'e':
            exit(0);
        }
    }
}