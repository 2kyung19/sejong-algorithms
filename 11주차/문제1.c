#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct incidence {
    int edge;
    struct incidence* next;
}INCIDENCE;

typedef struct vertices {
    INCIDENCE* incidence;
    int elem;
    int label;
}VERTICES;

typedef struct edge {
    int vertex1;
    int vertex2;
    int label;
}EDGE;

typedef struct graph {
    VERTICES* vertices; //편의를 위해 index를 1부터 시작
    EDGE* edges;
    int edgeSize;
    int size;
}GRAPH;

INCIDENCE* getIncidence(int edge) {
    INCIDENCE* node = (INCIDENCE*)malloc(sizeof(INCIDENCE));

    node->next = NULL;
    node->edge = edge;

    return node;
}

void initGraph(GRAPH* graph, int n, int m);
void insertIncidence(int v1, int v2, INCIDENCE* incidence, GRAPH* graph);
void insertEdge(int v1, int v2, GRAPH* graph);
void DFS(GRAPH* graph, int s);
void rDFS(GRAPH* graph, int s);

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

    DFS(&graph, s);

    return 0;
}

void initGraph(GRAPH* graph, int n, int m) {
    graph->size = n;
    graph->edgeSize = 0;

    //vertices -> 편의상 1부터 시작
    graph->vertices = (VERTICES*)malloc(sizeof(VERTICES) * (n + 1));
    graph->edges = (EDGE*)malloc(sizeof(EDGE) * m);
    for (int i = 1; i <= graph->size; i++) {
        graph->vertices[i].incidence = NULL;
        graph->vertices[i].elem = i;
    }
}

void insertIncidence(int v1, int v2, INCIDENCE* incidence, GRAPH* graph) {
    EDGE* edge = graph->edges;
    VERTICES* vertices = graph->vertices;
    INCIDENCE* p;
    int other;

    p = vertices[v1].incidence;
    if (p == NULL) vertices[v1].incidence = incidence; //첫 노드

    else { //오름차순 삽입
          //head와 비교
        if (edge[p->edge].vertex1 == v1) other = edge[p->edge].vertex2;
        else other = edge[p->edge].vertex1;

        if (other > v2) { //head에서 교환
            incidence->next = p;
            vertices[v1].incidence = incidence;
        }

        else {
            while (p->next != NULL) {
                if (edge[p->next->edge].vertex1 == v1) other = edge[p->next->edge].vertex2;
                else other = edge[p->next->edge].vertex1;

                if (other > v2) break;
                p = p->next;
            }

            if (p->next == NULL) p->next = incidence;
            else {
                incidence->next = p->next;
                p->next = incidence;
            }
        }
    }
}

void insertEdge(int v1, int v2, GRAPH* graph) {
    EDGE* edge = graph->edges;
    INCIDENCE* incidence1, * incidence2;
    int other, index = -1;

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

    //incidence node 생성 및 추가
    incidence1 = getIncidence(index);
    incidence2 = getIncidence(index);

    insertIncidence(v1, v2, incidence1, graph);

    if (v1 != v2) {
        insertIncidence(v2, v1, incidence2, graph);
    }

    graph->edgeSize += 1;
}

void DFS(GRAPH* graph, int s) {
    for (int i = 1; i <= graph->size; i++) {
        graph->vertices[i].label = 0;
    }
    for (int i = 0; i < graph->edgeSize; i++) {
        graph->edges[i].label = 0;
    }

    rDFS(graph, s);
}

void rDFS(GRAPH* graph, int s) {
    EDGE* edge = graph->edges;
    INCIDENCE* temp = NULL;
    int index = s, other;

    printf("%d\n", index);
    
    graph->vertices[index].label = -1; //방문
    temp = graph->vertices[index].incidence;

    while (temp != NULL) {
        if (graph->edges[temp->edge].label == 0) { //방문하지 않았다면
            if (edge[temp->edge].vertex1 == graph->vertices[index].elem) other = edge[temp->edge].vertex2;
            else other = edge[temp->edge].vertex1;
            
            if (graph->vertices[other].label == 0) {
                graph->edges[temp->edge].label = -1;
                rDFS(graph, other);
            }
        }
        temp = temp->next;
    }
}