#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct sorted_array
{
	void* buffer;
	size_t elem_size;
	size_t max_elems;

	int (*compar)(void* a, void* b);

	size_t n;
};

struct sa_iter
{
	struct sorted_array* array;
	size_t i;
};




// ===============================  Supplementary funcs  ==================================

inline void* getElem(struct sorted_array* array, size_t index)
{
	return (char*)array->buffer + index * array->elem_size;
}

inline int cmp(struct sorted_array* array, size_t a_index, size_t b_index)
{
	return array->compar(getElem(array, a_index), getElem(array, b_index));
}

inline int cmp(struct sorted_array* array, size_t index, void* elem)
{
	return array->compar(getElem(array, index), elem);
}

void insert8(struct sorted_array* array, size_t index, void* elem)
{
	for (size_t i = array->n; i > index; i--)
		*(int8_t*)getElem(array, i) = *(int8_t*)getElem(array, i - 1);
	*(int8_t*)getElem(array, index) = *(int8_t*)elem;
	array->n++;
}

void remove8(struct sorted_array* array, size_t index)
{
	for (size_t i = index; i < (array->n - 1); i++)
		*(int8_t*)getElem(array, i) = *(int8_t*)getElem(array, i + 1);
	array->n--;
}

void insert(struct sorted_array* array, size_t index, void* elem)
{
	switch (array->elem_size)
	{
		case 1:
			insert8(array, index, elem);
			break;
		default:
			for (size_t i = array->n; i > index; i--)
				memcpy(getElem(array, i), getElem(array, i - 1), array->elem_size);
			memcpy(getElem(array, index), elem, array->elem_size);
			break;
	}
}

void remove(struct sorted_array* array, size_t index)
{
	switch (array->elem_size)
	{
		case 1:
			remove8(array, index);
			break;
		default:
			for (size_t i = index; i < (array->n - 1); i++)
				memcpy(getElem(array, i), getElem(array, i + 1), array->elem_size);
			array->n--;
			break;
	}
}

/// Find the first element that is greater than given or any element that is equal to given in a sorted array.
size_t findPlace(struct sorted_array* array, void* elem)
{
	if (array->n == 0)
		return 0;
	if (cmp(array, 0, elem) >= 0)
		return 0;
	if (cmp(array, array->n - 1, elem) <= 0)
		return array->n;


	size_t left = 0;
	size_t right = array->n - 1;
	size_t center;
	while (left + 1 < right)
	{
		center = (left + right) / 2;
		int sign = cmp(array, center, elem);
		if (sign == 0)
			return center;
		if (sign < 0)
			left = center;
		else
			right = center;
	}
	return right;
}

/// Find the first element >= @p elem
size_t findPlaceLeft(struct sorted_array* array, void* elem)
{
	if (array->n == 0)
		return 0;
	if (cmp(array, 0, elem) >= 0)
		return 0;
	if (cmp(array, array->n - 1, elem) < 0)
		return array->n;


	size_t left = 0;
	size_t right = array->n - 1;
	size_t center;
	while (left + 1 < right)
	{
		center = (left + right) / 2;
		int sign = cmp(array, center, elem);
		if (sign < 0)
			left = center;
		else
			right = center;
	}
	return right;
}

///Find the first element > @p elem
size_t findPlaceRight(struct sorted_array* array, void* elem)
{
	if (array->n == 0)
		return 0;
	if (cmp(array, 0, elem) > 0)
		return 0;
	if (cmp(array, array->n - 1, elem) < 0)
		return array->n;


	size_t left = 0;
	size_t right = array->n - 1;
	size_t center;
	while (left + 1 < right)
	{
		center = (left + right) / 2;
		int sign = cmp(array, center, elem);
		if (sign <= 0)
			left = center;
		else
			right = center;
	}
	return right;
}






// =================================  API funcs  =======================================
/**
 * @errors
 * @b ENOMEM -- Failed to allocate memory;\n
 * @b ERANGE -- @p elem_size of @p max_elems is not positive.
 */
