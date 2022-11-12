#include <cstdio>
#include <cstring>
#include <stdlib.h> 
#include<stdio.h>

int findMax(int treeDataSet[], int size);
int searchCurMax(int treeDataSet[], int treeNum, int need);

int findMax(int treeDataSet[], int size) {
	int max = 0;
	for (int i = 0; i < size; i++) {
        if (max < treeDataSet[i]) {
            max = treeDataSet[i];
        }
    }
    return max;
}

int searchCurMax(int treeDataSet[], int treeNum, int need) {
	int min, max, mid;
	int cutSum;
	int cutMaxHeight = 0;

	min = 1;
	max = findMax(treeDataSet, treeNum);

    while (min <= max) {
    	cutSum = 0;
        mid = (min + max) / 2;
        for (int i = 0; i < treeNum; i++) {
            if ((treeDataSet[i] - mid) > 0) {
                cutSum = cutSum + (treeDataSet[i] - mid);
            }
        }

        printf("cut height:%d, cut Sum:%d\n", mid, cutSum);

        if (cutSum < need) {
            max = mid - 1;
        } else if (cutSum == need) {
        	cutMaxHeight = mid;
        	return cutMaxHeight;
        } else {
            if (cutMaxHeight < mid) {
                cutMaxHeight = mid;
            }

            min = mid + 1;
        }
    }
	return cutMaxHeight;
}

int main()
{
    int n = 4, m = 7;
    int treeDataSet[] = {20, 15, 10, 17};
    int maxCurTreeHeight = 0;
    int n2 = 5, m2 = 20;
    int treeDataSet2[] = {4, 42, 40, 26, 46};

    printf("[예제 1]\n");
    printf("N:%d, M:%d\n", n, m);
    for (int i = 0; i < n; i++) {
    	printf("%d ", treeDataSet[i]);
    }
    printf("\n");
    maxCurTreeHeight = searchCurMax(treeDataSet, n, m);

    printf("절단기 최대 높이:%d\n", maxCurTreeHeight);

    printf("[예제 2]\n");
    printf("N:%d, M:%d\n", n2, m2);
    for (int i = 0; i < n2; i++) {
    	printf("%d ", treeDataSet2[i]);
    }
    printf("\n");
    maxCurTreeHeight = searchCurMax(treeDataSet2, n2, m2);

    printf("절단기 최대 높이:%d\n", maxCurTreeHeight);

    return 0;
}