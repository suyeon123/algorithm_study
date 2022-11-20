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
	ht->table = (Node *)malloc(sizeof(Node));
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
	HashTable *ht = createHashTable(193);

	setHash(ht, 418, 32114);
	setHash(ht, 9, 514);
	setHash(ht, 27, 8917);
	setHash(ht, 1031, 286);

	printf("key:%d, value:%d\n", 418, getHash(ht, 418));
	printf("key:%d, value:%d\n", 9, getHash(ht, 9));
	printf("key:%d, value:%d\n", 27, getHash(ht, 27));
	printf("key:%d, value:%d\n", 1031, getHash(ht, 1031));

	destroyHashTable(ht);

	return 0;
}