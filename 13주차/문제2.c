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
}VERTEX;

typedef struct seperate {
	int size;
	INCIDENT* head;
}SEPERATE;

typedef struct graph {
	VERTEX* vertex;
	EDGE* edge;
	int n, m;
}GRAPH;

typedef struct heap {
	int key;
	int weight;
}HEAP;

GRAPH graph;

void buildGraph();
void initGraph(int n, int m);
void insertIncidentEdge(int v1, int v2, int w, int idx);

void kruskalMST();

SEPERATE* buildSet();
HEAP* buildHeap();
int findSet(SEPERATE* set, int v);
void unionSet(SEPERATE* set, int v1, int v2);
void downHeap(HEAP* heap, int idx, int size);
int removeMin(HEAP* heap, int idx);
void swapElem(HEAP* x, HEAP* y);
void addFirst(INCIDENT** head, int idx);
int deleteFirst(INCIDENT** head);

void freeSet(SEPERATE* set);
void freeGraph();

int main(void) {
	INCIDENT* head;

	buildGraph();

	kruskalMST();
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
		graph.vertex[i].name = i;
	}
}

void insertIncidentEdge(int v1, int v2, int w, int idx) {
	graph.edge[idx].vertex1 = v1;
	graph.edge[idx].vertex2 = v2;
	graph.edge[idx].weight = w;
}

void kruskalMST() {
	SEPERATE* set = buildSet();
	HEAP* heap = buildHeap();
	int size = graph.m;
	int sum = 0;
	int u, v1, v2;

	while (size > 0) {
		u = removeMin(heap, size);

		v1 = findSet(set, graph.edge[u - 1].vertex1);
		v2 = findSet(set, graph.edge[u - 1].vertex2);

		if (v1 != v2) {
			printf(" %d", graph.edge[u - 1].weight);
			sum += graph.edge[u - 1].weight;
			unionSet(set, v1, v2);
		}
		size--;
	}

	printf("\n%d", sum);
	freeSet(set);
	free(heap);
}

SEPERATE* buildSet() {
	SEPERATE* set = (SEPERATE*)malloc(sizeof(SEPERATE) * graph.n);

	for (int i = 0; i < graph.n; i++) {
		set[i].size = 0;
		set[i].head = (INCIDENT*)malloc(sizeof(INCIDENT));
		set[i].head->edge = graph.vertex[i + 1].name;
		set[i].head->next = NULL;
	}

	return set;
}

HEAP* buildHeap() {
	HEAP* heap = (HEAP*)malloc(sizeof(HEAP) * (graph.m + 1));
	int i;

	for (i = 1; i <= graph.m; i++) { //초기화
		heap[i].weight = graph.edge[i - 1].weight;
		heap[i].key = i;
	}

	for (i = graph.m / 2; i >= 1; i--) { //상향식 힙생성
		downHeap(heap, i, graph.m);
	}

	return heap;
}

int findSet(SEPERATE* set, int v) {
	INCIDENT* p;

	for (int i = 0; i < graph.n; i++) {
		p = set[i].head;
		while (p != NULL) {
			if (graph.vertex[p->edge].name == v) return i;
			p = p->next;
		}
	}
	return -1;
}

void unionSet(SEPERATE* set, int v1, int v2) {
	int temp, i;

	if (set[v1].size < set[v2].size) {
		temp = v1;
		v1 = v2;
		v2 = temp;
	}

	while (1) {
		i = deleteFirst(&(set[v2].head));

		if (i == -1) break;

		addFirst(&(set[v1].head), i);
	}

	set[v2].head = NULL;
	set[v2].size = 0;
}

void downHeap(HEAP* heap, int idx, int size) {
	int left = 2 * idx;
	int right = 2 * idx + 1;
	int smaller;

	if (left > size) return;

	smaller = left;
	if (right <= size) {
		if (heap[right].weight < heap[left].weight) {
			smaller = right;
		}
	}

	if (heap[idx].weight <= heap[smaller].weight) return;

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
	HEAP remove;

	if (idx == 0) return -1;

	remove = heap[1];
	swapElem(heap + 1, heap + idx);
	downHeap(heap, 1, --idx);

	return remove.key;
}

void addFirst(INCIDENT** head, int idx) {
	INCIDENT* node = (INCIDENT*)malloc(sizeof(INCIDENT));
	node->edge = idx;
	node->next = *head;
	*head = node;
}

int deleteFirst(INCIDENT** head) {
	int remove;

	if (*head == NULL) return -1;

	remove = (*head)->edge;
	*head = (*head)->next;

	return remove;
}

void freeSet(SEPERATE* set) {
	INCIDENT* p, * next;

	for (int i = 0; i < graph.n; i++) {
		p = set[i].head;

		while (p != NULL) {
			next = p->next;
			free(p);
			p = next;
		}
	}
	free(set);
}

void freeGraph() {
	free(graph.vertex);
	free(graph.edge);
}