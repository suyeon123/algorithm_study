#include<stdio.h>

void swap(int *a, int *b);

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int partition(int dataSet[], int left, int right) {
	int first = left;
	int pivot = dataSet[first];

	++left;

	while (left <= right) {
		while (dataSet[left] <= pivot) {
			++left;
		}
		while (dataSet[right] > pivot) {
			--right;
		}

		if (left < right) {
			swap(&dataSet[left], &dataSet[right]);
		} else {
			break;
		}
	}

	swap(&dataSet[first], &dataSet[right]);
	return right;
}

void quickSort(int dataSet[], int left, int right) {
	if (left < right) {
		int index = partition(dataSet, left, right);
		quickSort(dataSet, left, index - 1);
		quickSort(dataSet, index + 1, right);
	}
}

int main(void)
{
	/* code */
	int dataSet[] = {6, 4, 2, 3, 1, 5};
	int dataSet2[] = {1, 2, 3, 4, 5, 6};
	//sizeof(배열) = 배열크기 * 배열 요소 사이즈
	int len = sizeof(dataSet) / sizeof(dataSet[0]);

	quickSort(dataSet, 0, len - 1);

	for (int i = 0; i < len; i++) {
		printf("%d\n", dataSet[i]);
	}

	quickSort(dataSet2, 0, len - 1);

	for (int i = 0; i < len; i++) {
		printf("%d\n", dataSet2[i]);
	}
	return 0;
}
