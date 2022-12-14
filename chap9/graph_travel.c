#include <stdio.h>
#include <stdlib.h>
#include "LinkedQueue.h"

Graph *createGraph();
void destroyGraph(Graph *g);

Vertex *createVertex(ElementType data);
void destroyVertex(Vertex *v);

Edge *createEdge(Vertex *from, Vertex *target, int weight);
void destroyEdge(Edge *e);

void addVertex(Graph *g, Vertex *v);
void addEdge(Vertex *v, Edge *e);
void printGraph(Graph *g);

void depthFindGraph(Vertex *v);
void widthFindGraph(Vertex *v, LinkedQueue *queue);

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

Vertex *createVertex(ElementType data) {
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

void printGraph(Graph *g) {
    Vertex *v = g->vertices;
    Edge *e = NULL;

    if (v == NULL) {
        return;
    }

    while (v != NULL) {
        printf("%d : ", v->data);
        e = v->adjacencyList;
        if (e == NULL) {
            v = v->next;
            printf("\n");
            continue;
        }

        while (e != NULL) {
            printf("%d[%d] ", e->target->data, e->weight);
            e = e->next;
        }

        printf("\n");
        v = v->next;
    }
    printf("\n");
}

void depthFindGraph(Vertex *v) {
    Edge *e = NULL;

    printf("%d ", v->data);
    v->visited = visited;

    e = v->adjacencyList;

    while (e != NULL) {
        if ((e->target != NULL) && (e->target->visited == notVisited)) {
            depthFindGraph(e->target);
        }
        e = e->next;
    }
}
void widthFindGraph(Vertex *v, LinkedQueue *queue) {
    Edge *e = NULL;

    printf("%d ", v->data);
    v->visited = visited;

    LQ_Enqueue(&queue, LQ_CreateNode(v));

    while (!LQ_IsEmpty(queue)) {
        Node *popped = LQ_Dequeue(&queue);
        v = popped->Data;
        e = v->adjacencyList;

        while (e != NULL) {
            v = e->target;

            if ((v != NULL) && (v->visited == notVisited)) {
                printf("%d ", v->data);
                v->visited = visited;
                LQ_Enqueue(&queue, LQ_CreateNode(v));
            }
            e = e->next;
        }
    }
}

int main() {
    Graph *g = createGraph();
    int mode = 0;

    // ?????? ??????
    Vertex *v1 = createVertex(1);
    Vertex *v2 = createVertex(2);
    Vertex *v3 = createVertex(3);
    Vertex *v4 = createVertex(4);
    Vertex *v5 = createVertex(5);

    addVertex(g, v1);
    addVertex(g, v2);
    addVertex(g, v3);
    addVertex(g, v4);
    addVertex(g, v5);

    // ????????? ????????? ???????????? ??????
    addEdge(v1, createEdge(v1, v2, 0));
    addEdge(v1, createEdge(v1, v3, 0));
    addEdge(v1, createEdge(v1, v4, 0));
    addEdge(v1, createEdge(v1, v5, 0));

    addEdge(v2, createEdge(v2, v1, 0));
    addEdge(v2, createEdge(v2, v3, 0));
    addEdge(v2, createEdge(v2, v5, 0));

    addEdge(v3, createEdge(v3, v1, 0));
    addEdge(v3, createEdge(v3, v2, 0));

    addEdge(v4, createEdge(v4, v1, 0));
    addEdge(v4, createEdge(v4, v5, 0));

    addEdge(v5, createEdge(v5, v1, 0));
    addEdge(v5, createEdge(v5, v2, 0));
    addEdge(v5, createEdge(v5, v4, 0));

    printf("Enter Travel Mode : ");
    scanf("%d", &mode);

    if (mode == 0) {
        depthFindGraph(g->vertices);
    } else {
        LinkedQueue *queue = LQ_CreateQueue();
        widthFindGraph(v1, queue);
        LQ_DestroyQueue(queue);
    }

    destroyGraph(g);

    return 0;
}