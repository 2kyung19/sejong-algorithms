#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//인접행렬 - 배열
typedef struct edge { //간선
	int vertex1;
	int vertex2;
	int check;
}EDGE;

typedef struct vertices {
	int elem;
	int check;
}VERTICES;

typedef struct graph { //그래프
	VERTICES* vertices;
	int** adjacency;
	EDGE* edges;
	int edgeSize;
	int size;
}GRAPH;

void initGraph(GRAPH* graph, int n, int m);
void insertEdge(int v1, int v2, GRAPH* graph);
void BFS(GRAPH* graph, int n, int m, int s);

int main() {
	GRAPH graph;
	int n, m, s;
	int u, v;

	scanf("%d %d %d", &n, &m, &s);

	initGraph(&graph, n, m);

	for (int i = 0; i < m; i++) {
		scanf("%d %d", &u, &v);

		insertEdge(u, v, &graph);
	}

	BFS(&graph, n, m, s);
	

	return 0;
}

void initGraph(GRAPH* graph, int n, int m) {
	graph->size = n;
	graph->edgeSize = 0;

	graph->vertices = (VERTICES*)malloc(sizeof(VERTICES) * n);
	graph->adjacency = (int**)malloc(sizeof(int*) * n);
	graph->edges = (EDGE*)malloc(sizeof(EDGE) * m);

	for (int i = 0; i < n; i++) {
		graph->vertices[i].elem = i + 1;
		graph->vertices[i].check = -1;

		graph->adjacency[i] = (int*)malloc(sizeof(int) * n);
		for (int j = 0; j < n; j++) {
			graph->adjacency[i][j] = -1;
		}
	}

	for (int i = 0; i < m; i++) {
		graph->edges[i].check = -1;
	}
}

void insertEdge(int v1, int v2, GRAPH* graph) {
	EDGE* edge = graph->edges;
	int index = -1;

	//edges list에 중복 검사 및 추가
	for (int i = 0; i < graph->edgeSize; i++) {
		if (edge[i].vertex1 == v1 && edge[i].vertex2 == v2) {
			index = i;
			break;
		}
		if (edge[i].vertex1 == v2 && edge[i].vertex2 == v1) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		index = graph->edgeSize;
	}

	edge[index].vertex1 = v1;
	edge[index].vertex2 = v2;
	edge[index].check = 1;

	//adjacency
	graph->adjacency[v1 - 1][v2 - 1] = index;
	graph->adjacency[v2 - 1][v1 - 1] = index;

	graph->edgeSize += 1;
}

void BFS(GRAPH* graph, int n, int m, int s) {
	int* temp = (int*)malloc(sizeof(int) * n);
	int num = 1, cnt = 0;
	
	printf("%d\n", s);

	for (int i = 0; i < n; i++) {
		temp[i] = 0;
	}
	temp[0] = s;
	graph->vertices[s - 1].check = 1;

	while (cnt < n) {
		for (int i = 0; i < n; i++) {
			if (temp[cnt] != 0 ) {
				if (graph->adjacency[temp[cnt] - 1][i] != -1 && graph->vertices[i].check == -1) {
					printf("%d\n", graph->vertices[i].elem);

					graph->vertices[i].check = 1;
					temp[num] = i + 1;
					num++;
				}
			}
		}
		cnt++;
	}
}