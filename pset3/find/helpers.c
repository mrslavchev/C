/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

// Implementation of binary search algorithm.
int binarySearch(int array[], int key, int min, int max){
    if(max < min){
        return -1;
    }else{
        int midPoint = (max + min) / 2;
        if(array[midPoint] > key){
            return binarySearch(array, key, min, midPoint - 1);
        }else if(array[midPoint] < key){
            return binarySearch(array, key, midPoint + 1, max);
        }else{
            return array[midPoint];
        }  
    }
}

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int result = binarySearch(values, value, 0, n - 1);
    
    if(result == value)
        return true;
    else
        return false;  
}



/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int i, j;
	int iMin;
	
	for(j = 0; j < n - 1; j++){
		iMin = j;
		for(i = j + 1; i < n; i++){
			if(values[i] < values[iMin]){
				iMin = i;
			}
		}
		
		if(iMin != j){
			values[j] ^= values[iMin];
			values[iMin] ^= values[j];
			values[j] ^= values[iMin];
		}
	}
	
	return;
}
