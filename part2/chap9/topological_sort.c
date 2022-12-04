#include <stdio.h>
#include <stdlib.h>
#include "topological_sort.h"

Graph *createGraph() {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->vertices = NULL;
    graph->vertexCount = 0;
    return graph;
}

void destroyGraph(Graph *g) {
    while (g->vertices != NULL) {
        Vertex *vertices = g->vertices->next;
        destroyVertex(g->vertices);
        g->vertices = vertices;
    }
    free(g);
    g = NULL;
}

Vertex *createVertex(TsElementType data) {
    Vertex *v = (Vertex *)malloc(sizeof(Vertex));
    v->data = data;
    v->next = NULL;
    v->adjacencyList = NULL;
    v->visited = notVisited;
    v->index -1;
    return v;
}

void destroyVertex(Vertex *v) {
    while (v->adjacencyList != NULL) {
        Edge *edge = v->adjacencyList->next;
        destroyEdge(v->adjacencyList);
        v->adjacencyList = edge;
    }
    free(v);
    v = NULL;
}

Edge *createEdge(Vertex *from, Vertex *target, int weight) {
    Edge *e = (Edge *)malloc(sizeof(Edge));
    e->from = from;
    e->target = target;
    e->next = NULL;
    e->weight = weight;
    return e;
}

void destroyEdge(Edge *e) {
    free(e);
    e = NULL;
}

void addVertex(Graph *g, Vertex *v) {
    Vertex *vertexList = g->vertices;

    if (vertexList == NULL) {
        g->vertices = v;
    } else {
        while (vertexList->next != NULL) {
            vertexList = vertexList->next;
        }
        vertexList->next = v;
    }
    v->index = g->vertexCount++;
}

void addEdge(Vertex *v, Edge *e) {
    if (v->adjacencyList == NULL) {
        v->adjacencyList = e;
    } else {
        Edge *adjacencyList = v->adjacencyList;
        while (adjacencyList->next != NULL) {
            adjacencyList = adjacencyList->next;
        }
        adjacencyList->next = e;
    }
}

void topologicalSort(Vertex *v, Node **list) {
    while ((v != NULL) && (v->visited == notVisited)) {
        tsDfs(v, list);
        v = v->next;
    }
}
void tsDfs(Vertex *v, Node **list) {
    Node *newHead = NULL;
    Edge *e = NULL;

    v->visited = visited;
    e = v->adjacencyList;

    while (e != NULL) {
        if ((e->target != NULL) && (e->target->visited == notVisited)) {
            tsDfs(e->target, list);
        }
        e = e->next;
    }

    printf("%c\n", v->data);

    newHead = SLL_CreateNode(v->data);
    SLL_InsertNewHead(list, newHead);
}

int main(void) {
    Node *sortedList = NULL;
    Node *currNode = NULL;

    Graph *graph = createGraph();

    Vertex *A = createVertex('A');
    Vertex *B = createVertex('B');
    Vertex *C = createVertex('C');
    Vertex *D = createVertex('D');
    Vertex *E = createVertex('E');
    Vertex *F = createVertex('F');
    Vertex *G = createVertex('G');
    Vertex *H = createVertex('H');

    addVertex(graph, A);
    addVertex(graph, B);
    addVertex(graph, C);
    addVertex(graph, D);
    addVertex(graph, E);
    addVertex(graph, F);
    addVertex(graph, G);
    addVertex(graph, H);

    addEdge(A, createEdge(A, C, 0));
    addEdge(A, createEdge(A, D, 0));

    addEdge(B, createEdge(B, C, 0));
    addEdge(B, createEdge(B, E, 0));

    addEdge(C, createEdge(C, F, 0));

    addEdge(D, createEdge(D, F, 0));
    addEdge(D, createEdge(D, G, 0));

    addEdge(E, createEdge(E, G, 0));

    addEdge(F, createEdge(F, H, 0));

    addEdge(G, createEdge(G, H, 0));

    topologicalSort(graph->vertices, &sortedList);

    printf("topologicalSort result: ");

    currNode = sortedList;

    while (currNode != NULL) {
        printf("%c ", currNode->Data);
        currNode = currNode->NextNode;
    }
    printf("\n");

    destroyGraph(graph);

    return 0;
}