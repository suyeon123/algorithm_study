#include <cstdio>
#include <cstdlib>
#include<stdio.h>

typedef struct myNode {
	struct myNode *leftChild;
	struct myNode *rightSibling;

	char data;
} treeNode;

treeNode *createTreeNode(char newData);
void destroyTreeNode(treeNode *node);
void destroyTree(treeNode *root);

void addChildNode(treeNode *parentNode, treeNode *childNode);
void printTree(treeNode *node, int depth);

treeNode *createTreeNode(char newData) {
	treeNode *newNode = (treeNode *)malloc(sizeof(treeNode));
	newNode->leftChild = NULL;
	newNode->rightSibling = NULL;
	newNode->data = newData;

	return newNode;
}

void destroyTreeNode(treeNode *node) {
	if (node) {
		free(node);
	}
}

void destroyTree(treeNode *root) {
	if (root->rightSibling != NULL) {
		destroyTree(root->rightSibling);
	}
	if (root->leftChild != NULL) {
		destroyTree(root->leftChild);
	}
	root->leftChild = NULL;
	root->rightSibling = NULL;
	destroyTreeNode(root);
}

void addChildNode(treeNode *parentNode, treeNode *childNode) {
	if (parentNode->leftChild == NULL) {
		parentNode->leftChild = childNode;
	} else {
		treeNode *tempNode = parentNode->leftChild;
		while (tempNode->rightSibling != NULL) {
			tempNode = tempNode->rightSibling;
		}
		tempNode->rightSibling = childNode;
	}
}

void printTree(treeNode *node, int depth) {
	for (int i = 0; i < depth; i++) {
		printf(" ");
	}
	printf("%c\n", node->data);

	if (node->leftChild != NULL) {
		printTree(node->leftChild, depth+1);
	}
	if (node->rightSibling != NULL) {
		printTree(node->rightSibling, depth);
	}
}

int main() {
	treeNode *root = createTreeNode('A');

	treeNode *B = createTreeNode('B');
	treeNode *C = createTreeNode('C');
	treeNode *D = createTreeNode('D');
	treeNode *E = createTreeNode('E');
	treeNode *F = createTreeNode('F');
	treeNode *G = createTreeNode('G');
	treeNode *H = createTreeNode('H');
	treeNode *I = createTreeNode('I');
	treeNode *J = createTreeNode('J');
	treeNode *K = createTreeNode('K');

	addChildNode(root, B);
	addChildNode(B, C);
	addChildNode(B, D);
	addChildNode(D, E);
	addChildNode(D, F);
	addChildNode(root, G);
	addChildNode(G, H);
	addChildNode(root, I);
	addChildNode(I, J);
	addChildNode(J, K);

	printTree(root, 0);

	destroyTree(root);
	return 0;
}