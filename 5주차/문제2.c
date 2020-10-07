#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void inPlaceQuickSort(int L[], int l, int r);
int findPivot(int L[], int l, int r);
int inPlacePartition(int L[], int l, int r, int k);
void swapElem(int* x, int* y);

int main(void) {
    int* L;
    int n;
    int i;

    srand(time(NULL));
    
    scanf("%d", &n);
    L = (int*)malloc(sizeof(int) * n);

    for (i = 0; i < n; i++) {
        scanf("%d", &L[i]);
    }

    inPlaceQuickSort(L, 0, n - 1);

    for (i = 0; i < n; i++) {
        printf(" %d", L[i]);
    }

    free(L);

    return 0;
}

void inPlaceQuickSort(int L[], int l, int r) {
    int k,m;
    int a, b;

    if (l >= r) return;

    k = findPivot(L,l,r);
    m = inPlacePartition(L, l, r, k);

    inPlaceQuickSort(L, l, m - 1);
    inPlaceQuickSort(L, m + 1, r);
}

int findPivot(int L[], int l, int r) {
    int pivot[3];
    int i, j;
    int tmp;

    for (i = 0; i < 3; i++) {
        pivot[i] = rand() % (r - l + 1) + l;
        for (j = 0; j < i; j++) {
            if (pivot[j] == pivot[i]) {
                pivot[i] = rand() % (r - l + 1) + l;
                j = 0;
            }
        }
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (L[pivot[i]] > L[pivot[j]]) swapElem(pivot + i, pivot + j);
        }
    }

    return pivot[1];
}

int inPlacePartition(int L[], int l, int r, int k) {
    int p;
    int i, j;

    p = L[k];
    swapElem(&L[k], &L[r]);
    i = l;
    j = r - 1;

    while (i <= j){
        while (i <= j && L[i] <= p){
            i++;
        }
        while (i <= j && L[j] >= p){
            j--;
        }
        if (i < j){
            swapElem(&L[i], &L[j]);
        }

    }
    swapElem(&L[i], &L[r]);
    return i;
}

void swapElem(int* a, int* b){
    int tmp;
    tmp = *b;
    *b = *a;
    *a = tmp;
}