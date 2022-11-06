#include <cstdio>
#include <cstdlib>
#include<stdio.h>

typedef struct myNode {
	int data;
} Node;

typedef struct circularQueueSt {
	int capacity;
	int front;
	int rear;
	Node *nodes;
} circularQueue;

void createCcQueue(circularQueue **queue, int capacity);
void destroyCcQueue(circularQueue *queue);
void enqueueCcQueue(circularQueue *queue, int data);
int dequeueCcQueue(circularQueue *queue);
int getSizeCcQueue(circularQueue *queue);
int isEmptyCcQueue(circularQueue *queue);
int isFullCcQueue(circularQueue *queue);

void createCcQueue(circularQueue **queue, int capacity) {
	(*queue) = (circularQueue *)malloc(sizeof(circularQueue));

	(*queue)->nodes = (Node *)malloc(sizeof(Node));
	(*queue)->capacity = capacity;
	(*queue)->front = 0;
	(*queue)->rear = 0;
}

void destroyCcQueue(circularQueue *queue) {
	if (queue->nodes) {
		free(queue->nodes);
	}
	if (queue) {
		free(queue);
	}
}

void enqueueCcQueue(circularQueue *queue, int data) {
	int position = 0;

	if (queue->rear == queue->capacity + 1) {
		queue->rear = 0;
	} else {
		position = queue->rear++;
	}
	queue->nodes[position].data= data;
}

int dequeueCcQueue(circularQueue *queue) {
	int position = queue->front;

	if (queue->front == queue->capacity) {
		queue->front = 0;
	} else {
		queue->front++;
	}
	return queue->nodes[position].data;
}

int getSizeCcQueue(circularQueue *queue) {
	if (queue->front <= queue->rear) {
		return queue->rear - queue->front;
	} else {
		return queue->rear + (queue->capacity - queue->front) + 1;
	}
}

int isEmptyCcQueue(circularQueue *queue) {
	return (queue->front == queue->rear);
}

int isFullCcQueue(circularQueue *queue) {
	if (queue->front < queue->rear) {
		return (queue->rear - queue->front) == queue->capacity;
	} else {
		return (queue->rear + 1) == queue->front;
	}
}

int main() {
	circularQueue *queue = NULL;
	int i = 100;

	createCcQueue(&queue, 10);

	enqueueCcQueue(queue, 1);
	enqueueCcQueue(queue, 2);
	enqueueCcQueue(queue, 3);
	enqueueCcQueue(queue, 4);

	printf("dequeue:%d, front:%d, rear:%d\n", dequeueCcQueue(queue), queue->front, queue->rear);
	printf("dequeue:%d, front:%d, rear:%d\n", dequeueCcQueue(queue), queue->front, queue->rear);
	printf("dequeue:%d, front:%d, rear:%d\n", dequeueCcQueue(queue), queue->front, queue->rear);

	return 0;
}