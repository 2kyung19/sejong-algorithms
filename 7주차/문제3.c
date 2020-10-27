#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    int key;
    int height;
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

NODE* root = NULL; //root

int isRoot(NODE* node);
int isExternal(NODE* node);
NODE* expandExternal(NODE* node);
void insertItem(int k);
NODE* treeSearch(NODE* node, int k);
int findElement(NODE* node, int k);
void searchAndFixAfterInsertion(NODE* node);
int isBalanced(NODE* node);
int abs(int n);
int findMax(int n, int m);
int updateHeight(NODE* node);
NODE* restructure(NODE* x, NODE* y, NODE* z);
int removeElement(NODE* node, int k);
NODE* sibling(NODE* node);
NODE* reduceExternal(NODE* z);
NODE* inOrderSucc(NODE* node);
void searchAndFixAfterRemoval(NODE* node);
void printTree(NODE* node);
void freeNode(NODE* node);

int main(void) {
    char order;
    int key;
    int loop = 1;
    int elem;

    root = getNode();

    while (loop) {
        scanf("%c", &order);
        getchar();

        switch (order) {
        case 'i':
            scanf("%d", &key);
            getchar();

            insertItem(key);
            break;

        case 'd':
        case 's':
            scanf("%d", &key);
            getchar();

            if (order == 'd') elem = removeElement(root, key);
            else elem = findElement(root, key);

            elem != -1 ? printf("%d\n", elem) : printf("X\n");
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

int isRoot(NODE* node) {
    if (node->parent == NULL) return 1;
    else return 0;
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
    node->height = 1;

    left->parent = node;
    right->parent = node;

    return node;
}

void insertItem(int k) {
    NODE* w;

    w = treeSearch(root, k);

    if (isExternal(w)) {
        w->key = k;
        w = expandExternal(w);
        searchAndFixAfterInsertion(w);
    }
}

NODE* treeSearch(NODE* n, int k) {
    NODE* node = n;

    if (isExternal(node)) return node;

    if (k == node->key) return node; // k == key(node)
    else if (k < node->key) return treeSearch(node->lChild, k); // k < key(node)
    else return treeSearch(node->rChild, k); // k > key(node)
}

int findElement(NODE* node, int k) {
    NODE* w;
    int e;
    w = treeSearch(node, k);

    if (isExternal(w)) return -1;
    else {
        e = w->key;
        return e;
    }
}

void searchAndFixAfterInsertion(NODE* node) {
    NODE* x, * y, * z;

    node->lChild->height = 0;
    node->rChild->height = 0;
    node->height = 1;

    if (isRoot(node)) return;
    z = node->parent;

    while (updateHeight(z) && isBalanced(z)) {
        if (isRoot(z)) return;
        z = z->parent;
    }

    if (isBalanced(z)) return;

    if (z->lChild->height > z->rChild->height) y = z->lChild;
    else y = z->rChild;

    if (y->lChild->height > y->rChild->height) x = y->lChild;
    else x = y->rChild;

    restructure(x, y, z);
}

int isBalanced(NODE* node) {
    NODE* left, * right;

    left = node->lChild;
    right = node->rChild;

    return abs(left->height - right->height) < 2;
}

int abs(int n) {
    if (n < 0) return -1 * n;
    return n;
}

int findMax(int n, int m) {
    if (n > m) return n;
    return m;
}

int updateHeight(NODE* node) {
    int h;
    NODE* left, * right;

    left = node->lChild;
    right = node->rChild;

    h = findMax(left->height, right->height) + 1;

    if (h != node->height) {
        node->height = h;
        return 1;
    }

    else return 0;
}

NODE* restructure(NODE* x, NODE* y, NODE* z) {
    NODE* a, * b, * c;
    NODE* T0, * T1, * T2, * T3;

    if (z->key < y->key && y->key < x->key) { //key(z) < key(y) < key(x)
        a = z; b = y; c = x;
        T0 = a->lChild; T1 = b->lChild; T2 = c->lChild; T3 = c->rChild;
    }
    else if (x->key < y->key && y->key < z->key) { //key(x) < key(y) < key(z)
        a = x; b = y; c = z;
        T0 = a->lChild; T1 = a->rChild; T2 = b->rChild; T3 = c->rChild;
    }
    else if (z->key < x->key && x->key < y->key) { //key(z) < key(x) < key(y)
        a = z; b = x; c = y;
        T0 = a->lChild; T1 = b->lChild; T2 = b->rChild; T3 = c->rChild;
    }
    else { //key(y) < key(x) < key(z)
        a = y; b = x; c = z;
        T0 = a->lChild; T1 = b->lChild; T2 = b->rChild; T3 = c->rChild;
    }

    if (isRoot(z)) {
        root = b;
        b->parent = NULL;
    }
    else if (z->parent->lChild == z) {
        z->parent->lChild = b;
        b->parent = z->parent;
    }
    else { //z.parent.right == z
        z->parent->rChild = b;
        b->parent = z->parent;
    }

    a->lChild = T0;
    T0->parent = a;
    a->rChild = T1;
    T1->parent = a;
    updateHeight(a);

    c->lChild = T2;
    T2->parent = c;
    c->rChild = T3;
    T3->parent = c;
    updateHeight(c);

    b->lChild = a;
    a->parent = b;
    b->rChild = c;
    c->parent = b;
    updateHeight(b);

    return b;
}

int removeElement(NODE* node, int k) {
    NODE* w, * y, * z, *zs;
    int e;

    w = treeSearch(node, k);

    if (isExternal(w)) return -1;

    e = w->key;
    z = w->lChild;

    if (!isExternal(z))z = w->rChild;

    if (isExternal(z)) zs = reduceExternal(z);

    else {
        y = inOrderSucc(w);
        z = y->lChild;
        w->key = y->key;
        zs = reduceExternal(z);
    }

    searchAndFixAfterRemoval(zs->parent);

    return e;
}

NODE* sibling(NODE* node) {
    if (isRoot(node)) return NULL;
    if (node->parent->lChild == node) return node->parent->rChild;
    else return node->parent->lChild;

}

NODE* reduceExternal(NODE* z) {
    NODE* w = z->parent;
    NODE* zs = sibling(z);
    NODE* g;

    if (isRoot(w)) {
        root = zs;
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

void searchAndFixAfterRemoval(NODE* node) {
    NODE* x, * y, * z;
    NODE* tree;

    z = node;

    while (updateHeight(z) && isBalanced(z)) {
        if (isRoot(z)) return;
        z = z->parent;
    }

    if (isBalanced(z)) return;

    if (z->lChild->height > z->rChild->height) y = z->lChild;
    else y = z->rChild;

    if (y->lChild->height > y->rChild->height) x = y->lChild;
    else if (y->lChild->height < y->rChild->height) x = y->rChild;
    else { 
        if (z->lChild == y) x = y->lChild;
        else x = y->rChild;
    }

    tree = restructure(x, y, z);
    if (isRoot(tree)) return;

    searchAndFixAfterRemoval(tree->parent);
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
