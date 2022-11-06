#include <cstdio>
#include <cstdlib>
#include <cstring>
#include<stdio.h>

typedef struct myNode {
	struct myNode *left;
	struct myNode *right;

	char data;
} expressionTreeNode;

expressionTreeNode *createTreeNode(char newData);
void destroyTreeNode(expressionTreeNode *node);
void destroyTree(expressionTreeNode *root);
void printPreorderTree(expressionTreeNode *node);
void printInorderTree(expressionTreeNode *node);
void printPostorderTree(expressionTreeNode *node);
void buildExpressionTree(char *postExpression, expressionTreeNode **node);
double evaluate(expressionTreeNode *tree);

expressionTreeNode *createTreeNode(char newData) {
	expressionTreeNode *newNode = (expressionTreeNode *)malloc(sizeof(expressionTreeNode));
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->data = newData;

	return newNode;
}

void destroyTreeNode(expressionTreeNode *node) {
	if (node) {
		free(node);
	}
}

void destroyTree(expressionTreeNode *root) {
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

void printPreorderTree(expressionTreeNode *node) {
	if (node == NULL) {
		return;
	}
	printf(" %c", node->data);
	printPreorderTree(node->left);
	printPreorderTree(node->right);
}

void printInorderTree(expressionTreeNode *node) {
	if (node == NULL) {
		return;
	}
	printInorderTree(node->left);
	printf(" %c", node->data);
	printInorderTree(node->right);
}

void printPostorderTree(expressionTreeNode *node) {
	if (node == NULL) {
		return;
	}
	printPostorderTree(node->left);
	printPostorderTree(node->right);
	printf(" %c", node->data);
}

void buildExpressionTree(char *postExpression, expressionTreeNode **node) {
	expressionTreeNode *newNode = NULL;
	int len = strlen(postExpression);
	char token = postExpression[len-1];
	postExpression[len-1] = '\0';

	switch (token) {
		case '+' :
		case '-' :
		case '*' :
		case '/' :
			(*node) = createTreeNode(token);
			buildExpressionTree(postExpression, &(*node)->right);
			buildExpressionTree(postExpression, &(*node)->left);
			break;
		default:
			(*node) = createTreeNode(token);
			break;
	}
}

double evaluate(expressionTreeNode *tree) {
	char temp[2];

	double left = 0;
	double right = 0;
	double result = 0;

	if (tree == NULL) {
		return 0;
	}

	switch (tree->data) {
	case '+' :
		left = evaluate(tree->left);
		right = evaluate(tree->right);
		result = left + right;
		break;
	case '-' :
	    left = evaluate(tree->left);
		right = evaluate(tree->right);
		result = left - right;
		break;
	case '*' :
		left = evaluate(tree->left);
		right = evaluate(tree->right);
		result = left * right;
		break;
	case '/' :
		left = evaluate(tree->left);
		right = evaluate(tree->right);
		result = left / right;
		break;
	default:
		memset(temp, 0, sizeof(temp));
		temp[0] = tree->data;
		result = atof(temp);
		break;
	}
	return result;
}

int main() {
	expressionTreeNode *root = NULL;

	char postExpression[20] = "71*52-/";
	buildExpressionTree(postExpression, &root);

	printf("preorder\n");
	printPreorderTree(root);
	printf("\n");

	printf("inorder\n");
	printInorderTree(root);
	printf("\n");

	printf("postorder\n");
	printPostorderTree(root);
	printf("\n");

	printf("evaluate result:%f\n", evaluate(root));

	destroyTree(root);

	return 0;
}