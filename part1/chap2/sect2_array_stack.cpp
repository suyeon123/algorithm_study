#include <cstdio>
#include <cstdlib>
#include<stdio.h>

typedef struct myNode {
	int data;
} Node;

typedef struct arrayStackSt {
	int capacity; //용량
	int top; // 최상위 노드 위치
	Node *nodes;
} ArrayStack;

void createAsStack(ArrayStack **stack, int capacity);
void destroyAsStack(ArrayStack *stack);
void pushAsStack(ArrayStack *stack, int data);
int popAsStack(ArrayStack *stack);

void createAsStack(ArrayStack **stack, int capacity) {
	(*stack) = (ArrayStack *)malloc(sizeof(ArrayStack));
	(*stack)->nodes = (Node *)malloc(sizeof(Node));

	(*stack)->capacity = capacity;
	(*stack)->top = 0;
}

void destroyAsStack(ArrayStack *stack) {
	if (stack->nodes) {
		free(stack->nodes);
	}
	if (stack) {
		free(stack);
	}
}

void pushAsStack(ArrayStack *stack, int data) {
	int position = stack->top;
	if (position < stack->capacity) {
		stack->nodes[position] = data;
		stack->top++;
	} else {
		printf("AsStack is full.\n");
	}
}

int popAsStack(ArrayStack *stack) {
	int position = stack->top;
	int data = stack->nodes[position].data;
	stack->nodes[position].data = 0;
	stack->top--;
	return data;
}