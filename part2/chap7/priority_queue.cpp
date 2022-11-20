#include <stdlib.h>
#include <memory.h>
#include<stdio.h>

typedef struct myNode {
	int priority;
	void *data;
} queueNode;

typedef struct queue {
	queueNode *nodes;
	int capacity;
	int usedSize;
} priorityQueue;

priorityQueue *createPQ(int init);
void destroyPQ(priorityQueue *pq);
void enqueuePQ(priorityQueue *pq, queueNode newNode);
void dequeuePQ(priorityQueue *pq, queueNode *root);
int getParentPQ(int index);
int getLeftChildPQ(int index);
void swapPQNodes(priorityQueue *pq, int index1, int index2);
int isEmptyPQ(priorityQueue *pq);

priorityQueue *createPQ(int init) {
	priorityQueue *newPQ = (priorityQueue *)malloc(sizeof(priorityQueue));
	newPQ->capacity = init;
	newPQ->usedSize = 0;
	newPQ->nodes = (queueNode *)malloc(sizeof(queueNode) * newPQ->capacity);
	return newPQ;
}

void destroyPQ(priorityQueue *pq) {
	if (pq->nodes) {
		free(pq->nodes);
	}
	if (pq) {
		free(pq);
	}
}

void enqueuePQ(priorityQueue *pq, queueNode newNode) {
	int currPosition = pq->usedSize;
	int parentPosition = getParentPQ(currPosition);

	if (pq->usedSize == pq->capacity) {
		pq->capacity *= 2;
		pq->nodes = (queueNode *)realloc(pq->nodes, sizeof(queueNode) * pq->capacity);
	}

	pq->nodes[currPosition] = newNode;

	while ((currPosition > 0) && (pq->nodes[currPosition].priority < pq->nodes[parentPosition].priority)) {
		swapPQNodes(pq, currPosition, parentPosition);
		currPosition = parentPosition;
		parentPosition = getParentPQ(currPosition);
	}
	pq->usedSize++;
}

void dequeuePQ(priorityQueue *pq, queueNode *root) {
	int parentPosition = 0;
	int leftPosition = 0;
	int rightPosition = 0;

	memcpy(root, &pq->nodes[0], sizeof(queueNode));
	memset(&pq->nodes[0], 0, sizeof(queueNode));

	pq->usedSize--;
	swapPQNodes(pq, 0, pq->usedSize);

	leftPosition = getLeftChildPQ(0);
	rightPosition = leftPosition + 1;

	while (1) {
		int selChild = 0;

		if (leftPosition >= pq->usedSize) {
			break;
		}
		if (rightPosition >= pq->usedSize) {
			selChild = leftPosition;
		} else {
			if (pq->nodes[leftPosition].priority > pq->nodes[rightPosition].priority) {
				selChild = rightPosition;
			} else {
				selChild = leftPosition;
			}
		}
		if (pq->nodes[selChild].priority < pq->nodes[parentPosition].priority) {
			swapPQNodes(pq, parentPosition, selChild);
			parentPosition = selChild;
		} else {
			break;
		}
		leftPosition = getLeftChildPQ(parentPosition);
		rightPosition = leftPosition + 1;
	}
	if (pq->usedSize < (pq->capacity / 2)) {
		pq->capacity /= 2;
		pq->nodes = (queueNode *)realloc(pq->nodes, sizeof(queueNode) * pq->capacity);
	}
}

int getParentPQ(int index) {
	return (int) ((index - 1) / 2);
}
int getLeftChildPQ(int index) {
	return (2 * index) + 1;
}

void swapPQNodes(priorityQueue *pq, int index1, int index2) {
	int copySize = sizeof(queueNode);
	queueNode *temp = (queueNode *)malloc(copySize);

	memcpy(temp, &pq->nodes[index1], copySize);
	memcpy(&pq->nodes[index1], &pq->nodes[index2], copySize);
	memcpy(&pq->nodes[index2], temp, copySize);

	free(temp);
}

int isEmptyPQ(priorityQueue *pq) {
	return (pq->usedSize == 0);
}

int main() {
	priorityQueue *pq = createPQ(3);
	queueNode poped;

	queueNode nodes[7] = {
		{34, (void *)"코딩"},
		{12, (void *)"고객미팅"},
		{87, (void *)"커피타기"},
		{45, (void *)"문서작성"},
		{35, (void *)"디버깅"},
		{66, (void *)"이닦기"}
	};

	enqueuePQ(pq, nodes[0]);
	enqueuePQ(pq, nodes[1]);
	enqueuePQ(pq, nodes[2]);
	enqueuePQ(pq, nodes[3]);
	enqueuePQ(pq, nodes[4]);
	enqueuePQ(pq, nodes[5]);

	while (!isEmptyPQ(pq)) {
		dequeuePQ(pq, &poped);
		printf("작업명:%s, 우선순위:%d\n", (char *)poped.data, poped.priority);
	}

	return 0;
}