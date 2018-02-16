#include <stdlib.h>

struct sorted_array
{
	void* buffer;
	size_t elem_size;
	size_t max_elems;

	int (*compar)(void* a, void* b);

	size_t n;
};

struct sorted_array* sacreate(size_t elem_size, size_t max_elems, int (*compar)(void* a, void* b))
{
	struct sorted_array* array = (struct sorted_array*) malloc(sizeof(struct sorted_array));
	if (array == NULL)
		return NULL;

	array->buffer = malloc(elem_size * max_elems);
	if (array->buffer == NULL)
	{
		free(array);
		return NULL;
	}

	array->max_elems = max_elems;
	array->elem_size = elem_size;
	array->compar = compar;

	array->n = 0;

	return array;
}

void sadelete(struct sorted_array* array)
{
	free(array->buffer);
	free(array);
}

