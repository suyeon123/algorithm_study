#include <cstdio>
#include <cstring>
#include <stdlib.h> 
#include<stdio.h>

typedef struct myNode {
	struct myNode *left;
	struct myNode *right;
	int data;
} Node;

Node *createNode(int newData);
void destroyNode(Node *node);
void destroyTree(Node *tree);

Node *searchNode(Node *tree, int target);
Node *searchMinNode(Node *tree);
void insertNode(Node *tree, Node *child);
Node *removeNode(Node *tree, Node *parent, int target);

void inorderPrintTree(Node *tree);

Node *createNode(int newData) {
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->data = newData;

	return newNode;
}

void destroyNode(Node *node) {
	if (node) {
		free(node);
	}
}

void destroyTree(Node *tree) {
	if (tree != NULL) {
		if (tree->left != NULL) {
			destroyTree(tree->left);
			tree->left = NULL;
		}
		if (tree->right != NULL) {
			destroyTree(tree->right);
			tree->right = NULL;
		}
		destroyNode(tree);
	}
}

Node *searchNode(Node *tree, int target) {
	if (tree == NULL) {
		return NULL;
	}

	if (tree->data < target) {
		return searchNode(tree->left, target);
	} else if (tree->data > target) {
		return searchNode(tree->right, target);
	} else {
		return tree;
	}
}

Node *searchMinNode(Node *tree) {
	if (tree == NULL) {
		return NULL;
	}

	if (tree->left == NULL) {
		return tree;
	} else {
		return searchMinNode(tree->left);
	}
}

void insertNode(Node *tree, Node *child) {
	if (tree->data < child->data) {
		if (tree->right == NULL) {
			tree->right = child;
		} else {
			insertNode(tree->right, child);
		}
	} else if (tree->data > child->data) {
		if (tree->left == NULL) {
			tree->left = child;
		} else {
			insertNode(tree->left, child);
		}
	}
}

Node *removeNode(Node *tree, Node *parent, int target) {
	Node *removed = NULL;

	if (tree == NULL) {
		return NULL;
	}

	if (tree->data > target) {
		removed = removeNode(tree->left, tree, target);
	} else if (tree->data < target) {
		removed = removeNode(tree->right, tree, target);
	} else {
		removed = tree;
		// 자식 X
		if ((tree->left == NULL) && (tree->right == NULL)) {
			if (parent->left == tree) {
				parent->left = NULL;
			}
			if (parent->right == tree) {
				parent->right = NULL;
			}
		} else { // 양 쪽 자식 있는 경우
			if ((tree->left != NULL) && (tree->right != NULL)) {
				Node *minNode = searchMinNode(tree->right);
				minNode = removeNode(tree, NULL, minNode->data);
				tree->data = minNode->data;
			} else { // 한 쪽만 자식 있는 경우
				Node *temp = NULL;
				if (tree->left != NULL) {
					temp = tree->left;
				} else {
					temp = tree->right;
				}
				if (parent->left = tree) {
					parent->left = temp;
				} else {
					parent->right = temp;
				}
			}
		}
	}
	return removed;
}

void inorderPrintTree(Node *tree) {
	if (tree == NULL) {
		return;
	}
	inorderPrintTree(tree->left);
	printf("%d ", tree->data);
	inorderPrintTree(tree->right);
}

int main() {
	Node *tree = createNode(123);
	Node *node = NULL;

	insertNode(tree, createNode(10));
	insertNode(tree, createNode(2793));
	insertNode(tree, createNode(213));
	insertNode(tree, createNode(5));
	insertNode(tree, createNode(56));
	insertNode(tree, createNode(5167));
	insertNode(tree, createNode(967));
	insertNode(tree, createNode(24));
	insertNode(tree, createNode(157));
	insertNode(tree, createNode(63));
	insertNode(tree, createNode(38));
	insertNode(tree, createNode(101));

	inorderPrintTree(tree);
	printf("\n");

	printf(" Remove 101 ...\n");
	node = removeNode(tree, NULL, 101);
	printf("Remove %d completed.\n", node->data);
	destroyNode(node);
	inorderPrintTree(tree);
	printf("\n");

	printf(" Remove 157 ...\n");
	node = removeNode(tree, NULL, 157);
	printf("Remove %d completed.\n", node->data);
	destroyNode(node);
	inorderPrintTree(tree);
	printf("\n");

	printf(" Insert 117 ...\n");
	insertNode(tree, createNode(117));
	printf("Remove %d completed.\n", node->data);
	inorderPrintTree(tree);
	printf("\n");

	destroyTree(tree);

	return 0;
}