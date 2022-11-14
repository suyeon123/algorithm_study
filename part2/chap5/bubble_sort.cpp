#include <cstdio>
#include <cstdlib>
#include<stdio.h>

void bubbleSort(int dataSet[], int len) {
	int i = 0;
	int j = 0;
	int temp = 0;

	for (i = 0; i < len; i++) {
		int changeCount = 0;
		for (j = 0; j < len-(i+1); j++) {
			if (dataSet[j] > dataSet[j+1]) {
				temp = dataSet[j+1];
				dataSet[j+1] = dataSet[j];
				dataSet[j] = temp;
				changeCount++;
			}
		}
		if (changeCount == 0) {
			printf("already sorted\n");
			return;
		}
	}
}

int main(void)
{
	/* code */
	int dataSet[] = {6, 4, 2, 3, 1, 5};
	int dataSet2[] = {1, 2, 3, 4, 5, 6};
	//sizeof(배열) = 배열크기 * 배열 요소 사이즈
	int len = sizeof(dataSet) / sizeof(dataSet[0]);

	bubbleSort(dataSet, len);

	for (int i = 0; i < len; i++) {
		printf("%d\n", dataSet[i]);
	}

	bubbleSort(dataSet2, len);

	for (int i = 0; i < len; i++) {
		printf("%d\n", dataSet2[i]);
	}
	return 0;
}