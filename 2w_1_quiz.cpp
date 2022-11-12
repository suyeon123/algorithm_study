#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include<stdio.h>

int sortString(const void *_elem1, const void *_elem2);

int sortString(const void *_elem1, const void *_elem2) {
    const char** str1 = (const char**)_elem1;
    const char**str2 = (const char**)_elem2;

    if (strlen(*str1) > strlen(*str2)) {
    	return 1;
    } else if (strlen(*str1) < strlen(*str2)) {
    	return -1;
    } else{
    	return (strcmp(*str1, *str2));
    }
}

int main() {
	const char *dataSet[] = {"13", "but", "i", "wont", "hesitate"
					        ,"no", "more", "no", "more", "it", "cannot"
					        , "wait", "im", "yours"};
	int len = sizeof dataSet / sizeof dataSet[0];
	int i = 0;

	printf(" Before Sort ... \n");
	for (i = 0; i < len; i++) {
		printf("%s ", dataSet[i]);
	}
	printf("\n");

	qsort((void *)dataSet, len, sizeof(const char *), sortString);

    printf(" After Sort ... \n");
	for (i = 0; i < len; i++) {
		printf("%s ", dataSet[i]);
	}
	printf("\n");

	return 0;
}