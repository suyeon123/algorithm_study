#include <cstdio>
#include <cstdlib>
#include<stdio.h>

typedef struct myNode {
	struct myNode *left;
	struct myNode *right;

	char data;
} binaryTreeNode;

binaryTreeNode *createTreeNode(char newData);
void destroyTreeNode(binaryTreeNode *node);
void destroyTree(binaryTreeNode *root);

binaryTreeNode *createTreeNode(char newData) {
	binaryTreeNode *newNode = (binaryTreeNode *)malloc(sizeof(binaryTreeNode));
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->data = newData;

	return newNode;
}

void destroyTreeNode(binaryTreeNode *node) {
	if (node) {
		free(node);
	}
}

void destroyTree(binaryTreeNode *root) {
	if (root->right != NULL) {
		destroyTree(root->right);
	}
	if (root->left != NULL) {
		destroyTree(root->left);
	}
	root->left = NULL;
	root->right = NULL;
	destroyTreeNode(root);
}

void printPreorderTree(binaryTreeNode *node) {
	if (node == NULL) {
		return;
	}
	printf(" %c", node->data);
	printPreorderTree(node->left);
	printPreorderTree(node->right);
}

void printInorderTree(binaryTreeNode *node) {
	if (node == NULL) {
		return;
	}
	printInorderTree(node->left);
	printf(" %c", node->data);
	printInorderTree(node->right);
}

void printPostorderTree(binaryTreeNode *node) {
	if (node == NULL) {
		return;
	}
	printPostorderTree(node->left);
	printPostorderTree(node->right);
	printf(" %c", node->data);
}

int main() {
	binaryTreeNode *root = createTreeNode('A');

	binaryTreeNode *B = createTreeNode('B');
	binaryTreeNode *C = createTreeNode('C');
	binaryTreeNode *D = createTreeNode('D');
	binaryTreeNode *E = createTreeNode('E');
	binaryTreeNode *F = createTreeNode('F');
	binaryTreeNode *G = createTreeNode('G');

	root->left = B;
	B->left = C;
	B->right = D;

	root->right = E;
	E->left = F;
	E->right = G;

	printf("preorder tree\n");
	printPreorderTree(root);
	printf("\n");

	printf("inorder tree\n");
	printInorderTree(root);
	printf("\n");

	printf("postorder tree\n");
	printPostorderTree(root);
	printf("\n");

	destroyTree(root);
	return 0;
}