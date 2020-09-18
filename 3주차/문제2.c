#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int H[100]; //heap
int n = 0; //heap size

void buildHeap();
void downHeap(int i);
void printHeap();
void swapElements(int i, int j);

int main(void) {
    int i;

    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        scanf("%d", &H[i]);
    }

    buildHeap();

    printHeap();

    return 0;
}

void buildHeap() {
    for (int i = n / 2; i >= 1; i--) {
        downHeap(i);
    }
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
