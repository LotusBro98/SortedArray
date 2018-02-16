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
 */
