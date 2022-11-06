#include <cstdio>
#include <cstdlib>
#include <cstring>
#include<stdio.h>

typedef struct myNode {
	char *data;
	struct myNode *nextNode;
} Node;

typedef struct listStackSt {
	Node *list;
	Node *top;
	int count;
} listStack;

void createListStack(listStack **stack);
void destroyListStack(listStack *stack);

Node *createNode(char *data);
void destroyNode(Node *node);

void pushListStack(listStack *stack, Node *node);
Node *popListStack(listStack *stack);

Node *getTopListStack(listStack *stack);
int getSizeListStack(listStack *stack);
int isEmptyListStack(listStack *stack);


void createListStack(listStack **stack) {
	(*stack) = (listStack*)malloc(sizeof(listStack));
	(*stack)->list = NULL;
	(*stack)->top = NULL;
}

void destroyListStack(listStack *stack) {
	while (!isEmptyListStack(stack)) {
		Node *node = popListStack(stack);
		destroyNode(node);
		node = NULL;
	}
}

Node *createNode(char *data) {
	Node *node = (Node *)malloc(sizeof(Node));
	node->data = (char *)malloc(strlen(data) + 1);

	strcpy(node->data, data);

	node->nextNode = NULL;

	return node;
}

void destroyNode(Node *node) {
	if (node->data) {
		free(node->data);
	}
	if (node) {
		free(node);
	}
}

void pushListStack(listStack *stack, Node *node) {
	if (stack->list == NULL) {
		stack->list = node;
		stack->top = node;
	} else {
		Node *oldTop = stack->top;
		while (oldTop->nextNode != NULL) {
			oldTop = oldTop->nextNode;
		}
		oldTop->nextNode = node;
		stack->top = node;
	}
	stack->count++;
}
Node *popListStack(listStack *stack) {
	Node *top = stack->top;

	if (stack->list == top) {
		stack->list = NULL;
		stack->top = NULL;
	} else {
		Node *newTop = stack->list;
		while ((newTop != NULL) && (newTop->nextNode != top)) {
			newTop = newTop->nextNode;
		}
		stack->top = newTop;
		newTop->nextNode = NULL;
	}
	stack->count--;
	return top;
}

Node *getTopListStack(listStack *stack) {
	return stack->top;
}

int getSizeListStack(listStack *stack) {
	return stack->count;
}

int isEmptyListStack(listStack *stack) {
	if (stack->list == NULL) {
		return 1;
	}
	return 0;
}

int main() {
	listStack *stack = NULL;

	createListStack(&stack);

	pushListStack(stack, createNode((char *)"abc"));
	pushListStack(stack, createNode((char *)"def"));
	pushListStack(stack, createNode((char *)"efg"));

	printf("size:%d, top:%s\n", stack->count, stack->top->data);

	while (stack->list != NULL) {
		Node *pop = popListStack(stack);
		printf("%s\n", pop->data);
		destroyNode(pop);
	}
	destroyListStack(stack);
}