#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    int elem;
    struct node* next;
}NODE;

NODE* getNode(int elem) {
    NODE* node;

    node = (NODE*)malloc(sizeof(NODE));
    node->next = NULL;
    node->elem = elem;

    return node;
}

int h(int x, int M);
void initBucketArray(NODE** bucket, int M);
void insertItem(NODE** bucket, int M, int x);
int findElement(NODE** bucket, int M, int x);
int removeElement(NODE** bucket, int M, int x);
void printBucketArray(NODE** bucket, int M);
void freeNode(NODE** bucket, int M);

int main(void) {
    char order;
    int M, x;
    NODE** bucket;

    scanf("%d", &M);
    getchar();

    bucket = (NODE**)malloc(sizeof(NODE*) * M);
    initBucketArray(bucket, M);

    while (1) {
        scanf("%c", &order);
        getchar();

        if (order == 'i' || order == 's' || order == 'd') {
            scanf("%d", &x);
            getchar();

            if (order == 'i') insertItem(bucket, M, x);
            else if (order == 's') printf("%d\n", findElement(bucket, M, x));
            else if (order == 'd') printf("%d\n", removeElement(bucket, M, x));
        }
        else if (order == 'p') printBucketArray(bucket,M);
        else if (order == 'e') break;

    }

    freeNode(bucket, M);
    free(bucket);

    return 0;
}

int h(int x, int M) {
    return x % M;
}

void initBucketArray(NODE** bucket, int M) {
    for (int i = 0; i < M; i++) {
        bucket[i] = NULL;
    }
}

void insertItem(NODE** bucket, int M, int x) {
    NODE* node = getNode(x);
    NODE* tmp;
    int v = h(x, M);
    
    if (bucket[v] == NULL) bucket[v] = node;
    else {
        tmp = bucket[v];
        bucket[v] = node;
        node->next = tmp;
    }
}

int findElement(NODE** bucket, int M, int x) {
    NODE* node;
    int v = h(x, M);
    int cnt = 0;

    if (bucket[v] == NULL) return 0; //버켓리스트가 null

    node = bucket[v];
    while (node != NULL) {
        cnt++;
        if (node->elem == x) return cnt;

        node = node->next;
    }

    return 0; //버켓리스트에 없는 경우
}

int removeElement(NODE** bucket, int M, int x) {
    NODE* node, * del, * before;
    int v = h(x, M);
    int cnt = findElement(bucket,M,x);

    if (cnt == 0) return 0;
    
    node = before = del = bucket[v];

    for (int i = 1; i < cnt; i++) {
        if (i == cnt - 2) before = node; //중간에 껴있다면
        node = node->next;
    }
    del = node;

    if (del->next == NULL) { //tail인 경우
        if (bucket[v] == del) bucket[v] = NULL; //원소가 하나였던 경우
        else before->next = NULL;
    }
    
    else {
        if (bucket[v] == del) bucket[v] = del->next;//head인 경우
        else before->next = del->next;
    }
    
    free(del);

    return cnt;
    
}

void printBucketArray(NODE** bucket, int M) {
    NODE* node;

    for (int i = 0; i < M; i++) {
        if (bucket[i] == NULL) continue;
        
        node = bucket[i];
        while (node != NULL) {
            printf(" %d", node->elem);
            node = node->next;
        }
    }
    printf("\n");
}

void freeNode(NODE** bucket, int M) {
    NODE* node, * next;

    for (int i = 0; i < M; i++) {
        if (bucket[i] == NULL) continue;
        node = bucket[i];

        while (node != NULL) {
            next = node->next;
            free(node);
            node = next;
        }
    }
}