#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define INFINITE 99999;

typedef struct edge {
	int vertex1, vertex2;
	int weight;
}EDGE;

typedef struct incident {
	int edge;
	struct incident* next;
}INCIDENT;

typedef struct vertex {
	int name;
	int distance;
	INCIDENT* head;
}VERTEX;

typedef struct graph {
	VERTEX* vertex;
	EDGE* edge;
	int n, m;
}GRAPH;

typedef struct heap {
	int key;
	int distance;
}HEAP;

GRAPH graph;

void buildGraph();
void initGraph(int n, int m);
void insertVertex(int idx);
void insertIncidentEdge(int v1, int v2, int w, int idx);
void addFirst(INCIDENT* head, int idx);

void primJarnikMST();

HEAP* buildHeap();
void upHeap(HEAP* heap, int idx);
void downHeap(HEAP* heap, int idx, int size);
void swapElem(HEAP* x, HEAP* y);
int removeMin(HEAP* heap, int idx);
int opposite(int u, int e);
int isInclude(HEAP* heap, int idx, int z);
void replaceKey(HEAP* heap, int idx, int z, int w);

void freeGraph();

int main(void) {
	INCIDENT* head;

	buildGraph();

	primJarnikMST();
	freeGraph();

	return 0;
}

void buildGraph() {
	int n, m;
	int v1, v2, w;

	scanf("%d %d", &n, &m);

	initGraph(n, m);

	for (int i = 0; i < graph.m; i++) {
		scanf("%d %d %d", &v1, &v2, &w);
		insertIncidentEdge(v1, v2, w, i);
	}
}

void initGraph(int n, int m) {
	graph.n = n;
	graph.m = m;
	graph.vertex = (VERTEX*)malloc(sizeof(VERTEX) * (n + 1)); //1부터 시작
	graph.edge = (EDGE*)malloc(sizeof(EDGE) * m);

	for (int i = 1; i <= n; i++) {
		insertVertex(i);
	}
}

void insertVertex(int idx) {
	graph.vertex[idx].name = idx;

	graph.vertex[idx].head = (INCIDENT*)malloc(sizeof(INCIDENT));
	graph.vertex[idx].head->next = NULL;
}

void insertIncidentEdge(int v1, int v2, int w, int idx) {
	graph.edge[idx].vertex1 = v1;
	graph.edge[idx].vertex2 = v2;
	graph.edge[idx].weight = w;

	addFirst(graph.vertex[v1].head, idx);
	addFirst(graph.vertex[v2].head, idx);
}

void addFirst(INCIDENT* head, int idx) {
	INCIDENT* node = (INCIDENT*)malloc(sizeof(INCIDENT));
	node->edge = idx;
	node->next = head->next;
	head->next = node;
}

void primJarnikMST() {
	HEAP* heap;
	INCIDENT* p;
	int sum, u, z;
	int i;

	for (int i = 1; i <= graph.n; i++) { // 초기화
		graph.vertex[i].distance = INFINITE;
	}
	graph.vertex[1].distance = 0;

	heap = buildHeap();

	sum = 0;
	i = graph.n;
	while (i > 0) {
		u = removeMin(heap, i);
		printf(" %d", graph.vertex[u].name);

		sum += graph.vertex[u].distance;

		p = graph.vertex[u].head->next;
		while (p != NULL) {
			z = opposite(u, p->edge);
			if (isInclude(heap, i, z) && graph.edge[p->edge].weight < graph.vertex[z].distance) {
				graph.vertex[z].distance = graph.edge[p->edge].weight;
				replaceKey(heap, i, z, graph.vertex[z].distance);
			}
			p = p->next;
		}

		i--;
	}

	printf("\n%d", sum);
	free(heap);
}

HEAP* buildHeap() {
	HEAP* heap = (HEAP*)malloc(sizeof(HEAP) * (graph.n + 1));
	int i;
	for (i = 1; i <= graph.n; i++) { //초기화
		heap[i].distance = graph.vertex[i].distance;
		heap[i].key = graph.vertex[i].name;
	}

	for (i = graph.n / 2; i >= 1; i--) { //상향식 힙생성
		downHeap(heap, i, graph.n);
	}

	return heap;
}

void upHeap(HEAP* heap, int idx) {
	if (idx == 1)return;
	if (heap[idx].distance >= heap[idx / 2].distance) return;
	swapElem(heap + idx, heap + idx / 2);
	upHeap(heap, idx / 2);
}

void downHeap(HEAP* heap, int idx, int size) {
	int left = 2 * idx;
	int right = 2 * idx + 1;
	int smaller;

	if (left > size) return;

	smaller = left;
	if (right <= size) {
		if (heap[right].distance < heap[left].distance) {
			smaller = right;
		}
	}

	if (heap[idx].distance <= heap[smaller].distance) return;

	swapElem(heap + idx, heap + smaller);
	downHeap(heap, smaller, size);
}

void swapElem(HEAP* x, HEAP* y) {
	HEAP temp;

	temp = *x;
	*x = *y;
	*y = temp;
}

int removeMin(HEAP* heap, int idx) {
	HEAP res;

	if (idx == 0) return -1;

	res = heap[1];
	swapElem(heap + 1, heap + idx);
	downHeap(heap, 1, --idx);

	return res.key;
}

int opposite(int u, int e) {
	if (graph.edge[e].vertex1 == u) return graph.edge[e].vertex2;
	else return graph.edge[e].vertex1;
}

int isInclude(HEAP* heap, int idx, int z) {
	for (int i = 1; i < idx; i++) {
		if (heap[i].key == z) return 1;
	}

	return 0;
}

void replaceKey(HEAP* heap, int idx, int z, int w) {
	int i;

	for (i = 1; i < idx; i++) {
		if (heap[i].key == z) {
			heap[i].distance = w;
			break;
		}
	}
	upHeap(heap, i);
}

void freeGraph() {
	INCIDENT* node, * next;

	for (int i = 1; i <= graph.n; i++) {
		node = graph.vertex[i].head;
		while (node != NULL) {
			next = node->next;
			free(node);
			node = next;
		}
	}

	free(graph.vertex);
	free(graph.edge);
}