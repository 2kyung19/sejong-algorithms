#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int H[100]; //heap
int n = 0; //heap size

void insertItem(int key);
int removeMax();
void upHeap(int i);
void downHeap(int i);
void printHeap();
void swapElements(int i, int j);

int main(void) {
    char order;
    int key;

    while (1) {
        scanf("%c", &order);

        if (order == 'q') break;

        else if (order == 'i') {
            scanf("%d", &key);
            insertItem(key);

            printf("0\n"); //삽입 완료
        }

        else if (order == 'd') {
            printf("%d\n", removeMax());
        }

        else if (order == 'p') {
            printHeap();
        }

    }

    return 0;
}

void insertItem(int key) {
    n += 1;
    H[n] = key;
    upHeap(n);
}

int removeMax() {
    int k;

    k = H[1];
    H[1] = H[n];

    n -= 1;
    downHeap(1);

    return k;
}

void upHeap(int i) {
    if (i == 1) return; //root 인 경우
    if (H[i] <= H[i / 2]) return; //부모보다 작으면

    swapElements(i, i / 2);
    upHeap(i / 2);
}

void downHeap(int i) {
    int bigger;

    if (i * 2 > n) return; //자식이 없으면

    bigger = i * 2;
    if (H[i * 2 + 1] > H[i * 2]) {
        bigger = i * 2 + 1;
    }

    if (H[i] >= H[bigger]) return; //현재 노드가 자식보다 크다면

    swapElements(i, bigger);

    downHeap(bigger);
}

void printHeap() {
    for (int i = 1; i <= n; i++) {
        printf(" %d", H[i]);
    }
    printf("\n");
}

void swapElements(int i, int j) {
    int temp;

    temp = H[j];
    H[j] = H[i];
    H[i] = temp;
}