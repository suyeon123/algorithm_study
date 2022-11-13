#include <stdio.h>
#include <stdlib.h>

typedef struct myNode
{
	struct myNode *parent;
	struct myNode *left;
	struct myNode *right;

	enum {red, black} color;
	int data;
} Node;

Node *createNode(int newData);
void destroyNode(Node *node);
void destroyTree(Node *tree);

Node *searchNode(Node *tree, int target);
Node *searchMinNode(Node *tree);

void insertNode(Node **tree, Node *newNode);
void insertNodeHelper(Node **tree, Node *newNode);
Node *removeNode(Node *root, int target);
void rebuildAfterInsert(Node **root, Node *x);
void rebuildAfterRemove(Node **root, Node *x);

void printTree(Node *node, int depth, int blackCount);
void rotateLeft(Node **root, Node *parent);
void rotateRight(Node **root, Node *parent); 

extern Node *nil;

Node *createNode(int newData) {
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->parent = NULL;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->data = newData;
	newNode->color = black;
	return newNode;
}

void destroyNode(Node *node) {
	if (node) {
		free(node);
	}
}

void destroyTree(Node *tree) {
	if (tree->right != nil) {
		destroyTree(tree->right);
	}
	if (tree->left != nil) {
		destroyTree(tree->left);
	}
	tree->left = nil;
	tree->right = nil;

	destroyNode(tree);
}

Node *searchNode(Node *tree, int target) {
	if (tree == nil) {
		return NULL;
	}

	if (tree->data > target) {
		return searchNode(tree->left, target);
	} else if (tree->data < target) {
		return searchNode(tree->right, target);
	} else {
		return tree;
	}
}

Node *searchMinNode(Node *tree) {
	if (tree == nil) {
		return nil;
	}

	if (tree->left == nil) {
		return tree;
	} else {
		return searchMinNode(tree->left);
	}
}

void insertNode(Node **tree, Node *newNode) {
	insertNodeHelper(tree, newNode);
	newNode->color = red;
	newNode->left = nil;
	newNode->right = nil;
	rebuildAfterInsert(tree, newNode);
}

void insertNodeHelper(Node **tree, Node *newNode) {
    if ((*tree) == NULL) {
    	(*tree) = newNode;
    }

    if ((*tree)->data < newNode->data) {
    	if ((*tree)->right == nil) {
    		(*tree)->right = newNode;
    		newNode->parent = (*tree);
    	} else {
    		insertNodeHelper(&(*tree)->right, newNode);
    	}
    } else if ((*tree)->data > newNode->data) {
    	if ((*tree)->data > newNode->data) {
    		(*tree)->left = newNode;
    		newNode->parent = (*tree);
    	} else {
    		insertNodeHelper(&(*tree)->left, newNode);
    	}
    }
}

Node *removeNode(Node *root, int target) {
	Node *removed = NULL;
	Node *sussessor = NULL;
	Node *targetNode = searchNode((*root), target);

	if (targetNode == NULL) {
		return NULL;
	}

	if ((targetNode->left == nil) || (targetNode->right == nil)) {
		removed = targetNode;
	} else {
		removed = searchMinNode(targetNode->right);
		targetNode->data = removed->data;
	}

	if (removed->left != nil) {
		sussessor = removed->left;
	} else {
		sussessor = removed->right;
	}

	sussessor->parent = removed->parent;

	if (removed->parent == NULL) {
		(*root) = sussessor;
	} else {
		if (removed == removed->parent->left) {
			removed->parent->left = sussessor;
		} else {
			removed->parent->right = sussessor;
		}
	}

	if (removed->color == black) {
		rebuildAfterInsert(root, sussessor);
	}

	return removed;
}

