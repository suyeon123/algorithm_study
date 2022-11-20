#include <stdlib.h>
#include <string.h>
#include<stdio.h>

typedef char* KeyType;
typedef char* ValueType;

enum ElementStatus {
	EMPTY = 0,
	OCCUPIED = 1
};

typedef struct myElementType {
	KeyType key;
	ValueType value;

	enum ElementStatus status;
} ElementType;

typedef struct myHashTable {
	int occupiedCount;
	int tableSize;

	ElementType *table;
} HashTable;

HashTable *createHashTable(int tableSize);
void destroyHashTable(HashTable *ht);
void clearElement(ElementType *element);

void setHash(HashTable **ht, KeyType key, ValueType value);
ValueType getHash(HashTable *ht, KeyType key);
int hash(KeyType key, int keyLen, int tableSize);
int hash2(KeyType key, int keyLen, int tableSize);

void rehash(HashTable **ht);

HashTable *createHashTable(int tableSize) {
	HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
	ht->table = (ElementType *)malloc(sizeof(ElementType) * tableSize);

	memset(ht->table, 0, sizeof(ElementType) * tableSize);

	ht->tableSize = tableSize;
	ht->occupiedCount = 0;

	return ht;
}

void destroyHashTable(HashTable *ht) {
	for (int i = 0; i < ht->tableSize; i++) {
		clearElement(&(ht->table[i]));
	}
	free(ht->table);
	free(ht);
}

void clearElement(ElementType *element) {
	if (element->status == EMPTY) {
		return;
	}
	free(element->key);
	free(element->value);
}

void setHash(HashTable **ht, KeyType key, ValueType value) {
	int keyLen, address, stepSize;
	double usage;

	usage = (double)(*ht)->occupiedCount/(*ht)->tableSize;

	if (usage > 0.5) {
		rehash(ht);
	}

	keyLen = strlen(key);
	address = hash(key, keyLen, (*ht)->tableSize);
	stepSize = hash2(key, keyLen, (*ht)->tableSize);

	while ((*ht)->table[address].status != EMPTY &&
		strcmp((*ht)->table[address].key, key) != 0) {
		printf("충돌 발생 : key:%s, address:%d, stepSize:%d\n", key, address, stepSize);
		address = (address + stepSize) % (*ht)->tableSize;
	}

	(*ht)->table[address].key = (char *)malloc(sizeof(char) * (keyLen + 1));
	strcpy((*ht)->table[address].key, key);

	(*ht)->table[address].value = (char *)malloc(sizeof(char) * (strlen(value) + 1));
	strcpy((*ht)->table[address].value, value);

	(*ht)->table[address].status = OCCUPIED;

	(*ht)->occupiedCount++;

	printf("key(%s) entered at address(%d)\n", key, address);
}

ValueType getHash(HashTable *ht, KeyType key) {
	int keyLen = strlen(key);
	int address = hash(key, keyLen, ht->tableSize);
	int stepSize = hash2(key, keyLen, ht->tableSize);

	while (ht->table[address].status != EMPTY &&
			strcmp(ht->table[address].key, key) != 0) {
		address = (address + stepSize) % ht->tableSize;
	}

	return ht->table[address].value;
}

int hash(KeyType key, int keyLen, int tableSize) {
	int hashValue = 0;

	for (int i = 0; i < keyLen; i++) {
		hashValue = (hashValue << 3) + key[i];
	}
	hashValue = hashValue % tableSize;

	return hashValue;
}

int hash2(KeyType key, int keyLen, int tableSize) {
	int hashValue = 0;

	for (int i = 0; i < keyLen; i++) {
		hashValue = (hashValue << 2) + key[i];
	}

	hashValue = hashValue % (tableSize - 3);

	return hashValue + 1;
}

void rehash(HashTable **ht) {
	ElementType *oldTable = (*ht)->table;

	HashTable *newTable = createHashTable((*ht)->tableSize * 2);

	for (int i = 0; i < (*ht)->tableSize; i++) {
		if (oldTable[i].status == OCCUPIED) {
			setHash(&newTable, oldTable[i].key, oldTable[i].value);
		}
	}

	for (int i = 0; i < (*ht)->tableSize; i++) {
		clearElement(&(oldTable[i]));
	}
	free(oldTable);

	(*ht) = newTable;
}

int main() {
	HashTable *ht = createHashTable(11);

	setHash(&ht, (char *)"MSFT", (char *)"Microsoft Corporation");
	setHash(&ht, (char *)"JAVA", (char *)"Sun Microsystems");
	setHash(&ht, (char *)"REDH", (char *)"Red Hat Linux");
	setHash(&ht, (char *)"APAC", (char *)"Apache Org");
	setHash(&ht, (char *)"ZYMZZ", (char *)"Unisys Ops Check");
	setHash(&ht, (char *)"IBM", (char *)"IBM Ltd");


	printf("key:%s, value:%s\n", (char *)"MSFT", getHash(ht, (char *)"MSFT"));
	printf("key:%s, value:%s\n", (char *)"JAVA", getHash(ht, (char *)"JAVA"));
	printf("key:%s, value:%s\n", (char *)"REDH", getHash(ht, (char *)"REDH"));
	printf("key:%s, value:%s\n", (char *)"APAC", getHash(ht, (char *)"APAC"));
	printf("key:%s, value:%s\n", (char *)"ZYMZZ", getHash(ht, (char *)"ZYMZZ"));
	printf("key:%s, value:%s\n", (char *)"IBM", getHash(ht, (char *)"IBM"));

	destroyHashTable(ht);

	return 0;
}