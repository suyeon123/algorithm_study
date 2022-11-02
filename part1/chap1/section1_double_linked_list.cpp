#include <cstdio>
#include <cstdlib>
#include<stdio.h>

/* 더블 링크드 리스트 */
/* 양방향 탐색이 가능
*/

typedef struct myNode 
{
	int data; // 데이터 필드
	struct myNode *prevNode;
	struct myNode *nextNode;
} Node;

/* 함수 선언 */
Node *dllCreateNode(int newData);
void dllDestroyNode(Node *node);
void dllAppendNode(Node **head, Node *newNode);
void dllRemoveNode(Node **head, Node *removeNode);
void dllInsertAfter(Node *currNode, Node *newNode);
Node *dllGetNodeAt(Node *head, int index);
int dllGetNodeCount(Node *head);

/* 노드 생성 */
Node *dllCreateNode(int newData) {
	Node *newNode = (Node *)malloc(sizeof(Node));

	newNode->data = newData;
	newNode->prevNode = NULL;
	newNode->nextNode = NULL;

	return newNode;
}

/* 노드 소멸 */
void dllDestroyNode(Node *node) {
	if (node != NULL) {
		free(node);
	}
}

/* 노드 추가 */
void dllAppendNode(Node **head, Node *newNode) {
	if ((*head) == NULL) {
		*head = newNode;
	} else {
		Node *tail = (*head);
		while (tail->nextNode != NULL) {
			tail = tail->nextNode;
		}
		tail->nextNode = newNode;
		newNode->prevNode = tail;
	}
}

/* 노드 제거 */
void dllRemoveNode(Node **head, Node *removeNode) {
	if ((*head) == removeNode) {
		*head = removeNode->nextNode;
		if ((*head) != NULL) {
			(*head)->prevNode = NULL;
		}
		removeNode->prevNode = NULL;
		removeNode->nextNode = NULL;
	} else {
		Node *tempNode = removeNode;
		if (tempNode->prevNode != NULL) {
			removeNode->prevNode->nextNode = tempNode->nextNode;
		}
		if (tempNode->nextNode != NULL) {
			removeNode->nextNode->prevNode = tempNode->prevNode;
		}
		removeNode->prevNode = NULL;
		removeNode->nextNode = NULL;
	}
}

/* 노드 삽입 */
void dllInsertAfter(Node *currNode, Node *newNode) {
	newNode->nextNode = currNode->nextNode;
	currNode->nextNode = newNode;
	if (currNode->nextNode != NULL) {
		currNode->nextNode->prevNode = newNode;
		currNode->nextNode = newNode;
	}
}

/* 노드 탐색 */
Node *dllGetNodeAt(Node *head, int index) {
	Node *currNode = head;

	while ((currNode != NULL) && (index > 0)) {
		currNode = currNode->nextNode;
		index--;
	}

	return currNode;
}

/* 노드 갯수 세기 */
int dllGetNodeCount(Node *head) {
	int count = 0;
	Node *currNode = head;

	while (currNode != NULL) {
		currNode = currNode->nextNode;
		count++;
	}
	return count;
}

int main() {
	Node *list = NULL;
	Node *newNode = NULL;
	Node *currNode = NULL;

	// 노드 5개 추가
	for (int i = 0; i < 5; i++) {
		newNode = dllCreateNode(i);
		dllAppendNode(&list, newNode);
	}

	// 리스트 출력
	for (int i = 0; i < dllGetNodeCount(list); i++) {
		printf("[%d] %d\n", i, dllGetNodeAt(list, i)->data);
	}

	// 세번째 노드 뒤에 노드 추가
	newNode = dllCreateNode(3000);
	currNode = dllGetNodeAt(list, 2);
	dllInsertAfter(currNode, newNode);

	// 리스트 출력
	for (int i = 0; i < dllGetNodeCount(list); i++) {
		printf("[%d] %d\n", i, dllGetNodeAt(list, i)->data);
	}

	// 리스트 역순으로 출력
	for (int i = dllGetNodeCount(list); i != 0; i--) {
		printf("[%d] %d\n", (i-1), dllGetNodeAt(list, i-1)->data);
	}

	// 모든 노드 제거
	for (int i = 0; i < dllGetNodeCount(list); i++) {
		currNode = dllGetNodeAt(list, i);
		if (currNode) {
			dllRemoveNode(&list, currNode);
			dllDestroyNode(currNode);
		}
	}

	return 0;
}