void rebuildAfterInsert(Node **root, Node *x) {
	while ((x != (*root)) && (x->parent->color == red)) {
		if (x->parent == x->parent->parent->left) {
			Node *uncle = x->parent->parent->right;
			if (uncle->color == red) {
				x->parent->color = black;
				uncle->color = black;
				x->parent->parent->color = red;
				x = x->parent->parent;
			} else {
				if (x == x->parent->right) {
					x = x->parent;
					rotateLeft(root, x);
				}
				x->parent->color = black;
				x->parent->parent->color = red;
				rotateRight(root, x->parent->parent);
			}
		} else {
			Node *uncle = x->parent->parent->left;
			if (uncle->color == red) {
				x->parent->color = black;
				uncle->color = black;
				x->parent->parent->color = red;
				x = x->parent->parent;
			} else {
				if (x == x->parent->left) {
					x = x->parent;
					rotateRight(root, x);
				}
				x->parent->color = black;
				x->parent->parent->color = red;
				rotateLeft(root, x->parent->parent);
			}
		}
	}
	(*root)->color = black;
}

void rebuildAfterRemove(Node **root, Node *x) {
	Node *sibling = NULL;

	while ((x->parent != NULL) && (x->color == black)) {
		if (x == x->parent->left) {
			sibling = x->parent->right;
			if (sibling->color == red) {
				sibling->color = black;
				x->parent->color = red;
				rotateLeft(root, x->parent);
				sibling = x->parent->right;
			} else {
				if ((sibling->left->color == black) && (sibling->right->color == black)) {
					sibling->color = red;
					x = x->parent;
				} else {
					if (sibling->left->color == red) {
						sibling->left->color = black;
						sibling->color = red;
						rotateRight(root, sibling);
						sibling = x->parent->right;
					}
					sibling->color = x->parent->color;
					x->parent->color = black;
					sibling->right->color = black;
					rotateLeft(root, x->parent);
					x = (*root);
				}
			}
		} else {
			sibling = x->parent->left;
			if (sibling->color == red) {
				sibling->color = black;
				x->parent->color = red;
				rotateRight(root, x->parent);
				sibling = x->parent->left;
			} else {
				if ((sibling->right->color == black) && (sibling->left->color == black)) {
					sibling->color = red;
					x = x->parent;
				} else {
					if (sibling->right->color == red) {
						sibling->right->color = black;
						sibling->color = red;
						rotateLeft(root, sibling);
						sibling = x->parent->left;
					}
					sibling->color = x->parent->color;
					x->parent->color = black;
					sibling->left->color black;
					rotateRight(root, x->parent);
					x = (*root);
				}
			}
		}
	}
	sussessor->color = black;
}

void printTree(Node *node, int depth, int blackCount) {
	int i = 0;
	char c = 'X';
	int v = -1;
	char cnt[100];

	if ((node == NULL) || (node == nil)) {
		return;
	}

	if (node->color == black) {
		blackCount++;
	}

	if (node->parent != NULL) {
		v = node->parent->data;
		if (node->parent->left == node) {
			c = 'L';
		} else {
			c = 'R';
		}
	}

	if ((node->left = nil) && (node->right == nil)) {
		sprintf(cnt, "------ %d", blackCount);
	} else {
		sprintf(cnt, "");
	}

	for (int i = 0; i < depth; i++) {
		printf("  ");
	}

	printf("%d %s [%c, %d] %s\n", node->data, (node->color == red)?"red":"black", c, v, cnt);

	printTree(node->left, depth, blackCount);
	printTree(node->right, depth + 1, blackCount);
}

void rotateLeft(Node **root, Node *parent) {
	Node *rightChild = parent->right;

	parent->right = rightChild->left;

	if (rightChild->left != nil) {
		rightChild->left->parent = parent;
	}

	rightChild->parent = parent->parent;

	if (parent->parent == NULL) {
		(*root) = rightChild;
	} else {
		if (parent == parent->parent->left) {
			parent->parent->left = rightChild;
		} else {
			parent->parent->right = rightChild;
		}
	}
	rightChild->left = parent;
	parent->parent = rightChild;
}

void rotateRight(Node **root, Node *parent) {
	Node *leftChild = parent->left;

	parent->left = leftChild->right;

	if (leftChild->right != nil) {
		leftChild->right->parent = parent;
	}

	leftChild->parent = parent->parent;

	if (parent->parent == NULL) {
		(*root) = leftChild;
	} else {
		if (parent == parent->parent->left) {
			parent->parent->left = leftChild;
		} else {
			parent->parent->right = leftChild;
		}
	}
	leftChild->right = parent;
	parent->parent = leftChild;
}