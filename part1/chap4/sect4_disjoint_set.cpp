#include <cstdio>
#include <cstdlib>
#include <cstring>
#include<stdio.h>

typedef struct myNode {
	struct myNode *parent;

	void *data;
} disJointSet;


void unionSet(disJointSet *set1, disJointSet *set2);
disJointSet *findSet(disJointSet *set);
disJointSet *makeSet(void *newData);
void destroySet(disJointSet *set);

void unionSet(disJointSet *set1, disJointSet *set2) {
	set2 = findSet(set2);
	set2->parent = set1;
}

disJointSet *findSet(disJointSet *set) {
	while (set->parent != NULL) {
		set = set->parent;
	}
	return set;
}

disJointSet *makeSet(void *newData) {
	disJointSet *newNode = (disJointSet *)malloc(sizeof(disJointSet));
	newNode->data = newData;
	newNode->parent = NULL;

	return newNode;
}

void destroySet(disJointSet *set) {
	if (set) {
		free(set);
	}
}

int main() {
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;

	disJointSet *set1 = makeSet(&a);
	disJointSet *set2 = makeSet(&b);
	disJointSet *set3 = makeSet(&c);
	disJointSet *set4 = makeSet(&d);

	unionSet(set1, set2);
	unionSet(set3, set4);

	printf("set1 == set3 :%d \n", findSet(set1) == findSet(set3));
	printf("set2 == set4 :%d \n", findSet(set2) == findSet(set4));

	unionSet(set2, set4);

	printf("set1 == set3 :%d \n", findSet(set1) == findSet(set3));
	printf("set2 == set4 :%d \n", findSet(set2) == findSet(set4));

	return 0;
}