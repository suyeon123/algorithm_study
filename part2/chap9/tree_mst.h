#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

enum visitMode {visited, notVisited};

typedef char TsElementType;

// 정점 구조체
typedef struct tagVertex {
    TsElementType data;
    int visited;
    int index;

    struct tagVertex *next;
    struct tagEdge *adjacencyList;
} Vertex;

// 간선 구조체
typedef struct tagEdge {
    int weight; // 가중치
    struct tagEdge *next;
    Vertex *from;
    Vertex *target;
} Edge;

// 그래프 구조체
typedef struct tagGraph {
    Vertex *vertices;
    int vertexCount;
} Graph;

Graph *createGraph();
void destroyGraph(Graph *g);

Vertex *createVertex(TsElementType data);
void destroyVertex(Vertex *v);

Edge *createEdge(Vertex *from, Vertex *target, int weight);
void destroyEdge(Edge *e);

void addVertex(Graph *g, Vertex *v);
void addEdge(Vertex *v, Edge *e);

void topologicalSort(Vertex *v, Node **list);
void tsDfs(Vertex *v, Node **list);