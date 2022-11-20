#include <stdlib.h>
#include <memory.h>
#include<stdio.h>

typedef struct myJewel {
	int weight;
	int value;
	int seled;
} jewelInfo;

typedef struct myBag {
	int maxWeight;
	jewelInfo jewel;
} bagList;

int compare(const void *_elem1, const void *_elem2) {
	jewelInfo *elem1 = (jewelInfo *)_elem1;
	jewelInfo *elem2 = (jewelInfo *)_elem2;

	if (elem1->value < elem2->value) {
		return 1;
	} else if (elem1->value > elem2->value) {
		return -1;
	} else {
		return 0;
	}
}

int exam1(void)
{
	int n = 2; //보석 갯수
	int k = 1; //가방 갯수
	int currBagId = 0;

	jewelInfo jewels[n] = {
		{5, 10, 0},
		{100, 100, 0},
	};

	bagList bags[k] = {
		{11, {0,}}
	};

	int len = sizeof(jewels) / sizeof(jewels[0]);
	qsort((void *)jewels, len, sizeof(jewelInfo), compare);

	while (currBagId < k) {
		for (int i = 0; i < n; i++) {
			if ((jewels[i].seled != 1) && (jewels[i].weight <= bags[currBagId].maxWeight)) {
				jewels[i].seled = 1;
				bags[currBagId].jewel = jewels[i]; 
				currBagId++;
				break;
			}
		}
	}

	int totalValue = 0;

	for (int i = 0; i < k; i++) {
		printf("가방[%d] - jewel weight:%d, value:%d\n", i, bags[i].jewel.weight, bags[i].jewel.value);
		totalValue += bags[i].jewel.value;
	}
	printf("%d\n", totalValue);

	return 0;
}

int exam2(void)
{
	int n = 3; //보석 갯수
	int k = 2; //가방 갯수
	int currBagId = 0;

	jewelInfo jewels[n] = {
		{1, 65, 0},
		{5, 23, 0},
		{2, 99, 0}
	};

	bagList bags[k] = {
		{10, {0,}},
		{2, {0,}}
	};

	int len = sizeof(jewels) / sizeof(jewels[0]);
	qsort((void *)jewels, len, sizeof(jewelInfo), compare);

	while (currBagId < k) {
		for (int i = 0; i < n; i++) {
			if ((jewels[i].seled != 1) && (jewels[i].weight <= bags[currBagId].maxWeight)) {
				jewels[i].seled = 1;
				bags[currBagId].jewel = jewels[i]; 
				currBagId++;
				break;
			}
		}
	}

	int totalValue = 0;

	for (int i = 0; i < k; i++) {
		printf("가방[%d] - jewel weight:%d, value:%d\n", i, bags[i].jewel.weight, bags[i].jewel.value);
		totalValue += bags[i].jewel.value;
	}
	printf("%d\n", totalValue);

	return 0;
}

int main() {
	exam1();
	exam2();
	return 0;
}