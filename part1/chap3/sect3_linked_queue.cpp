#include <cstdio>
#include <cstdlib>
#include<stdio.h>
#include <cstring>

typedef struct myNode {
	char *data;
	struct myNode *nextNode;
} Node;

typedef struct linkedQueueSt {
	Node *front;
	Node *rear;
	int count;
} linkedQueue;

void createLinkedQueue(linkedQueue **queue);
void destroyLinkedQueue(linkedQueue *queue);
Node *createNode(char *newData);
void destroyNode(Node *node);
void enqueueLinkedQueue(linkedQueue *queue, Node *newNode);
Node *dequeueLinkedQueue(linkedQueue *queue);
int isEmptyLinkedQueue(linkedQueue *queue);

void createLinkedQueue(linkedQueue **queue) {
	(*queue) = (linkedQueue *)malloc(sizeof(linkedQueue));

	(*queue)->count = 0;
	(*queue)->front = NULL;
	(*queue)->rear = NULL;
}

void destroyLinkedQueue(linkedQueue *queue) {
	while (!isEmptyLinkedQueue(queue)) {
		Node *delNode = dequeueLinkedQueue(queue);
		destroyNode(delNode);
	}
	free(queue);
}

Node *createNode(char *newData) {
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->data = (char *)malloc(strlen(newData) + 1);

	strcpy(newNode->data, newData);

	newNode->nextNode = NULL;

	return newNode;
}

/* 노드 소멸 */
void destroyNode(Node *node) {
	if (node != NULL) {
		free(node->data);
		free(node);
	}
}


void enqueueLinkedQueue(linkedQueue *queue, Node *newNode) {
	if (queue->front == NULL) {
		queue->front = newNode;
		queue->rear = newNode;
	} else {
		queue->rear->nextNode = newNode;
		queue->rear = newNode;
	}
	queue->count++;
}

Node *dequeueLinkedQueue(linkedQueue *queue) {
	Node *front = queue->front;

	if (queue->front->nextNode == NULL) {
		queue->front = NULL;
		queue->rear = NULL;
	} else {
		queue->front = queue->front->nextNode;
	}
	queue->count--;

	return front;
}

int isEmptyLinkedQueue(linkedQueue *queue) {
	return (queue->front == NULL);
}

int main() {
	Node *pop = NULL;
	linkedQueue *queue = NULL;

	createLinkedQueue(&queue);

	enqueueLinkedQueue(queue, createNode((char *)"abc"));
	enqueueLinkedQueue(queue, createNode((char *)"def"));
	enqueueLinkedQueue(queue, createNode((char *)"efg"));
	enqueueLinkedQueue(queue, createNode((char *)"hij"));

	printf("size:%d\n", queue->count);

	while (!isEmptyLinkedQueue(queue)) {
		pop = dequeueLinkedQueue(queue);
		printf("%s\n", pop->data);
		destroyNode(pop);
	}
	dequeueLinkedQueue(queue);

	return 0;
}