struct sorted_array* sacreate(ssize_t elem_size, ssize_t max_elems, int (*compar)(void* a, void* b))
{
	if (elem_size <= 0 || max_elems <= 0)
	{
		errno = ERANGE;
		return NULL;
	}

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

/**
 * @errors
 * @b EINVAL -- @p array is NULL.
 */
void sadelete(struct sorted_array* array)
{
	if (array == NULL)
	{
		errno = EINVAL;
		return;
	}

	free(array->buffer);
	free(array);
}

/**
 * @errors
 * @b EINVAL -- @p array is NULL;\n
 * @b ERANGE -- @p index is out of range.
 */
void* saget(struct sorted_array* array, size_t index)
{
	if (array == NULL)
	{
		errno = EINVAL;
		return NULL;
	}

	if (index >= array->n)
	{
		errno = ERANGE;
		return NULL;
	}

	return (char*)array->buffer + index * array->elem_size;
}

/**
 * @errors
 * @b EINVAL -- @p array is NULL;\n
 * @b ENOMEM -- Maximum number of stored elements is reached.
 */
int saput(struct sorted_array* array, void* elem)
{
	if (array == NULL || elem == NULL)
	{
		errno = EINVAL;
		return -1;
	}
	
	if (array->n >= array->max_elems)
	{
		errno = ENOMEM;
		return -1;
	}

	size_t place = findPlace(array, elem);
	insert(array, place, elem);

	return 0;
}

/**
 * @errors
 * @b EINVAL -- @p array is NULL;\n
 * @b ERANGE -- @p index is out of range.
 */
int sarm(struct sorted_array* array, size_t index)
{
	if (array == NULL)
	{
		errno = EINVAL;
		return -1;
	}

	if (index >= array->n)
	{
		errno = ERANGE;
		return -1;
	}

	remove(array, index);
	return 0;
}

/**
 * @errors
 * @b EINVAL -- @p array or @p elem is NULL
 */
int sarmall(struct sorted_array* array, void* elem)
{
	if (array == NULL || elem == NULL)
	{
		errno = EINVAL;
		return -1;
	}

	size_t left = findPlaceLeft(array, elem);
	size_t right = findPlaceRight(array, elem);

	// TODO do it at once:
	for (; right > left; right--)
		sarm(array, left);

	return 0;
}

/**
 * @errors
 * @b EINVAL -- @p array is NULL.
 */
size_t salen(struct sorted_array* array)
{
	if (array == NULL)
	{
		errno = EINVAL;
		return (size_t) -1;
	}

	return array -> n;
}

/**
 * @errors
 * @b EINVAL -- @p array or @p elem is NULL;\n
 * @b ENOENT -- there is no such element in the array.
 */
size_t safind(struct sorted_array* array, void* elem)
{
	if (array == NULL || elem == NULL)
	{
		errno = EINVAL;
		return (size_t)-1;
	}

	if (array->n == 0)
	{
		errno = ENOENT;
		return (size_t)-1;
	}

	size_t place = findPlaceLeft(array, elem);
	if (place == array->n)
	{
		errno = ENOENT;
		return (size_t)-1;
	}

	if (cmp(array, place, elem) == 0)
		return place;
	else
	{
		errno = ENOENT;
		return (size_t)-1;
	}
}






// ----------- Iterator --------------

/**
 * @errors
 * @b EINVAL -- @p array is NULL;\n
 * @b ENOMEM -- Failed to allocate memory.
 */
struct sa_iter* sainew(struct sorted_array* array)
{
	if (array == NULL)
	{
		errno = EINVAL;
		return NULL;
	}

	struct sa_iter* it = (struct sa_iter*) malloc(sizeof(struct sa_iter));
	if (it == NULL)
		return NULL;

	it -> array = array;
	it -> i = 0;

	return it;
}

/**
 * @errors
 * @b EINVAL -- @p it is NULL. 
 */
int saiend(struct sa_iter* it)
{
	if (it == NULL)
	{
		errno = EINVAL;
		return -1;
	}

	if ((it -> i) < (it -> array -> n))
		return 0;
	else
	{
		free(it);
		return 1;
	}
}

/**
 * @errors
 * @b EINVAL -- @p it is NULL
 */
int sainext(struct sa_iter* it)
{
	if (it == NULL)
	{
		errno = EINVAL;
		return -1;
	}

	it -> i++;
	return 0;
}

/**
 * @errors
 * @b EINVAL -- @p it is NULL
 */
void* saiget(struct sa_iter* it)
{
	if (it == NULL)
	{
		errno = EINVAL;
		return NULL;
	}

	return getElem(it -> array, it -> i);
}
