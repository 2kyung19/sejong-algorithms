#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int H[100];
int n;

void inPlaceHeapSort();
void BuildHeap();
void downHeap(int i, int size);
void swapElements(int i, int j);
void printArray();

int main(void) {
    int i;

    scanf("%d", &n);
   
    for (i = 1; i <= n; i++) {
        scanf("%d", &H[i]);
    }

    inPlaceHeapSort();

    printArray();

    return 0;
}

void inPlaceHeapSort() {
    BuildHeap(); //phase 1
  
    for (int i = n; i > 1; i--) { //phase 2
        swapElements(1, i);
        downHeap(1, i - 1);
    }
}

void BuildHeap() {
    for (int i = n / 2; i > 0; i--) {
        downHeap(i, n);
    }
}

void downHeap(int i, int size) {
    int bigger;

    if (i * 2 > size) return; //자식이 없는 경우

    bigger = i * 2;
    if (size >= i * 2 + 1 && H[i * 2] < H[i * 2 + 1]) {
        bigger = i * 2 + 1;
    }

    if (H[i] >= H[bigger]) return;

    swapElements(i, bigger);

    downHeap(bigger, size);
}

void swapElements(int i, int j) {
    int temp;

    temp = H[i];
    H[i] = H[j];
    H[j] = temp;
}

void printArray() {
    for (int i = 1; i <= n; i++) {
        printf(" %d", H[i]);
    }
    printf("\n");
}