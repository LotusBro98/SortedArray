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
		if (errno != 0)
			throw errno;
	}

	~SortedArray()
	{
		for (Iterator it(*this); !it.isEnd(); it.next())
			it.get().~T();
		sadelete(array);
	}

	inline void put(T elem)	
	{ 
		saput(array, &elem); 
		if (errno != 0)
			throw errno;
	}
	
	inline T get(size_t index) 
	{ 
		T* t = (T*)saget(array, index); 
		if (errno == 0)
			return *t;
		else 
			throw errno;
	}
	
	inline void remove(size_t index) 
	{
		sarm(array, index); 
		if (errno != 0)
			throw errno;
	}
	
	inline void removeAll(T elem) 
	{ 
		sarmall(array, &elem); 
	}

	inline size_t len()	
	{ 
		return salen(array); 
	}

	inline int cmp(size_t index, T elem)
	{
		int res = sacmp(array, index, &elem);
		if (errno == 0)
			return res;
		else
			throw errno;
	}
	
	inline size_t find(T elem) 
	{ 
		size_t i = safind(array, &elem); 
		if (errno == 0)
			return i;
		else
			throw errno;
	}
	
	inline void resort() 
	{ saresort(array); }

	void foreach(void (*func)(void* elem)) 
	{ 
		saforeach(array, func); 
		if (errno != 0)
			throw errno;
	}

	void foreach(void* context, void (*func)(void* elem, void* context))
	{ 
		saforeach(array, context, func); 
		if (errno != 0)
			throw errno;
	}

	/**
	* Sorted Array Iterator
	 * @see sa_iter;
	 */
	class Iterator
	{
	public:
		Iterator(SortedArray &sa)
		{ 
			it = sainew(sa.array); 
			if (errno != 0)
				throw errno; 
		}

		~Iterator()
		{ saidelete(it); }

		inline T get() 
		{
			T* t = (T*)saiget(it); 
			if (errno == 0)
				return *t;
			else
				throw errno;
		}
		
		inline void next()	
		{ 
			sainext(it); 
			if (errno != 0)
				throw errno; 
		}
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
			if (cmp(i, array[i]) != 0)
				return false;

		return true;
	}

	template <size_t N>
	inline bool operator!=(T (&array)[N])
	{ 
		return !operator==(array); 
	}
	

private:
	struct sorted_array* array;
};
