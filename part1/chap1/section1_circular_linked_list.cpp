#include <cstdio>
#include <cstdlib>
#include<stdio.h>

typedef struct myNode 
{
	int data; // 데이터 필드
	struct myNode *prevNode;
	struct myNode *nextNode;
} Node;

/* 함수 선언 */
Node *cllCreateNode(int newData);
void cllDestroyNode(Node *node);
void cllAppendNode(Node **head, Node *newNode);
void cllRemoveNode(Node **head, Node *removeNode);
void cllInsertAfter(Node *currNode, Node *newNode);
Node *cllGetNodeAt(Node *head, int index);
int cllGetNodeCount(Node *head);

/* 노드 생성 */
Node *cllCreateNode(int newData) {
	Node *newNode = (Node *)malloc(sizeof(Node));

	newNode->data = newData;
	newNode->prevNode = NULL;
	newNode->nextNode = NULL;

	return newNode;
}

/* 노드 소멸 */
void cllDestroyNode(Node *node) {
	if (node != NULL) {
		free(node);
	}
}

/* 노드 추가 */
void cllAppendNode(Node **head, Node *newNode) {
	if ((*head) == NULL) {
		*head = newNode;
		(*head)->prevNode = *head;
		(*head)->nextNode = *head;
	} else {
		Node *tail = (*head)->prevNode;

		tail->nextNode->prevNode = newNode;
		tail->nextNode = newNode;

		newNode->nextNode = *head;
		newNode->prevNode = tail;
	}
}

/* 노드 제거 */
void cllRemoveNode(Node **head, Node *removeNode) {
	if ((*head) == removeNode) {
		(*head)->prevNode->nextNode = removeNode->nextNode;
		(*head)->nextNode->prevNode = removeNode->prevNode;

		*head = removeNode->nextNode;

		removeNode->prevNode = NULL;
		removeNode->nextNode = NULL;
	} else {
		Node *tempNode = removeNode;

		removeNode->prevNode->nextNode = tempNode->nextNode;
		removeNode->nextNode->prevNode = tempNode->prevNode;

		removeNode->prevNode = NULL;
		removeNode->nextNode = NULL;
	}
}

/* 노드 삽입 */
void cllInsertAfter(Node *currNode, Node *newNode) {
	newNode->nextNode = currNode->nextNode;
	newNode->prevNode = currNode;

	currNode->nextNode->prevNode = newNode;
	currNode->nextNode = newNode;
}

/* 노드 탐색 */
Node *cllGetNodeAt(Node *head, int index) {
	Node *currNode = head;

	while ((currNode != NULL) && (index > 0)) {
		currNode = currNode->nextNode;
		index--;
	}

	return currNode;
}

/* 노드 갯수 세기 */
int cllGetNodeCount(Node *head) {
	int count = 0;
	Node *currNode = head;

	while (currNode != NULL) {
		currNode = currNode->nextNode;
		count++;
		if (currNode == head) {
			break;
		}
	}

	return count;
}

int main() {
	Node *list = NULL;
	Node *newNode = NULL;
	Node *currNode = NULL;

	// 노드 5개 추가
	for (int i = 0; i < 5; i++) {
		newNode = cllCreateNode(i);
		cllAppendNode(&list, newNode);
	}

	// 리스트 출력
	for (int i = 0; i < cllGetNodeCount(list); i++) {
		printf("[%d] %d\n", i, cllGetNodeAt(list, i)->data);
	}

	// 세번째 노드 뒤에 노드 추가
	newNode = cllCreateNode(3000);
	currNode = cllGetNodeAt(list, 2);
	cllInsertAfter(currNode, newNode);

	// 리스트 출력
	for (int i = 0; i < cllGetNodeCount(list); i++) {
		printf("[%d] %d\n", i, cllGetNodeAt(list, i)->data);
	}

	// 모든 노드 제거
	for (int i = 0; i < cllGetNodeCount(list); i++) {
		currNode = cllGetNodeAt(list, i);
		if (currNode) {
			cllRemoveNode(&list, currNode);
			cllDestroyNode(currNode);
		}
	}

	return 0;
}