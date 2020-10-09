#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>

int n = 100000;
int Limits[] = { 1,100,500,1000 };
int Limit;

int* createArray();
int* copyArray(int* A);
void quickSort(int* A, int mode);
void rQuickSort(int* A, int l, int r, int mode);
void insertionSort(int* A);
int findPrivot(int* A, int l, int r, int mode);
int findIndexOfMedianOfThree(int* A, int a, int b, int c);
void inPlacePartition(int* A, int l, int r, int k, int* a, int* b);
void swapElem(int* a, int* b);

int main(void) {
    int* A, * Acopy;
    int i, j;

    LARGE_INTEGER ticksPerSec;
    LARGE_INTEGER start, end, diff;

    srand(time(NULL));
    QueryPerformanceFrequency(&ticksPerSec);

    A = createArray();

    printf("%5s  %-10s  %-10s  %-10s  %-10s\n", "Limit", "결정적1", "결정적3", "무작위1", "무작위3");
    for (i = 0; i < 4; i++) {
        Limit = Limits[i];

        printf("%-5d", Limit);
        for (j = 0; j < 4; j++) {
            Acopy = copyArray(A); //copy

            QueryPerformanceCounter(&start);
            quickSort(Acopy, j);
            QueryPerformanceCounter(&end);
            diff.QuadPart = end.QuadPart - start.QuadPart;
            printf("  %-10f", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

            free(Acopy);
        }
        printf("\n");
    }

    free(A);

    return 0;
}

int* createArray() {
    int* A = (int*)malloc(sizeof(int) * n);
    long r;

    for (int i = 0; i < n; i++) {
        r = ((((long)rand() << 15) | rand()) % n) + 1;
        A[i] = (int)r;
    }

    return A;
} //A[n] 생성

int* copyArray(int* A) {
    int* Acopy = (int*)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        Acopy[i] = A[i];
    }

    return Acopy;
} //복제

void quickSort(int* A, int mode) {
    rQuickSort(A, 0, n - 1, mode);

    if (Limit > 1) {
        insertionSort(A);
    }
}

void rQuickSort(int* A, int l, int r, int mode) {
    int k;
    int* a = l, * b = r;

    if (r - l >= Limit) {
        k = findPrivot(A, l, r, mode);
        inPlacePartition(A, l, r, k, &a, &b); //a,b에 값 저장

        rQuickSort(A, l, a - 1, mode);
        rQuickSort(A, b + 1, r, mode);
    }
}

void insertionSort(int* A) {
    int* arr = A;
    int i = 1, j, target;

    while (i < n) {
        j = i - 1;
        target = arr[i];
        while (arr[j] > target&& j >= 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = target;
        i++;
    }
}//삽입정렬

int findPrivot(int* A, int l, int r, int mode) {
    long num;

    if (r - l == 1) return l;

    if (mode == 0) return r; //deterministic1
    else if (mode == 1) { //deterministic3
        if (r - l < 3) return l;

        return findIndexOfMedianOfThree(A, l, (l + r) / 2, r);
    }
    if (mode == 2) return ((((long)rand() << 15) | rand()) % (r - l + 1)) + l; //randomized1

    else { //randomized3
        if (r - l < 3) return l;

        int a = ((((long)rand() << 15) | rand()) % (r - l + 1)) + l;
        int b = ((((long)rand() << 15) | rand()) % (r - l + 1)) + l;
        int c = ((((long)rand() << 15) | rand()) % (r - l + 1)) + l;

        return findIndexOfMedianOfThree(A, a, b, c);
    }
}

int findIndexOfMedianOfThree(int* A, int a, int b, int c) {
    if (A[a] >= A[b]) {
        if (A[b] >= A[c]) return b; //a>b>c
        else if (A[a] <= A[c]) return c; //c>a>b
        else return c; //a>c>b
    }
    else if (A[a] >= A[c]) return a; //b>a>c
    else if (A[b] >= A[c]) return c; //b>c>a
    else return b; //c>b>a

} //중앙값

void inPlacePartition(int* A, int l, int r, int k, int* a, int* b) {
    int p = A[k];
    int i, j;

    swapElem(A + k, A + r);

    i = l; j = r - 1;

    //a값
    while (i <= j) {
        while (i <= j && A[i] <= p) i++;
        while (j >= i && A[j] >= p) j--;
        if (i < j) swapElem(A + i, A + j);
    }
    *a = i;


    //b값
    j = r - 1;
    while (i <= j) {

        while (i <= j && A[i] == p) i += 1;
        while (j >= i && A[j] > p) j -= 1;
        if (i < j) swapElem(A + i, A + j);
    }

    *b = i;
    swapElem(A + i, A + r);
} //분할

void swapElem(int* a, int* b) {
    int tmp;
    tmp = *b;
    *b = *a;
    *a = tmp;
}