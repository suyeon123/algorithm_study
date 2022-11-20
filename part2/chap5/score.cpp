#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "score.h"

int compare(const void *_elem1, const void *_elem2) {
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

int main(void)
{
	int len = sizeof(DataSet) / sizeof(DataSet[0]);
	qsort((void *)DataSet, len, sizeof(Score), compare);
	printf("number:%d, score: %f\n", DataSet[17213].number, DataSet[17213].score);
	return 0;
}
