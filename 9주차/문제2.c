#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int h(int x, int M);
void initBucketArray(int* bucket, int M);
int insertItem(int* bucket, int M, int x);
int findElement(int* bucket, int M, int x);

int main(void) {
    char order;
    int* bucket;
    int M, n, x;
    int cnt = 0;
    int find;

    scanf("%d %d", &M, &n);
    getchar();

    bucket = (int*)malloc(sizeof(int) * M);
    initBucketArray(bucket, M);

    while (1) {
        scanf("%c", &order);
        getchar();

        if (order == 'i') {
            scanf("%d", &x);
            getchar();

            if (cnt >= n) continue;
            printf("%d\n",insertItem(bucket, M, x));
            cnt++;
        }
        else if (order == 's') {
            scanf("%d", &x);
            getchar();

            find = findElement(bucket, M, x);
            if (find == -1) printf("%d\n", -1);
            else printf("%d %d\n", find, x);
        }

        else if (order == 'e') break;
    }
    
    free(bucket);
    return 0;
}

int h(int x, int M) {
    return x % M;
}

void initBucketArray(int* bucket, int M) {
    for (int i = 0; i < M; i++) {
        bucket[i] = 0;
    }
}

int insertItem(int* bucket, int M, int x) {
    int v = h(x, M);

    while (bucket[v] != 0) { //충돌이 안날때까지
        printf("C");
        v = h(v + 1, M);
    }

    bucket[v] = x; //저장 성공

    return v;
}

int findElement(int* bucket, int M, int x) {
    for (int i = 0; i < M; i++) {
        if (bucket[i] == x) {
            return i;
        }
    }

    return -1;
}