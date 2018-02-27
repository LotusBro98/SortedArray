/** @file SortedArray.hpp
 * Header file for Sorted Array data structure wrapper class.
 */



#include "sorted_array.h"

#include <iostream>

/**
 * Sorted array wrapper class
 * @see sorted_array
 */
template <typename T> class SortedArray
{
public:
	inline SortedArray(size_t maxElems, int (*compar)(const void* a, const void* b))
	{
		array = sanew(sizeof(T), maxElems, compar);
	}

	~SortedArray()
	{
		for (Iterator it(*this); !it.isEnd(); it.next())
			it.get().~T();
		sadelete(array);
	}

	inline void put(T elem)			{ saput(array, &elem); }
	inline T get(size_t index)		{ return *(T*)saget(array, index); }
	inline void remove(size_t index){ sarm(array, index); }
	inline void removeAll(T elem)	{ sarmall(array, &elem); }
	inline size_t len()				{ return salen(array); }
	inline size_t find(T elem)		{ return safind(array, &elem); }
	inline void resort()			{ saresort(array); }

	void foreach(void (*func)(void* elem))
	{ saforeach(array, func); }

	void foreach(void* context, void (*func)(struct sorted_array* array, void* elem, void* context))
	{ saforeach(array, context, func); }

	/**
	* Sorted Array Iterator
	 * @see sa_iter;
	 */
	class Iterator
	{
	public:
		Iterator(SortedArray &sa)
		{ it = sainew(sa.array); }

		~Iterator()
		{ saidelete(it); }

		inline T get()		{ return *(T*)saiget(it); }
		inline void next()	{ sainext(it); }
		inline bool isEnd()	{ return saiend(it); }

	private:
		struct sa_iter* it;
	};
	
	friend std::ostream& operator<<(std::ostream &os, SortedArray &sa)
	{
		for (Iterator it(sa); !it.isEnd(); it.next())
			os << it.get() << ' ';
		os << '\n';
		return os;
	}

	inline T operator[](size_t index)
	{
		return get(index);
	}

	template <size_t N>
	bool operator==(T (&array)[N])
	{
		if (len() != N)
			return false;

		for (size_t i = 0; i < N; i++)
			if (sacmp(this->array, i, &(array[i])) != 0)
				return false;

		return true;
	}

private:
	struct sorted_array* array;
};
