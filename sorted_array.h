/** @file sorted_array.h
 * Header file containing interface for working with sorted array data structure.
 *
 * Here you can find declarations and descriptions of:
 * - struct sotred_array;
 * - functions for creating and destroying a sorted array:
 *   + saalloc();
 *   + safree();
 * - functions for working with elements:
 *   + saput();
 *   + saget();
 *   + sarm();
 *   + sarmall();
 * - functions for obtaining information about an array and its elements:
 *   + salen();
 *   + safind();
 * - iterator interface for this structure:
 *   + struct sorted_array_iter;
 *   + sainew();
 *   + saiend();
 *   + sainext();
 *   + saiget();
 * - different variants of foreach() function.
 * - saresort() function to fix broken order in case when it can change.
 */


/** @struct sorted_array
 * Structure representing a static sorted array.
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
 */
 struct sorted_array;
