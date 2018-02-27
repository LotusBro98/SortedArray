#include "SortedArray.hpp"

#include <iostream>
#include <stdio.h>

int cmp_int(const void* a, const void* b)
{
	return *(int*)a - *(int*)b;
}

void testMsg(int testNumber, bool success)
{
	if (success)
	{
		printf("\033[1m\033[32mTest %d passed.\033[0m\n", testNumber);
	}
	else
	{
		printf("\033[1m\033[31mTest %d failed.\033[0m\n", testNumber);
		exit(EXIT_FAILURE);
	}

}

int main()
{
	int A[20] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 3, 6, 2, 1, 8, 7, 9, 0, 4, 5};
	int B[20] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9};
	
	SortedArray<int> sa(20, cmp_int);
	
	// Test 1. putting and getting
	for (int a : A)
		sa.put(a);

	testMsg(1, sa == B);
	
	return 0;
}
