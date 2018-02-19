/** @file sorted_array.h
 * Header file containing interface for working with sorted array data structure.
 *
 * Here you can find declarations and descriptions of:
 * - struct sotred_array;
 * - functions for creating and destroying a sorted array:
 *   + sacreate();
 *   + sadelete();
 * - functions for working with elements:
 *   + saput(); //TODO
 *   + saget(); //TODO
 *   + sarm(); //TODO
 *   + sarmall(); //TODO
 * - functions for obtaining information about an array and its elements:
 *   + salen(); //TODO
 *   + safind(); //TODO
 * - iterator interface for this structure:
 *   + struct sa_iter; //TODO
 *   + sainew(); //TODO
 *   + saiend(); //TODO
 *   + sainext(); //TODO
 *   + saiget(); //TODO
 * - different variants of foreach() function. //TODO
 * - saresort() function to fix broken order in case when it can change. //TODO
 */

#ifndef SORTED_ARRAY_H
#define SORTED_ARRAY_H

#include <stdlib.h>

/** @struct sorted_array
 * Structure representing a static array that is always sorted.
 *
 * This array can contain elements of any size, but all elements in one array are of the same size.
 * The elements are stored one by one in a buffer allocated in heap.
 *
 * The array is sorted, so there must be relations of order between elements. 
 * When creating a new array, the caller of saalloc() must specify comparator function to define these relations.
 * These relations must preserve across the whole lifetime of the array.
 *
 * @note If you want to have an array of "heavy" elements, consider working with their pointers instead 
 * (So, in fact, the array will be dynamic).
 * @note If you encounter a situation when you need to apply some changes to the elements that can affect their order 
 *  (e.g. You are storing pointers to some elements, and you also have pointers to them in other places of the program), 
 *  call saresort() function to sort the array again.
 * @note The array is sorted in ascending order.
 */
 struct sorted_array;

/**
 * Create a new sorted array.
 *
 * This function allocates a space for the sorted_array struct and for underlying buffer in the heap.
 *
 * @param elem_size size of one element in bytes
 * @param max_elems max array length 
 * @param compar specifies a comparator function. 
 * It has to return negative value if the first argument is less than the second, 
 * positive value if the first argument is bigger than the second, 
 * and zero if they are equal.
 * @return A pointer to newly created array, or NULL in case of an error.
 * @errors See man 3 malloc
 */
struct sorted_array* sacreate(size_t elem_size, size_t max_elems, int (*compar)(void* a, void* b));

/**
 * Delete a sorted array.
 *
 * Free the space, allocated for this struct and the underlying buffer.
 */
void sadelete(struct sorted_array* array);

/**
 * Get a pointer to an element of the array by its index.
 *
 * @return A pointer to i'th element or NULL, if index is out of range.
 * @note This function doesn't create a new instance of an element, so if you want to change the element afterwards, you will need to copy the element manually. Also you can call saresort() after applying changes.
 */
void* saget(struct sorted_array* array, size_t index);

/**
 * Put an element into a sorted array.
 *
 * This function will insert a copy of given element into a sorted array, keeping its ascending order.
 * @return 0, if no error, -1 otherwise
 */
int saput(struct sorted_array* array, void* elem);

#endif
