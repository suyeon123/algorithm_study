#include <cstdio>
#include <cstdlib>
#include <cstring>
#include<stdio.h>

typedef struct myNode 
{
	int data; // 데이터 필드
	struct myNode *nextNode; // 다음 노드를 가리키는 포인터
} Node;

/* 함수 선언 */
Node *sllCreateNode(int newData);
void sllDestroyNode(Node *node);
void sllDestroyAll(Node **list);
void sllAppendNode(Node **head, Node *newNode);
void sllRemoveNode(Node **head, Node *removeNode);
void sllInsertAfter(Node *currNode, Node *newNode);
void sllInsertBefore(Node **head, Node *currNode, Node *newNode);
void sllInsertHead(Node **currHead, Node *newHead);
Node *sllGetNodeAt(Node *head, int index);
int sllGetNodeCount(Node *head);
Node *seqeunceSearch(Node *head, int target);
Node *seqeunceMoveToFront(Node **head, int target);
Node *seqeunceTranspose(Node **head, int target);

/* 노드 생성 */
Node *sllCreateNode(int newData) {
	Node *newNode = (Node *)malloc(sizeof(Node));

	newNode->data = newData;
	newNode->nextNode = NULL;

	return newNode;
}

/* 노드 소멸 */
void sllDestroyNode(Node *node) {
	if (node != NULL) {
		free(node);
	}
}

void sllDestroyAll(Node **list) {
	int count = sllGetNodeCount(*list);

	for (int i = 0; i < count; i++) {
		Node *currNode = sllGetNodeAt(*list, i);
		if (currNode != NULL) {
			sllRemoveNode(list, currNode);
			sllDestroyNode(currNode);
		}
	}
}

/* 노드 추가 */
// * 대신 ** 사용하는 이유 : 포인터가 가진 값이 아닌, 포인터 자신의 주소를 넘겨야함
void sllAppendNode(Node **head, Node *newNode) {
	if ((*head) == NULL) {
		*head = newNode;
	} else {
		Node *tail = (*head);
		while (tail->nextNode != NULL) {
			tail = tail->nextNode;
		}
		tail->nextNode = newNode;
	}
}

/* 노드 제거 */
// * 대신 ** 사용하는 이유 : 포인터가 가진 값이 아닌, 포인터 자신의 주소를 넘겨야함
void sllRemoveNode(Node **head, Node *removeNode) {
	if ((*head) == removeNode) {
		*head = removeNode->nextNode;
	} else {
		Node *currNode = (*head);
		while ((currNode != NULL) && (currNode->nextNode != removeNode)) {
			currNode = currNode->nextNode;
		}
		if (currNode != NULL) {
			currNode->nextNode = removeNode->nextNode;
		}
	}
}

/* 노드 삽입 */
void sllInsertAfter(Node *currNode, Node *newNode) {
	newNode->nextNode = currNode->nextNode;
	currNode->nextNode = newNode;
}

void sllInsertBefore(Node **head, Node *currNode, Node *newNode) {
	if (*head == currNode) {
		newNode->nextNode = currNode;
		(*head) = newNode;
	} else {
		Node *tempNode = (*head);
		while ((tempNode != NULL) && (tempNode->nextNode != currNode)) {
			tempNode = tempNode->nextNode;
		}
		tempNode->nextNode = newNode;
		newNode->nextNode = currNode;
	}
}

/* 헤드 삽입 */
void sllInsertHead(Node **currHead, Node *newHead) {
	if (*currHead == NULL) {
		(*currHead) = newHead;
	} else {
		newHead->nextNode = (*currHead);
		(*currHead) = newHead;
	}
}

/* 노드 탐색 */
Node *sllGetNodeAt(Node *head, int index) {
	Node *currNode = head;

	while ((currNode != NULL) && (index > 0)) {
		currNode = currNode->nextNode;
		index--;
	}

	return currNode;
}

/* 노드 갯수 세기 */
int sllGetNodeCount(Node *head) {
	int count = 0;
	Node *currNode = head;

	while (currNode != NULL) {
		currNode = currNode->nextNode;
		count++;
	}
	return count;
}

Node *seqeunceSearch(Node *head, int target) {
	Node *curr = head;
	Node *match = NULL;

	while (curr != NULL) {
		if (curr->data == target) {
			match = curr;
			break;
		} else {
			curr = curr->nextNode;
		}
	}

	return match;
}

Node *seqeunceMoveToFront(Node **head, int target) {
	Node *curr = (*head);
	Node *prev = NULL;
	Node *match = NULL;

	while (curr != NULL) {
		if (curr->data == target) {
			match = curr;
			if (prev != NULL) {
				prev->nextNode = curr->nextNode;
				curr->nextNode = (*head);
				(*head) = curr;
			}
			break;
		} else {
			prev = curr;
			curr = curr->nextNode;
		}
	}
	return match;
}

Node *seqeunceTranspose(Node **head, int target) {
	Node *curr = (*head);
	Node *pprev = NULL;
	Node *prev = NULL;
	Node *match = NULL;

	while (curr != NULL) {
		if (curr->data == target) {
			match = curr;
			if (prev != NULL) {
				if (pprev != NULL) {
					pprev->nextNode = curr;
				} else {
					(*head) = curr;
				}
				prev->nextNode = curr->nextNode;
				curr->nextNode = prev;
			}
			break;
		} else {
			if (prev != NULL) {
				pprev = prev;
			}
			prev = curr;
			curr = curr->nextNode;
		}
	}
	return match;
}

int main() {
	Node *list = NULL;
	Node *newNode = NULL;
	Node *currNode = NULL;

	// 노드 5개 추가
	for (int i = 0; i < 10; i++) {
		newNode = sllCreateNode(i);
		sllAppendNode(&list, newNode);
	}

	// 리스트 출력
	for (int i = 0; i < sllGetNodeCount(list); i++) {
		printf("[%d] %d\n", i, sllGetNodeAt(list, i)->data);
	}

	currNode = seqeunceSearch(list, 5);

	printf("%d\n", currNode->data);

	// 전진 이동법
	currNode = seqeunceMoveToFront(&list, 5);

	// 리스트 출력
	for (int i = 0; i < sllGetNodeCount(list); i++) {
		printf("[%d] %d\n", i, sllGetNodeAt(list, i)->data);
	}

	currNode = seqeunceTranspose(&list, 3);

	// 리스트 출력
	for (int i = 0; i < sllGetNodeCount(list); i++) {
		printf("[%d] %d\n", i, sllGetNodeAt(list, i)->data);
	}

	return 0;
}