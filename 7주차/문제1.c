#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    int key;
    struct node* parent;
    struct node* lChild;
    struct node* rChild;
}NODE;

NODE* getNode() {
    NODE* node = (NODE*)malloc(sizeof(NODE));

    node->parent = NULL;
    node->lChild = NULL;
    node->rChild = NULL;

    return node;
}

int isExternal(NODE* node);
NODE* expandExternal(NODE* node);
void insertItem(NODE* node, int k);
int findElement(NODE* node, int k);
NODE* treeSearch(NODE* node, int k);
int removeElement(NODE** node, int k);
NODE* sibling(NODE* node);
NODE* reduceExternal(NODE** node, NODE* z);
NODE* inOrderSucc(NODE* node);
void printTree(NODE* node);
void freeNode(NODE* node);

int main(void) {
    NODE* root = getNode();

    char order;
    int key;
    int loop = 1;
    int elem;

    while (loop) {
        scanf("%c", &order);
        getchar();

        switch (order) {
            case 'i':
                scanf("%d", &key);
                getchar();

                insertItem(root, key);
                break;

            case 'd':
            case 's':
                scanf("%d", &key);
                getchar();

                if (order == 'd') elem = removeElement(&root, key);
                else elem = findElement(root, key);

                elem != -1 ?  printf("%d\n", elem) : printf("X\n");
                break;

            case 'p':
                printTree(root);
                printf("\n");
                break;
            
            case 'q':
                freeNode(root);
                loop = 0;
                break;
        }
    }
    return 0;
}

int isExternal(NODE* node) {
    if (node->lChild == NULL && node->rChild == NULL) return 1;
    else return 0;
}

NODE* expandExternal(NODE* node) {
    NODE* left, * right;

    left = getNode();
    right = getNode();

    node->lChild = left;
    node->rChild = right;

    left->parent = node;
    right->parent = node;

    return node;
}

void insertItem(NODE* node, int k) {
    NODE* w;

    w = treeSearch(node, k);

    if (isExternal(w)) {
        w->key = k;
        w = expandExternal(w);
    }
}

NODE* treeSearch(NODE* node, int k) {
    if (isExternal(node)) return node;

    if (k == node->key) return node; // k == key(node)
    else if (k < node->key) return treeSearch(node->lChild, k); // k < key(node)
    else return treeSearch(node->rChild, k); // k > key(node)
}

int findElement(NODE* node, int k) {
    NODE* w;

    w = treeSearch(node, k);

    if (isExternal(w)) return -1;

    else {
        return w->key;
    }
}

int removeElement(NODE** node, int k) {
    NODE* w, * z, * y;
    int e;

    w = treeSearch(*node, k);

    if (isExternal(w)) return -1;

    e = w->key;
    z = w->lChild;
    
    if (!isExternal(z))z = w->rChild;

    if (isExternal(z)) reduceExternal(node, z);

    else {
        y = inOrderSucc(w);
        z = y->lChild;
        w->key = y->key;
        reduceExternal(node, z);
    }
    
    return e;
}

NODE* sibling(NODE* node) {

    if (node->parent->lChild == node) return node->parent->rChild;
    else return node->parent->lChild;

}

NODE* reduceExternal(NODE** node, NODE* z) {
    NODE* w = z->parent;
    NODE* zs = sibling(z);
    NODE* g;

    if (w == *node) {
        *node = zs;
        zs->parent = NULL;
    }

    else {
        g = w->parent;
        zs->parent = g;
        if (w == g->lChild) g->lChild = zs;
        else g->rChild = zs;
    }

    free(z);
    free(w);

    return zs;
}

NODE* inOrderSucc(NODE* node) {
    NODE* w = node->rChild;

    if (isExternal(w)) return NULL;
    while (!isExternal(w->lChild)) w = w->lChild;

    return w;
}

void printTree(NODE* node) {
    if (isExternal(node)) return;

    printf(" %d", node->key);

    printTree(node->lChild);
    printTree(node->rChild);
}

void freeNode(NODE* node) {
    if (isExternal(node)) return;

    freeNode(node->lChild);
    freeNode(node->rChild);

    free(node);
}
