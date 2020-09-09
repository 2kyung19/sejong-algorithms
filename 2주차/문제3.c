#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>

void selection(int* array, int n);
void insertion(int* array, int n);
void reverse(int* array, int n);

int main(void) {
    int *A , *B;
    int n, num;
    int i, j;

    LARGE_INTEGER ticksPerSec;
    LARGE_INTEGER start, end, diff;

    srand(time(NULL));
    QueryPerformanceFrequency(&ticksPerSec);

    scanf("%d", &n);

    A = (int*)malloc(sizeof(int) * n);
    B = (int*)malloc(sizeof(int) * n);
    
    /*난수 저장*/
    for (i = 0; i < n; i++) {
        num = rand();
        A[i] = num;
        B[i] = num;
    }

/* A : 난수 데이터 정렬 */
    printf("\n** A\n");
    QueryPerformanceCounter(&start);
    /*선택*/ selection(A, n);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    printf("%.5f ms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart)*1000);
    
    QueryPerformanceCounter(&start);
    /*삽입*/ insertion(B, n);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    printf("%.5f ms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart)*1000);
    
/* B : 이미 정렬된 데이터를 정렬*/
    printf("\n** B\n");
    QueryPerformanceCounter(&start);
    /*선택*/ selection(A, n);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    printf("%.5f ms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

    QueryPerformanceCounter(&start);
    /*삽입*/ insertion(B, n);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    printf("%.5f ms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);


/* C : 역순으로 정렬된 데이터를 정렬 */
    reverse(A, n);
    reverse(B, n);

    printf("\n** C\n");
    QueryPerformanceCounter(&start);
    /*선택*/ selection(A, n);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    printf("%.5f ms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

    QueryPerformanceCounter(&start);
    /*삽입*/ insertion(B, n);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    printf("%.5f ms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

    return 0;
}

void selection(int* array, int n) {
    int min,temp;
    int i,j;

    /*선택 정렬*/
    for (i = 0; i < n - 1; i++) {

        min = n - 1;
        for (j = n - 1; j >= i; j--) {
            if (array[min] > array[j]) {
                min = j;
            }
        }

        //교환
        temp = array[i];
        array[i] = array[min];
        array[min] = temp;
    }
}

void insertion(int* array, int n) {
    int exchange, temp;
    int i, j;

    /*삽입 정렬*/
    for (i = 1; i < n; i++) {

        exchange = i;
        for (j = i - 1; j >= 0; j--) {
            if (array[exchange] > array[j]) {
                break;
            }

            //교환
            temp = array[exchange];
            array[exchange] = array[j];
            array[j] = temp;

            exchange = j;
        }
    }
}

void reverse(int* array, int n) {
    int exchange, temp;
    int i, j;

    /*삽입 정렬*/
    for (i = 1; i < n; i++) {

        exchange = i;
        for (j = i - 1; j >= 0; j--) {
            if (array[exchange] < array[j]) {
                break;
            }

            //교환
            temp = array[exchange];
            array[exchange] = array[j];
            array[j] = temp;

            exchange = j;
        }
    }
}