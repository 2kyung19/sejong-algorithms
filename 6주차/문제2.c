#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int findElement(int* A, int k, int n);

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
    int mid;
    int l = 0 , r = n - 1;

    while (l <= r) {
        mid = (l + r) / 2;

        if (A[mid] == k) return mid;
        else if (A[mid] > k) r = mid - 1;
        else l = mid + 1;
    }

    if (l == 0 && A[l] < k) return n;

    return l;
}