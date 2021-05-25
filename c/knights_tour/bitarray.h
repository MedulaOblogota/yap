#ifndef BITARRAY_OL70 /*header gaurd*/
#define BITARRAY_OL70

/********************************************************
* The functions in this file handle a bit array     	*
* data structure. 				   						*
* The implementation of the bit array is by	            *
* using an unsigned long variable.		    			*
*						    							*
*						    							*
* Written by: OL-70				    					*
* Last update: 22:05 , 26.06.2019                 		*
*********************************************************/

#include <stddef.h> /*for size_t */

int BitsArrIsBitOn(unsigned long bit_array, size_t bit_index);
/********************************************************
* Checks if an index bit is on in bit_array				*
* bit_array - an implementation of a 64 bit array		*
* Maximum size: 64 elements, indexed 0-63				*
* bit_index - index of the bit to check, 				*
* Valid input of bit_index - 0-63.						*
* Return value: boolean int, 1 if true, 0 otherwise		*
* Complexity - O(1)										*
*********************************************************/

int BitsArrIsBitOff(unsigned long bit_array, size_t bit_index);
/********************************************************
* Checks if an index bit is off in bit_array			*
* bit_array - an implementation of a 64 bit array		*
* Maximum size: 64 elements, indexed 0-63				*
* bit_index - index of the bit to check, 				*
* Valid input of bit_index - 0-63.						*
* Return value: boolean int, 1 if true, 0 otherwise		*
* Complexity - O(1)										*
*********************************************************/

unsigned long BitsArrSetBitOn (unsigned long bit_array, size_t bit_index);
/********************************************************
* Sets bit_index bit on	in bit_array					*
* bit_array - an implementation of a 64 bit array		*
* Maximum size: 64 elements, indexed 0-63				*
* bit_index - index of the bit to set on, 				*
* Valid input of bit_index - 0-63.						*
* Return value: updated bit_array of type unsigned long	*
* Complexity - O(1)										*
*********************************************************/

unsigned long BitsArrSetBitOff (unsigned long bit_array, size_t bit_index);
/********************************************************
* Sets bit_index bit off in bit_array					*
* bit_array - an implementation of a 64 bit array		*
* Maximum size: 64 elements, indexed 0-63				*
* bit_index - index of the bit to set off, 				*
* Valid input of bit_index - 0-63.						*
* Return value: updated bit_array of type unsigned long	*
* Complexity - O(1)										*
*********************************************************/

unsigned long BitsArrSetBit (unsigned long bit_array, size_t bit_index,
                                                        int bit_value);
/********************************************************
* Sets bit_index bit to bit_value in bit_array			*
* bit_array - an implementation of a 64 bit bit_array	*
* Maximum size: 64 elements, indexed 0-63				*
* bit_index - index of the bit to set on / off,			*
* Valid input of bit_index - 0-63.						*
* Valid input of bit_value - 1 / 0 (on / off)			*
* Return value: updated bit_array of type unsigned long	*
* Complexity - O(1)										*
*********************************************************/

unsigned long BitsArrFlip(unsigned long bit_array, size_t bit_index);
/********************************************************
* Toggles bit_index bit in bit_array					*
* bit_array - an implementation of a 64 bit array		*
* Maximum size: 64 elements, indexed 0-63				*
* bit_index - index of the bit to toggle, 				*
* Valid input of bit_index - 0-63.						*
* Return value: updated bit_array of type unsigned long	*
* Complexity - O(1)										*
*********************************************************/


size_t BitsArrCountOn(unsigned long bit_array);
/********************************************************
* Counts how many bits are set in bit_array				*
* bit_array - an implementation of a 64 bit array		*
* Maximum size: 64 elements, indexed 0-63				*
* Return value: The number of set bits in bit_array 	*
* Complexity - O(n)										*
*********************************************************/

size_t BitsArrCountOff(unsigned long bit_array);
/********************************************************
* Counts how many bits are unset in bit_array			*
* bit_array - an implementation of a 64 bit array		*
* Maximum size: 64 elements, indexed 0-63				*
* Return value: The number of unset bits in bit_array	*
* Complexity - O(n)										*
*********************************************************/

unsigned long BitsArrRotateLeft(unsigned long bit_array, size_t shift_amount);
/********************************************************
* Rotates bit_array left a number of times		      	*
* as given in shift_amount 				    			*
* bit_array - an implementation of a 64 bit array	    *
* Maximum size: 64 elements, indexed 0-63		      	*
* Shift_amount - any positive number			  	    *
* Return value: The updated bit_array		 	  	    *
* Complexity - O(n)					   					*
*********************************************************/

unsigned long BitsArrRotateRight(unsigned long bit_array, size_t shift_amount);
/********************************************************
* Rotates bit_array right a number of times		    	*
* as given in shift_amount 				      			*
* bit_array - an implementation of a 64 bit array	    *
* Maximum size: 64 elements, indexed 0-63		      	*
* Shift_amount - any positive number			     	*
* Return value: The updated bit_array		 	      	*
* Complexity - O(n)					     				*
*********************************************************/

unsigned long BitsArrMirror(unsigned long bit_array);
/********************************************************
* Mirrors bit_array 	  				      			*
* bit_array - an implementation of a 64 bit array	    *
* Maximum size: 64 elements, indexed 0-63		      	*
* Return value: The updated bit_array		 	      	*
* Complexity - O(n)					      				*
*********************************************************/

unsigned long BitsArrLUTMirror(unsigned long bit_array);
/********************************************************
* Mirrors bit_array 	  				      			*
* bit_array - an implementation of a 64 bit array	    *
* Maximum size: 64 elements, indexed 0-63		      	*
* Return value: The updated bit_array,					*
* by using a LUT which contains mirrored 64-bit values	*
* for each variation of bit_array 					 	*
* Complexity - Time: O(1) Space: O(2^n)			      				*
*********************************************************/

size_t BitsArrLUTCountOn(unsigned long bit_array);
/********************************************************
* Counts how many bits are set in bit_array	 	  		*
* bit_array - an implementation of a 64 bit array	    *
* Maximum size: 64 elements, indexed 0-63		      	*
* Return value: The number of set bits in bit_array,	*
* by using a LUT which contains a value for the number	*
* of set bits for every variation of bit_array setting  *
* Complexity - Time: O(1) Space: O(2^n)					      				*
*********************************************************/



#endif /*BITARRAY_OL70*/
