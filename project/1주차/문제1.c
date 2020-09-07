#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node {
    int elem;
    struct node* prev;
    struct node* next;
}node;

node* getNode() {
    node* n;

    n = (node*)malloc(sizeof(node));
    n->prev = NULL;
    n->next = NULL;

    return n;
}

void add(node* header, int r, char e);
void delete(node* header, int r);
char get(node* header, int r);
void print(node* header);

void freeNode(node* n);
int invalidRankExceiption(int r, int size);

int main(void) {
    node* header = getNode();
    node* trailer = getNode();

    int n, size = 0;
    int rank;
    char order, elem;
    int i;

    header->next = trailer;
    trailer->prev = header;

    scanf("%d", &n);
    getchar();

    for (i = 0; i < n; i++) {
        scanf("%c", &order);
        getchar();

        switch (order) {
        case 'A': //add
            scanf("%d %c", &rank, &elem);
            getchar();

            if (invalidRankExceiption(rank, size + 1)) {
                printf("invalid position\n");
            }
            else {
                add(header, rank, elem);
                size++;
            }
            break;

        case 'D': //delete
            scanf("%d", &rank);
            getchar();

            if (invalidRankExceiption(rank, size)) {
                printf("invalid position\n");
            }
            else {
                delete(header, rank);
                size--;
            }
            break;

        case 'G': //get
            scanf("%d", &rank);
            getchar();

            if (invalidRankExceiption(rank, size)) {
                printf("invalid position\n");
            }
            else {
                printf("%c\n", get(header, rank));
            }
            break;

        case 'P': //print
            print(header);
            break;

        default:
            break;
        }

    }

    freeNode(header);

    return 0;
}

void add(node* header, int r, char e) {
    node* h = header;
    node* node = getNode();

    int i;

    for (i = 1; i < r; i++) { //h를 rank - 1 까지
        h = h->next;
    }

    node->next = h->next;
    node->prev = h;

    h->next->prev = node;
    h->next = node;

    node->elem = e;
}

void delete(node* header, int r) {
    node* h = header;

    int i;

    for (i = 0; i < r; i++) { //h를 rank 까지
        h = h->next;
    }

    h->prev->next = h->next;
    h->next->prev = h->prev;

    free(h);
}

char get(node* header, int r) {
    node* h = header;

    int i;

    for (i = 0; i < r; i++) { //h를 rank 까지
        h = h->next;
    }

    return h->elem;
}

void print(node* header) {
    node* h = header->next;

    while (1) {
        if (h->next == NULL) break;

        printf("%c", h->elem);
        h = h->next;
    }

    printf("\n");
}

void freeNode(node* n) {
    node* h = n->next;

    free(n);

    if (h == NULL) {
        return;
    }

    return freeNode(h);
}

int invalidRankExceiption(int r, int size) {
    if (size == 0 || size < r) {
        return 1;
    }

    return 0;
}