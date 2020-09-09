#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void) {
    int* array;
    int n, temp;
    int exchange;
    int i, j;

    scanf("%d", &n);

    array = (int*)malloc(sizeof(int) * n);

    /*배열 값 저장*/
    for (i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }

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

    for (i = 0; i < n; i++) {
        printf(" %d", array[i]);
    }

    return 0;
}
