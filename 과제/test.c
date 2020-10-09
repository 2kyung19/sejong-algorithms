#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
int n = 100000;
int limits[4] = { 1, 100, 500, 1000 }; //부배열의 크기가 limits이하면 삽입정렬로 전환

typedef struct array {
    int* ar;
    int size;
}array;

array* createArray();
array* copyArray(array* ary);
void clearArray(array* ary);
void swapElem(int* x, int* y);
void inPlaceInsertSort(array* ary);
void inPlacePartition(int* ar, int l, int r, int k, int* a, int* b);
int findIndexofMedianOfThree(int a, int b, int c);
int findPivot(array* A, int l, int r, int mode);
void inPlaceQuickSort(array* ary, int l, int r, int limit, int mode);
void quickSort(array* ary, int limit, int mode);
void test(array* copy_A, int limit, int mode);
void printHeaders();

array* createArray() {
    srand(time(NULL));
    int e;
    array* ary = (array*)malloc(sizeof(array));
    ary->ar = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        e = rand() % 100000 + 1;
        (ary->ar)[i] = e;
    }
    ary->size = n;
    return ary;
}
array* copyArray(array* ary) {
    array* bry = (array*)malloc(sizeof(array));
    bry->size = ary->size;
    bry->ar = (int*)malloc(sizeof(int) * ary->size);
    for (int i = 0; i < ary->size; i++) {
        (bry->ar)[i] = (ary->ar)[i];
    }

    return bry;
}
void clearArray(array* ary) {
    free(ary->ar);
    free(ary);
}
void swapElem(int* x, int* y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}
void inPlaceInsertSort(array* ary) {
    int* arr = ary->ar;
    int i = 1, j, target;

    while (i < ary->size) {
        j = i - 1;
        target = arr[i];
        while (arr[j] > target&& j >= 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = target; //1 3 6 4 5
        i++;
    }
}
void inPlacePartition(int* ar, int l, int r, int k, int* a, int* b) {
    int pivot = ar[k];
    swapElem(ar + k, ar + r);

    //LT, ET+GT
    int i = l, j = r - 1;
    while (i <= j) {
        while (i <= j && ar[i] < pivot) {
            i++;
        }
        while (i <= j && ar[j] >= pivot) {
            j--;
        }
        if (i < j) {
            swapElem(ar + i, ar + j);
        }
    }
    *a = i;
    //ET, GT
    j = r - 1;
    while (i <= j) {
        while (i <= j && ar[i] == pivot) {
            i++;
        }
        while (i <= j && ar[j] > pivot) {
            j--;
        }
        if (i < j) {
            swapElem(ar + i, ar + j);
        }
    }
    *b = i;
    swapElem(ar + i, ar + r);

}
int findIndexofMedianOfThree(int a, int b, int c) {
    if (a < b) {
        if (a < c && b < c) return b; //a<b<c
        else if (a<c && b>c) return c; //a<c<b
        else if (a > c) return a; //c<a<b
    }
    else {
        if (b < c && a < c) return a; //b<a<c
        else if (b<c && a>c) return c; //b<c<a
        else if (b > c) return b; //c<b<a
    }
}
int findPivot(array* A, int l, int r, int mode) {
    if (mode == 0) //deterministic1
        return r;
    if (mode == 1) //deterministic3
    {
        if (r - l < 3) //결정적3에 앞서 배열 크기가 3미만이면 l반환(셋 중 하나 골라야하니까)
            return l;

        return findIndexofMedianOfThree(l, (l + r) / 2, r);
    }
    if (mode == 2) //randomized1
    {
        srand(time(NULL));
        return (rand() % (r - l + 1)) + l;
    }
    else if (mode == 3) //randomized3
    {
        if (r - l < 3) //무작위3에 앞서 배열 크기가 3미만이면 l반환
            return l;

        srand(time(NULL));
        int a = (rand() % (r - l + 1)) + l; //l~r
        int b = (rand() % (r - l + 1)) + l;
        int c = (rand() % (r - l + 1)) + l;
        return findIndexofMedianOfThree(a, b, c);
    }
}
void inPlaceQuickSort(array* ary, int l, int r, int limit, int mode) {
    if (r - l > limit) {
        //분할
        int a, b;
        int k = findPivot(ary, l, r, mode);
        inPlacePartition(ary->ar, l, r, k, &a, &b);

        ////재귀, 통치
        inPlaceQuickSort(ary, l, a - 1, limit, mode);
        inPlaceQuickSort(ary, b + 1, r, limit, mode);
    }

}
void quickSort(array* ary, int limit, int mode) {
    inPlaceQuickSort(ary, 0, ary->size - 1, limit, mode);
    if (limit > 1) //limit=2도아니고 1은 이미 다 정렬된 상태이므로 의미없음
        inPlaceInsertSort(ary);
    return;
}
void test(array* copy_A, int limit, int mode) {
    LARGE_INTEGER ticksPerSec;
    LARGE_INTEGER start, end, diff;
    //시간 측정
    QueryPerformanceFrequency(&ticksPerSec);
    QueryPerformanceCounter(&start);

    //테스트
    quickSort(copy_A, limit, mode);

    //측정 종료
    QueryPerformanceCounter(&end);

    //실행시간 계산
    diff.QuadPart = end.QuadPart - start.QuadPart;
    printf("%10.8f    ", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);
}
void printHeaders() {
    char* header[5] = { "Limit    ", "결정적1        ", "결정적3        ", "무작위1        ", "무작위3        " };
    for (int i = 0; i < 5; i++) {
        printf("%s", header[i]);
    }printf("\n");
}
void miniTest() {
    // 1.난수 생성하는지(20개)
    srand(time(NULL));
    int e;
    array* ary = (array*)malloc(sizeof(array));
    ary->ar = (int*)malloc(sizeof(int) * 20);
    ary->size = 20;
    for (int i = 0; i < 20; i++) {
        e = rand() % 12 + 1;
        (ary->ar)[i] = e;
    }

    // 퀵정렬(삽입포함) 같은 모드0에서 limit변화
    for (int i = 0; i < 4; i++) {
        array* copy = copyArray(ary);

        printf("퀵정렬 limit %d: \n", 2 * (i + 1));

        inPlaceQuickSort(copy, 0, copy->size - 1, 2 * (i + 1), 0);
        for (int j = 0; j < 20; j++) {
            printf(" %d", copy->ar[j]);
        }printf("\n");

        inPlaceInsertSort(copy);
        for (int j = 0; j < 20; j++) {
            printf(" %d", copy->ar[j]);
        }printf("\n");

        clearArray(copy);
    }
}
void main() {
    char* ch_limits[4] = { "1        ", "100      ", "500      ", "1000     " };
    array* A = createArray();

    printHeaders();
    for (int i = 0; i < 4; i++) {
        printf("%s", ch_limits[i]);
        for (int mode = 0; mode < 4; mode++) {
            array* copy_A = copyArray(A);
            test(copy_A, limits[i], mode);
            clearArray(copy_A);
        }printf("\n");
    }
    clearArray(A);
}