#include <stdlib.h>
#include <memory.h>
#include<stdio.h>

typedef struct myNode {
	int data;
} heapNode;

typedef struct tagHeap {
	heapNode *nodes;
	int capacity;
	int usedSize;
} heap;

heap *createHeap(int init);
void destroyHeap(heap *h);
void insertHeap(heap *h, int newData);
void deleteMinHeap(heap *h, heapNode *root);
int getParentHeap(int index);
int getLeftChildHeap(int index);
void swapHeapNodes(heap *h, int index1, int index2);
void printHeapNodes(heap *h);

heap *createHeap(int init) {
	heap *newHeap = (heap *)malloc(sizeof(heap));
	newHeap->capacity = init;
	newHeap->usedSize = 0;
	newHeap->nodes = (heapNode *)malloc(sizeof(heapNode) * newHeap->capacity);
	printf("New heap created. capacity:%d, size: %ld\n", init, sizeof(heapNode));
	return newHeap;
}

void destroyHeap(heap *h) {
	if (h->nodes) {
		free(h->nodes);
	}
	if (h) {
		free(h);
	}
}

void insertHeap(heap *h, int newData) {
	int currPosition = h->usedSize;
	int parentPosition = getParentHeap(currPosition);

	if (h->usedSize == h->capacity) {
		h->capacity *= 2;
		h->nodes = (heapNode *)realloc(h->nodes, sizeof(heapNode) * h->capacity);
	}

	h->nodes[currPosition].data = newData;

	while ((currPosition > 0) && (h->nodes[currPosition].data < h->nodes[parentPosition].data)) {
		swapHeapNodes(h, currPosition, parentPosition);
		currPosition = parentPosition;
		parentPosition = getParentHeap(currPosition);
	}
	h->usedSize++;
}

void deleteMinHeap(heap *h, heapNode *root) {
	int parentPosition = 0;
	int leftPosition = 0;
	int rightPosition = 0;

	memcpy(root, &h->nodes[0], sizeof(heapNode));
	memset(&h->nodes[0], 0, sizeof(heapNode));

	h->usedSize--;
	swapHeapNodes(h, 0, h->usedSize);

	leftPosition = getLeftChildHeap(0);
	rightPosition = leftPosition + 1;

	while (1) {
		int selChild = 0;

		if (leftPosition >= h->usedSize) {
			break;
		}
		if (rightPosition >= h->usedSize) {
			selChild = leftPosition;
		} else {
			if (h->nodes[leftPosition].data > h->nodes[rightPosition].data) {
				selChild = rightPosition;
			} else {
				selChild = leftPosition;
			}
		}
		if (h->nodes[selChild].data < h->nodes[parentPosition].data) {
			swapHeapNodes(h, parentPosition, selChild);
			parentPosition = selChild;
		} else {
			break;
		}
		leftPosition = getLeftChildHeap(parentPosition);
		rightPosition = leftPosition + 1;
	}
	if (h->usedSize < (h->capacity / 2)) {
		h->capacity /= 2;
		h->nodes = (heapNode *)realloc(h->nodes, sizeof(heapNode) * h->capacity);
	}
}

int getParentHeap(int index) {
	return (int) ((index - 1) / 2);
}
int getLeftChildHeap(int index) {
	return (2 * index) + 1;
}

void swapHeapNodes(heap *h, int index1, int index2) {
	int copySize = sizeof(heapNode);
	heapNode *temp = (heapNode *)malloc(copySize);

	memcpy(temp, &h->nodes[index1], copySize);
	memcpy(&h->nodes[index1], &h->nodes[index2], copySize);
	memcpy(&h->nodes[index2], temp, copySize);

	free(temp);
}

void printHeapNodes(heap *h) {
	for (int i = 0; i < h->usedSize; i++) {
		printf("%d ", h->nodes[i].data);
	}
	printf("\n");
}

int main() {
	heap *h = createHeap(3);
	heapNode minNode;

	insertHeap(h, 12);
	insertHeap(h, 87);
	insertHeap(h, 111);
	insertHeap(h, 34);
	insertHeap(h, 16);
	insertHeap(h, 75);
	printHeapNodes(h);

	deleteMinHeap(h, &minNode);
	printHeapNodes(h);

	deleteMinHeap(h, &minNode);
	printHeapNodes(h);

	deleteMinHeap(h, &minNode);
	printHeapNodes(h);

	deleteMinHeap(h, &minNode);
	printHeapNodes(h);

	deleteMinHeap(h, &minNode);
	printHeapNodes(h);

	deleteMinHeap(h, &minNode);
	printHeapNodes(h);

	return 0;
}