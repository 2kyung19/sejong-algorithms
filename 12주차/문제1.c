#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct incident {
	int element;
	struct incident* next;
}INCIDENT;

typedef struct edge {
	int origin;
	int destination;
}EDGE;

typedef struct vertex {
	char name;
	INCIDENT* inEdges;
	INCIDENT* outEdges;
	int inDegree;
}VERTEX;

typedef struct graph {
	VERTEX* vertices;
	EDGE* edges;
}GRAPH;

GRAPH graph;
int n, m;
int topOrder[100];
int queue[100];
int start, end;

void initializeGraph();
void buildGraph();
void insertVertex(char vName, int i);
void insertDirectedEdge(char uName, char wName, int i);
int index(char vName);
void addFirst(INCIDENT* H, int i);
void topologicalSort();
void initQueue();
int isEmpty();
void enqueue(int v);
int dequeue();

int main() {

	buildGraph();
	topologicalSort();

	if (topOrder[0] == 0) printf("0\n");
	else {
		for (int i = 1; i <= n; i++) {
			printf("%c ", graph.vertices[topOrder[i]].name);
		}
	}
	return 0;
}

void initializeGraph() {
	graph.vertices = (VERTEX*)malloc(sizeof(VERTEX) * 100);
	graph.edges = (EDGE*)malloc(sizeof(EDGE) * 1000);
}

void buildGraph() {
	int i;
	char vName, uName, wName;

	initializeGraph();

	scanf("%d", &n);
	getchar();

	for (i = 0; i < n; i++) {
		scanf("%c", &vName);
		getchar();
		insertVertex(vName, i);
	}

	scanf("%d", &m);
	getchar();

	for (i = 0; i < m; i++) {
		scanf("%c %c", &uName, &wName);
		getchar();
		insertDirectedEdge(uName, wName, i);
	}
}

void insertVertex(char vName, int i) {
	graph.vertices[i].name = vName;

	graph.vertices[i].outEdges = (INCIDENT*)malloc(sizeof(INCIDENT));
	graph.vertices[i].inEdges = (INCIDENT*)malloc(sizeof(INCIDENT));
	graph.vertices[i].outEdges->next = NULL;
	graph.vertices[i].inEdges->next = NULL;

	graph.vertices[i].inDegree = 0;
}

void insertDirectedEdge(char uName, char wName, int i) {
	int u, w;

	u = index(uName);
	w = index(wName);

	graph.edges[i].origin = u;
	graph.edges[i].destination = w;

	addFirst(graph.vertices[u].outEdges, i);
	addFirst(graph.vertices[w].inEdges, i);

	graph.vertices[w].inDegree++;
}

int index(char vName) {
	for (int i = 0; i < n; i++) {
		if (graph.vertices[i].name == vName) return i;
	}
}

void addFirst(INCIDENT* H, int i) {
	INCIDENT* node = (INCIDENT*)malloc(sizeof(INCIDENT));

	node->element = i;
	node->next = H->next;
	H->next = node;
}

void topologicalSort() {
	int in[100];
	int t, u, w;
	INCIDENT* e;

	initQueue();

	for (int i = 0; i < n; i++) {
		in[i] = graph.vertices[i].inDegree;
		if (in[i] == 0) enqueue(i);
	}

	t = 1;

	while (!isEmpty()) {
		u = dequeue();
		topOrder[t] = u;
		t += 1;

		e = graph.vertices[u].outEdges;
		e = e->next;
		while (e != NULL) {
			w = graph.edges[e->element].destination;
			in[w] -= 1;
			if (in[w] == 0) enqueue(w);

			e = e->next;
		}
	}

	if (t <= n) topOrder[0] = 0;
	else topOrder[0] = 1;
}

void initQueue() {
	start = end = 0;

	for (int i = 0; i < 100; i++) {
		queue[i] = 0;
	}
}

int isEmpty() {
	if (start == end) return 1;
	else return 0;
}

void enqueue(int v) {
	queue[end] = v;
	end = (end + 1) % 100;
}

int dequeue() {
	int v;

	v = queue[start];

	start = (start + 1) % 100;

	return v;
}