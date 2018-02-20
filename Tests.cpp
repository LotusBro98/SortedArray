#include "sorted_array.h"

#include <stdio.h>

int cmp_char(void* a, void* b)
{
	return *(char*)a - *(char*)b;
}

int main()
{
	struct sorted_array* arr = sacreate(1, 100, cmp_char);

	char a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	char b[10] = {3, 6, 2, 1, 8, 7, 9, 0, 4, 5};
//	char c[10] = {1, 2, 3, 2, 1, 3, 2, 2, 1, 1};
	char victim = 3;



	for (int i = 0; i < 10; i++)
		saput(arr, a + i);

	for (int i = 0; i < 10; i++)
		saput(arr, b + i);

//	for (int i = 0; i < 10; i++)
//		saput(arr, c + i);

	for (struct sa_iter* it = sainew(arr); !saiend(it); sainext(it))
		printf("%hhu ", *(char*)saiget(it));
	printf("\n");

	for (int i = 0; i < 3; i++)
		sarm(arr, 0);

	sarmall(arr, &victim);
	victim = 11;
	sarmall(arr, &victim);

	for (struct sa_iter* it = sainew(arr); !saiend(it); sainext(it))
		printf("%hhu ", *(char*)saiget(it));
	printf("\n");

	return 0;
}
