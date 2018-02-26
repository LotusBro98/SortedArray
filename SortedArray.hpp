/** @file SortedArray.hpp
 * Header file for Sorted Array data structure wrapper class.
 */



#include "sorted_array.h"

/**
 * Sorted array wrapper class
 * @see sorted_array
 */
template <class T> class SortedArray
{
public:
	SortedArray(size_t maxElems, int (*compar)(void* a, void* b)) throw (int)
	{
		array = saalloc(sizeof(T), maxElems, compar);
		if (errno != 0)
			throw errno;
	}

	~SortedArray()
	{
		for (struct sa_iter* it = sainew(array); !saiend(it); sainext(it))
			((T*)saiget(it))->~T();
		sadelete(array);
	}

	void put(T &elem) 
	{
		saput(array, &elem);
	}

	T* get(size_t index) 
	{
		saget(array, index);
	}

	void remove(size_t index) 
	{
		sarm(array, index);
	}

	void removeAll(T &elem)
	{
		sarmall(array, &elem);
	}

	size_t len()
	{
		return salen(array);
	}

	size_t find(T &elem)
	{
		return safind(array, &elem);
	}

	void resort()
	{
		saresort(array);
	}

	void foreach(void (*func)(void* elem))
	{
		saforeach(array, func);
	}

	void foreach(void* context, void (*func)(struct sorted_array* array, void* elem, void* context))
	{
		saforeach(array, context, func);
	}
	
private:
	struct sorted_array* array;
}

/**
 * Sorted Array iterator
 * @see sa_iter;
 */
template <class T> class SAIterator
{
public:
	SAIterator(struct sorted_array* array)
	{
		iter = sainew(array);	
	}

	~SAIterator()
	{
		saidelete(iter);
	}

	T* get()
	{
		return (T*)saiget(iter);
	}

	void next()
	{
		sainext(iter);
	}

	bool isEnd()
	{
		return saiend(iter);
	}

private:
	struct sa_iter* iter;
}
