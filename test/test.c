#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Node
{
    int key;
    int c;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
} Node;

void swap(int* a, int* b)
{
    int tmp;
    tmp = *b;
    *b = *a;
    *a = tmp;
}

Node* getnode() {
    Node* n = (Node*)malloc(sizeof(Node));
    n->left = NULL;
    n->right = NULL;
    return n;
}

void upHeap(Node* v)
{
    if (v->parent == NULL) // 해당 노드가 루트일 경우 반환
        return;
    if (v->key >= (v->parent)->key) // 해당 노드의 키가 부모 노드의 키보다 크거나 같을 경우 반환
        return;
    swap(&(v->key), &(v->parent)->key); // 1, 2에 해당하지 않으면 힙 순서 속성에 어긋나므로 스왑
    upHeap(v->parent); // 부모노드를 인자로 재귀
}

void expandExternal(Node* z)
{
    Node* l = getnode();
    Node* r = getnode();

    l->parent = z;
    l->c = 1;

    r->parent = z;
    r->c = 2;

    z->left = l;
    z->right = r;

    return;
}

Node* advanceLast(Node* last)
{
    Node* v = last;

    while (v->c == 2) // 현재 노드가 오른쪽 자식인 동안
        v = v->parent; // 부모 노드로 이동

    while (v->c == 1) // 현재 노드가 왼쪽 자식인 동안
        v = (v->parent)->right; // 형제 노드로 이동

    while (v->left != NULL && v->right != NULL) // 현재 노드가 내부 노드인 동안 
        v = v->left; // 왼쪽 자식으로 이동

    return v;
}

Node* retreatLast(Node* v)
{
    while (v->c == 1) // 현재 노드가 왼쪽 자식인 동안
        v = v->parent; // 부모 노드로 이동

    while (v->c == 2) // 현재 노드가 오른쪽 자식인 동안
        v = (v->parent)->left; // 형제 노드로 이동

    while (v->left != NULL && v->right != NULL) // 현재 노드가 내부 노드인 동안
        v = v->right; // 오른쪽 자식으로 이동
    
    return v;
}

Node* insertItem(int k, Node* last)
{
    Node* z, * L;

    L = advanceLast(last);
    z = L;
    z->key = k;
    expandExternal(z);
    upHeap(z);

    return L;
}

void print_Tree(Node* tree)
{
    if (tree->left != NULL && tree->right != NULL) {
        printf(" %d", tree->key);
        print_Tree(tree->left);
        print_Tree(tree->right);
    }
}

int main()
{
    int i, n, k;

    Node* tree = getnode();
    Node* last = tree;
    tree->parent = NULL;
    tree->c = 0;

    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        scanf("%d", &k);

        last = insertItem(k, last);
    }

    print_Tree(tree);

    return 0;
}