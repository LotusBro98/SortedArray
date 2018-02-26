#include "sorted_array.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp_char(const void* a, const void* b)
{
	return *(char*)a - *(char*)b;
}

void printArr(struct sorted_array* arr)
{
	for (struct sa_iter* it = sainew(arr); !saiend(it); sainext(it))
		printf("%hhu ", *(char*)saiget(it));
	printf("\n");
}

int main()
{
	// Test 1. putting and getting

	char a[20] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 3, 6, 2, 1, 8, 7, 9, 0, 4, 5};
	char b[20] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 9, 8, 9, 9};

	struct sorted_array* arr = sacreate(1, 100, cmp_char);

	for (int i = 0; i < 20; i++)
	{
		saput(arr, a + i);
		printf("[ + %hhu]: ", a[i]);
		printArr(arr);
	}

	int good = true;
	for (int i = 0; i < 20; i++)
		if (b[i] != *(char*)saget(arr, i))
		{
			good = false;
			break;
		}

	if (good)
	{
		printf("\033[1m\033[32mTest 1 passed.\033[0m\n");
		sadelete(arr);
	}
	else
	{
		printf("\033[1m\033[31mTest 1 failed.\033[0m\n");
		sadelete(arr);
		exit(EXIT_FAILURE);
	}

	return 0;
}
