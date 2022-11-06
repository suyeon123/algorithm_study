#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include<stdio.h>

enum
{
	LEFT_SMALL_PARENTHESIS = 0,
	RIGHT_SMALL_PARENTHESIS,
	LEFT_BIG_PARENTHESIS,
	RIGHT_BIG_PARENTHESIS,
};

typedef struct myNode {
	char *data;
	struct myNode *nextNode;
} Node;

typedef struct listStackSt {
	Node *list;
	Node *top;
	int count;
} listStack;

std::string parenthesis[] = {"(", ")", "[", "]"};
char number[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
std::string example1 = "(()[[]])([])";
std::string example2 = "[][]((])";
//std::string example1[] = {"(", "(", ")", "[", "[", "]", "]", ")", "(", "[", "]", ")"};
//std::string example2[] = {"[", "]", "[", "]", "(", "(", "]", ")"};

void createListStack(listStack **stack);
void destroyListStack(listStack *stack);

Node *createNode(char *data);
void destroyNode(Node *node);

void pushListStack(listStack *stack, Node *node);
Node *popListStack(listStack *stack);

Node *getTopListStack(listStack *stack);
int getSizeListStack(listStack *stack);
int isEmptyListStack(listStack *stack);

int isNum(char *data);
int calculate(std::string expresstion);

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
	node->data = (char *)malloc(strlen(data));

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

int isNum(char *data) {
	for (int i = 0; i < strlen(data); i++) {
		if (isdigit(data[i]) == 0) {
            return 0;
        }
	}
	return 1;
}

int calculate(std::string expresstion) {
	int index = 0;
	listStack *stack;
	std::string read = "";
	Node *popNode = NULL;
	Node *pushNode = NULL;
	int needMultiply = 0;
	int cal = 0;
	int result = 0;

	createListStack(&stack);

	while (index < expresstion.size()) {
	//while (index < expresstion->size()) {
		read = expresstion.at(index);
		if (read.compare(parenthesis[RIGHT_SMALL_PARENTHESIS]) == 0) {
			printf("small %s\n", read.c_str());
			//while (std::string(popNode->data).compare(parenthesis[LEFT_SMALL_PARENTHESIS]) != 0) {
			do {
				popNode = popListStack(stack);
				printf("pop %s\n", popNode->data);
				if (popNode->data == parenthesis[LEFT_SMALL_PARENTHESIS]) {
					destroyNode(popNode);
					break;
				}
				if (popNode->data == parenthesis[LEFT_BIG_PARENTHESIS]) {
					destroyListStack(stack);
					return 0;
				}
				if (isNum(popNode->data)) {
					cal = std::stoi(popNode->data);
					needMultiply = 1;
				}
				destroyNode(popNode);
			} while(1);

			if (needMultiply) {
				cal = 2 * cal;
				needMultiply = 0;
			} else {
				cal = 2;
			}

			if (stack->top != NULL) {
				if (isNum(stack->top->data)) {
					popNode = popListStack(stack);
					cal = cal + std::stoi(popNode->data);
					//cal = cal + getNum(popNode->data);
					destroyNode(popNode);
				}
			}
			pushNode = createNode((char *)std::to_string(cal).c_str());
			printf("push %s\n", pushNode->data);
			pushListStack(stack, pushNode);
			cal = 0;
		} else if (read.compare(parenthesis[RIGHT_BIG_PARENTHESIS]) == 0) {
			printf("big %s\n", read.c_str());
			do {
				popNode = popListStack(stack);
				printf("pop %s\n", popNode->data);
				if (popNode->data == parenthesis[LEFT_BIG_PARENTHESIS]) {
					destroyNode(popNode);
					break;
				}
				if (popNode->data == parenthesis[LEFT_SMALL_PARENTHESIS]) {
					destroyListStack(stack);
					return 0;
				}
				if (isNum(popNode->data)) {
					cal = std::stoi(popNode->data);
					needMultiply = 1;
				}
				destroyNode(popNode);
			} while(1);

			if (needMultiply) {
				cal = 3 * cal;
				needMultiply = 0;
			} else {
				cal = 3;
			}

			if (stack->top != NULL) {
				if (isNum(stack->top->data)) {
					popNode = popListStack(stack);
					cal = cal + std::stoi(popNode->data);
					//cal = cal + getNum(popNode->data);
					destroyNode(popNode);
				}
			}

			pushNode = createNode((char *)std::to_string(cal).c_str());
			printf("push %s\n", pushNode->data);
			pushListStack(stack, pushNode);
			cal = 0;
		} else {
			pushNode = createNode((char *)read.c_str());
			printf("push %s\n", pushNode->data);
			pushListStack(stack, pushNode);
		}
		index++;
	}
	if (stack->top != NULL) {
		popNode = popListStack(stack);
		if (isNum(popNode->data)) {
			result = std::stoi(popNode->data);
		}
	}
	return result;

}

int main() {
	int result = 0;
	result = calculate(example1);
	if (result != 0) {
		printf("example1 result : %d\n", result);
	} else {
		printf("example1 is wrong expresstion : %d\n", result);
	}
	result = calculate(example2);
	if (result != 0) {
		printf("example1 result : %d\n", result);
	} else {
		printf("example1 is wrong expresstion : %d\n", result);
	}
	return 0;
}