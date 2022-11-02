#include <cstdio>
#include <cstdlib>
#include<stdio.h>

/* c언어 메모리 영역 */
/* 1. 정적 메모리(Static Memory) - 전역/정적변수 저장
   - 프로그램이 실행하면서 할당되며 프로그램이 종료될 때 해제되는 영역
   2. 자동 메모리(Automatic Memory) - 지역변수 저정
   - 코드 블럭이 종료됨에 따라 사라지는 영역
   3. 자유 저장소(Free Store)
    - 프로그래머가 직접 관리하는 메모리 영역 (malloc/free 이용)
*/

/* 링크드 리스트 장단점 */
/* 장점 - 노드의 추가/삽입/삭제가 빠름
   단점 - 특정 위치의 노드를 찾는 연산이 느림 */

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

int main() {
	Node *list = NULL;
	Node *newNode = NULL;
	Node *currNode = NULL;

	// 노드 5개 추가
	for (int i = 0; i < 5; i++) {
		newNode = sllCreateNode(i);
		sllAppendNode(&list, newNode);
	}

	// head에 노드 추가
	newNode = sllCreateNode(-1);
	sllInsertHead(&list, newNode);

	// 세번째 노드 뒤에 노드 추가
	newNode = sllCreateNode(3000);
	currNode = sllGetNodeAt(list, 2);
	sllInsertAfter(currNode, newNode);

	// 리스트 출력
	for (int i = 0; i < sllGetNodeCount(list); i++) {
		printf("[%d] %d\n", i, sllGetNodeAt(list, i)->data);
	}

	sllDestroyAll(&list);

	// 모든 노드 제거
	for (int i = 0; i < sllGetNodeCount(list); i++) {
		currNode = sllGetNodeAt(list, i);
		if (currNode) {
			sllRemoveNode(&list, currNode);
			sllDestroyNode(currNode);
		}
	}

	for (int i = 0; i < sllGetNodeCount(list); i++) {
		printf("[%d] %d\n", i, sllGetNodeAt(list, i)->data);
	}

	return 0;
}