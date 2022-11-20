#include <stdlib.h>
#include <memory.h>
#include<stdio.h>

typedef struct myNode {
	int key;
	int value;
} Node;

typedef struct myHashTable {
	int tableSize;
	Node *table;
} HashTable;

HashTable *createHashTable(int tableSize);
void setHash(HashTable *ht, int key, int value);
int getHash(HashTable *ht, int key);
void destroyHashTable(HashTable *ht);
int hash(int key, int tableSize);

HashTable *createHashTable(int tableSize) {
	HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
	ht->table = (Node *)malloc(sizeof(Node) * tableSize);
	ht->tableSize = tableSize;

	return ht;
}

void setHash(HashTable *ht, int key, int value) {
	int address = hash(key, ht->tableSize);

	ht->table[address].key = key;
	ht->table[address].value = value;
}

int getHash(HashTable *ht, int key) {
	int address = hash(key, ht->tableSize);

	if (ht->table[address].value == key) {
		return 1;
	} else {
		return 0;
	}

	return ht->table[address].value;
}

void destroyHashTable(HashTable *ht) {
	if (ht->table) {
		free(ht->table);
	}
	if (ht) {
		free(ht);
	}
}

int hash(int key, int tableSize) {
	return key % tableSize;
}

int main() {
	HashTable *ht = createHashTable(11);
	int push[5] = {4, 1, 5, 2, 3};
	int test[5] = {1, 3, 7, 9, 5};

	for (int i = 0; i < 5; i++) {
		setHash(ht, push[i], push[i]);
	}

	for (int i = 0; i < 5; i++) {
		printf("%d\n", getHash(ht, test[i]));
	}

	destroyHashTable(ht);

	return 0;
}