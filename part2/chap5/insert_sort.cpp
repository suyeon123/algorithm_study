#include<stdio.h>
#include <string.h>

void insertSort(int dataSet[], int len) {
	int i = 0;
	int j = 0;
	int value = 0;

	for (i = 1; i < len; i++) {
		if (dataSet[i - 1] <= dataSet[i]) {
			continue;
		}
		value = dataSet[i];
		for (j = 0; j < i; j++) {
			if (dataSet[j] > value) {
				memmove(&dataSet[j+1], &dataSet[j], sizeof(dataSet[0]) * (i-j));
				dataSet[j] = value;
				break;
			}
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

	insertSort(dataSet, len);

	for (int i = 0; i < len; i++) {
		printf("%d\n", dataSet[i]);
	}

	insertSort(dataSet2, len);

	for (int i = 0; i < len; i++) {
		printf("%d\n", dataSet2[i]);
	}
	return 0;
}