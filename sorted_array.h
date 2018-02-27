/** @file sorted_array.h
 * Header file containing interface for working with sorted array data structure.
 *
 * Here you can find declarations and descriptions of:
 * - struct sotred_array;
 * - functions for creating and destroying a sorted array:
 *   + sanew();
 *   + sadelete();
 * - functions for working with elements:
 *   + saput();
 *   + saget();
 *   + sarm();
 *   + sarmall();
 * - functions for obtaining information about an array and its elements:
 *   + salen();
 *   + safind();
 *   + sacmp();
 * - iterator interface for this structure:
 *   + struct sa_iter;
 *   + sainew();
 *   + saidelete();
 *   + saiend();
 *   + sainext();
 *   + saiget();
 * - different variants of foreach() function.
 * - saresort() function to fix broken order in case when it can change.
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
 */
struct sorted_array* sanew(ssize_t elem_size, ssize_t max_elems, int (*compar)(const void* a, const void* b));

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

/**
 * Remove an element specified by its index from sorted array.
 *
 * @return 0 on success, -1 in case of an error.
 */
int sarm(struct sorted_array* array, size_t index);

/**
 * Remove all elements that are equal to given from a sorted array.
 *
 * @return 0 on success, -1 in case of an error.
 */
int sarmall(struct sorted_array* array, void* elem);

/**
 * Get sorted array length.
 *
 * @return A number of elements, currently stored in @p array, or (size_t)-1 in case of an error.
 */
size_t salen(struct sorted_array* array);

/**
 * Find an element in a sorted array.
 *
 * Get an index of first occurence of @p elem in a sorted array, performing binary search.
 *
 * @return Index of given element, or (size_t)-1 in case of an error.
 */
size_t safind(struct sorted_array* array, void* elem);

/**
 * Compare an element of a sorted array, specified by @p index, with @p elem.
 *
 * @return An integer less than, equal to, or greater than zero, 
 * if i-th element is less than, equal to, or greater than @p elem.
 */
int sacmp(struct sorted_array* array, size_t index, void* elem);

/**
 * Sort array again in case when relations of order between stored elements change.
 * 
 * Invoke qsort() on an array to restore broken order.
 * @return 0 on success, -1 on error
 */
int saresort(struct sorted_array* array);

/**
 * Call @p func on every element of an array.
 */
int saforeach(struct sorted_array* array, void (*func)(void* elem));

/**
 * Call @p func on every element of an array.
 *
 * The extended version. You can also pass an argument @p context to every call of @p func.
 */
int saforeach(struct sorted_array* array, void* context, void (*func)(struct sorted_array* array, void* elem, void* context));

// ----------------------------------  ITERATOR -------------------------------

/** @struct sa_iter
 * Sorted array iterator.
 *
 * Presents a convenient way to perform an action to every element in an array.
 *
 * @b Example
 * ~~~~~~~~~~~~~~~~~{.c}
 * struct sa_iter* it;
 * for (it = sainew(array); !saiend(it); sainext(it))
 *     *(int*)saiget(it) = 0;
 * saidelete(it);
 * ~~~~~~~~~~~~~~~~~
 */
struct sa_iter;

/**
 * Create a new sorted array iterator.
 *
 * Allocates memory for a new iterator of sorted array @p array, that will be automatically freed when saiend() returns true;
 * @return Pointer to the newly created iterator.
 * @see sa_iter
 */
struct sa_iter* sainew(struct sorted_array* array);

/**
 * Delete sorted array iterator.
 */
void saidelete(struct sa_iter* it);

/**
 * Check, whether the iteraor has reached the end of an array.
 *
 * @return 
 * 0, if the end is not reached; \n
 * 1, if all the elements have been iterated; \n
 * -1 in case of an error.
 */
int saiend(struct sa_iter* it);

/**
 * Shifts the iterator to the next element.
 * 
 * @return 0 if no error; -1 in case of an error.
 */
int sainext(struct sa_iter* it);

/**
 * Get a pointer to the current element under the iterator.
 *
 * @returns Pointer to the current element, or NULL, in case of an error.
 */
void* saiget(struct sa_iter* it);
#endif
