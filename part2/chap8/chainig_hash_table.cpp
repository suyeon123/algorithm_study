#include <stdlib.h>
#include <string.h>
#include<stdio.h>

typedef struct myNode {
	char *key;
	char *value;

	struct myNode *next;
} Node;

typedef Node* List;

typedef struct myHashTable {
	int tableSize;
	List *table;
} HashTable;

HashTable *createHashTable(int tableSize);
void destroyHashTable(HashTable *ht);
Node *createNode(char *key, char* value);
void destroyNode(Node *node);
void destroyList(List list);
void setHash(HashTable *ht, char *key, char *value);
char *getHash(HashTable *ht, char *key);
int hash(char *key, int keyLen, int tableSize);

HashTable *createHashTable(int tableSize) {
	HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
	ht->table = (List *)malloc(sizeof(Node) * tableSize);

	memset(ht->table, 0, sizeof(List) * tableSize);

	ht->tableSize = tableSize;

	return ht;
}

void destroyHashTable(HashTable *ht) {
	for (int i = 0; i < ht->tableSize; i++) {
		List list = ht->table[i];
		destroyList(list);
	}
	if (ht->table) {
		free(ht->table);
	}
	if (ht) {
		free(ht);
	}
}

Node *createNode(char *key, char* value) {
	Node *newNode = (Node *)malloc(sizeof(Node));

	newNode->key = (char *)malloc(sizeof(char) * (strlen(key) + 1));
	strcpy(newNode->key, key);

	newNode->value = (char *)malloc(sizeof(char) * (strlen(value) + 1));
	strcpy(newNode->value, value);

	newNode->next = NULL;

	return newNode;
}

void destroyNode(Node *node) {
	free(node->key);
	free(node->value);
	free(node);
}

void destroyList(List list) {
	if (list = NULL) {
		return;
	}
	if (list->next != NULL) {
		destroyList(list->next);
	}
	destroyNode(list);
}

void setHash(HashTable *ht, char *key, char *value) {
	int address = hash(key, strlen(key), ht->tableSize);
	Node *newNode = createNode(key, value);

	if (ht->table[address] == NULL) {
		ht->table[address] = newNode;
	} else {
		List list = ht->table[address];
		newNode->next = list;
		ht->table[address] = newNode;
		printf("충돌 발생 : key(%s), address(%d)\n", key, address);
	}
}

char *getHash(HashTable *ht, char *key) {
	int address = hash(key, strlen(key), ht->tableSize);

	List list = ht->table[address];
	List target = NULL;

	if (list == NULL) {
		return NULL;
	}

	while (1) {
		if (strcmp(list->key, key) == 0) {
			target = list;
			break;
		}
		if (list->next == NULL) {
			break;
		} else {
			list = list->next;
		}
	}

	return target->value;
}

int hash(char *key, int keyLen, int tableSize) {
	int hashValue = 0;

	for (int i = 0; i < keyLen; i++) {
		hashValue = (hashValue << 3) + key[i];
	}

	hashValue = hashValue % tableSize;

	return hashValue;
}

int main() {
	HashTable *ht = createHashTable(12289);

	setHash(ht, (char *)"MSFT", (char *)"Microsoft Corporation");
	setHash(ht, (char *)"JAVA", (char *)"Sun Microsystems");
	setHash(ht, (char *)"REDH", (char *)"Red Hat Linux");
	setHash(ht, (char *)"APAC", (char *)"Apache Org");
	setHash(ht, (char *)"ZYMZZ", (char *)"Unisys Ops Check");
	setHash(ht, (char *)"IBM", (char *)"IBM Ltd");


	printf("key:%s, value:%s\n", (char *)"MSFT", getHash(ht, (char *)"MSFT"));
	printf("key:%s, value:%s\n", (char *)"JAVA", getHash(ht, (char *)"JAVA"));
	printf("key:%s, value:%s\n", (char *)"REDH", getHash(ht, (char *)"REDH"));
	printf("key:%s, value:%s\n", (char *)"APAC", getHash(ht, (char *)"APAC"));
	printf("key:%s, value:%s\n", (char *)"ZYMZZ", getHash(ht, (char *)"ZYMZZ"));
	printf("key:%s, value:%s\n", (char *)"IBM", getHash(ht, (char *)"IBM"));

	destroyHashTable(ht);

	return 0;
}