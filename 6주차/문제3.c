#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int main(void) {
    int a, b, mid;
    int n, i;
    char YorN;

    scanf("%d %d %d", &a, &b, &n);
    getchar();

    int l = a; int r = b;

    for (i = 0; i < n; i++) {
        scanf("%c", &YorN);

        mid = (a + b) / 2;

        if (YorN == 'Y') a = mid + 1;
        else b = mid;
    }

    printf("%d", a);

    return 0;
}