#include <cstdio>
#include <cstring>
#include <stdlib.h> 
#include<stdio.h>
#include "Score.h"

Score *binarySearch(Score scoreList[], int size, double target);
int compareScore(const void *elem1, const void *elem2);

Score *binarySearch(Score scoreList[], int size, double target) {
	int left, right, mid;

	left = 0;
	right = size - 1;

	while (left <= right) {
		mid = (left + right) / 2;
		if (target == scoreList[mid].score) {
			return &(scoreList[mid]);
		} else if (target > scoreList[mid].score) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}
	return NULL;
}

int compareScore(const void *_elem1, const void *_elem2) {
	Score *elem1 = (Score *)_elem1;
	Score *elem2 = (Score *)_elem2;

	if (elem1->score > elem2->score) {
		return 1;
	} else if (elem1->score < elem2->score) {
		return -1;
	} else {
		return 0;
	}
}

int main() {
	int len = sizeof DataSet / sizeof DataSet[0];
	int i = 0;
	Score *found = NULL;
	Score target;

	qsort((void *)DataSet, len, sizeof(Score), compareScore);

	found = binarySearch(DataSet, len, 671.78);

	printf("found num: %d score: %f\n", found->number, found->score);

	target.number = 0;
	target.score = 934.54;

	found = (Score *)bsearch((void*)&target, (void*)DataSet, len, sizeof (Score), compareScore);

	printf("found num: %d score: %f\n", found->number, found->score);

	return 0;
}