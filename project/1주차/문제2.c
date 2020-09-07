#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node {
    int elem;
    struct node* left;
    struct node* right;
}node;

node* getNode(int elem) {
    node* n;
    
    n = (node*)malloc(sizeof(node));

    n->left = NULL;
    n->right = NULL;
    n->elem = elem;

    return n;
}

void setChild(node* root, int parent, int left, int right);
node* findParent(node* PARENT, int parent);
void printChild(node* PARENT, char str[]);

int main(void) {
    node* root = getNode(-1);

    int n;
    int parent,left, right;
    int i;
    char str[100];

    /*트리 초기화*/
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d %d %d", &parent, &left, &right);

        setChild(root, parent, left, right);
    }

    /*트리 탐색*/
    scanf("%d", &n);
    getchar();

    for (i = 0; i < n; i++) {
        gets(str);
        
        printChild(root, str);
    }

    return 0;
}

void setChild(node* root, int parent, int left, int right) {
    node* PARENT = NULL;
    node* LEFT = NULL;
    node* RIGHT = NULL;

    if (root->elem == -1) {
        root->elem = parent;
        PARENT = root;
    } else {
        PARENT = findParent(root, parent);
    }
    
    if (left != 0) {
        LEFT = getNode(left);
        PARENT->left = LEFT;
    }
    if (right != 0) {
        RIGHT = getNode(right);
        PARENT->right = RIGHT;
    }
}

node* findParent(node* PARENT, int parent) {
    node* left = NULL;
    node* right = NULL;

    if (PARENT == NULL) {
        return NULL;
    }

    if (PARENT->elem == parent) {
        return PARENT;
    }

    left = findParent(PARENT->left, parent);
    right = findParent(PARENT->right, parent);

    if (left == NULL) {
        return right;
    } else {
        return left;
    }
}

void printChild(node* PARENT, char str[]) {
    int i;

    printf(" %d", PARENT->elem);

    for (i = 0; i < strlen(str); i++) {
        if (str[i] == 'L') PARENT = PARENT->left;
        else PARENT = PARENT->right;

        printf(" %d", PARENT->elem);
    }

    printf("\n");
}