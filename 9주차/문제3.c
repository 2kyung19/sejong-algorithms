#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int h(int x, int M);
int hPrime(int x, int q);
void initBucketArray(int* bucket, int M);
int insertItem(int* bucket, int M, int x, int q);
int findElement(int* bucket, int M, int x);
void printTable(int* bucket, int M);

int main(void) {
    char order;
    int* bucket;
    int M, n, q, x;
    int cnt = 0;
    int find;

    scanf("%d %d %d", &M, &n, &q);
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
            printf("%d\n", insertItem(bucket, M, x, q));
            cnt++;
        }
        else if (order == 's') {
            scanf("%d", &x);
            getchar();

            find = findElement(bucket, M, x);
            if (find == -1) printf("%d\n", -1);
            else printf("%d %d\n", find, x);
        }

        else if (order == 'p') {
            printTable(bucket,M);
        }

        else if (order == 'e') {
            printTable(bucket, M);
            free(bucket);
            break;
        }
    }

    return 0;
}

int h(int x, int M) {
    return x % M;
}

int hPrime(int x, int q) {
    return q - (x % q);
}

void initBucketArray(int* bucket, int M) {
    for (int i = 0; i < M; i++) {
        bucket[i] = 0;
    }
}

int insertItem(int* bucket, int M, int x, int q) {
    int i = 1;
    int v = h(x, M);
    int hash = v;

    while (bucket[v] != 0) { //충돌이 안날때까지
        printf("C");
        v = h(hash + (i * hPrime(x, q)), M);
        i++;
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

void printTable(int* bucket, int M) {
    for (int i = 0; i < M; i++) {
        printf(" %d", bucket[i]);
    }
    printf("\n");
}