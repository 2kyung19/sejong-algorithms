#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int findElement(int* A, int k, int n);
int rFE(int* A, int k, int l, int r);

int main(void) {
    int* A;
    int n, k;
    int i;

    scanf("%d %d", &n, &k);
    A = (int*)malloc(sizeof(int) * n);

    for (i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    printf(" %d", findElement(A, k, n));

    free(A);

    return 0;
}

int findElement(int* A, int k, int n) {
    return rFE(A, k, 0, n - 1);
}

int rFE(int* A, int k, int l, int r) {
    int mid = r;

    if (l > r) return mid;

    mid = (l + r) / 2;
    
    if (A[mid] == k) return mid;
    else if (A[mid] > k) return rFE(A, k, l, mid - 1);
    else return rFE(A, k, mid + 1, r);
}