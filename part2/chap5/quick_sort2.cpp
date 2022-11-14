#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *_elem1, const void *_elem2) {
	int *elem1 = (int *)_elem1;
	int *elem2 = (int *)_elem2;

	if (*elem1 > *elem2) {
		return 1;
	} else if (*elem1 < *elem2) {
		return -1;
	} else {
		return 0;
	}
}

int main(void)
{
	/* code */
	int dataSet[] = {6, 4, 2, 3, 1, 5};
	int dataSet2[] = {1, 2, 3, 4, 5, 6};
	//sizeof(배열) = 배열크기 * 배열 요소 사이즈
	int len = sizeof(dataSet) / sizeof(dataSet[0]);

	qsort((void *)dataSet, len, sizeof(int), compare);

	for (int i = 0; i < len; i++) {
		printf("%d\n", dataSet[i]);
	}

	qsort((void *)dataSet2.score, len, sizeof(int), compare);

	for (int i = 0; i < len; i++) {
		printf("%d\n", dataSet2[i]);
	}
	return 0;
}
