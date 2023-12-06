/**
 * Implemention of selected sorting algorithms
 * @file sorting.cpp
 */

#include "sorting.h"

/**
 * Implement the insertionSort algorithm correctly
 */
void insertionSort(int array[], int lowindex, int highindex, bool reversed) {
    int toinsert;
    int compareidx;
    // iterate over array from lowindex+1 to highindex+1
    for (int i = lowindex + 1; i <= highindex; i++) {
        // extract the data at i
        toinsert = array[i];
        compareidx = i-1;
        // work backwards from i-1 and copy elements
        // greater than toinsert to the right of their current position
        for (; compareidx >= 0 && (
            (array[compareidx] > toinsert && !reversed) ||
            (array[compareidx] < toinsert && reversed));
            compareidx--) {
            array[compareidx+1] = array[compareidx];
        }
        array[compareidx+1] = toinsert;
    }
}

void swap(int* a, int* b)

{

    int t = *a;

    *a = *b;

    *b = t;

}

/**
 * @brief Implementation of the partition function used by quick sort
 * 
 */
int partition(int array[], int lowindex, int highindex, bool reversed) {
    int pivot = array[highindex];
    int i = lowindex-1;
    
    for (int j = lowindex; j<= highindex - 1; j++) {
        if ((array[j] < pivot && !reversed) || (array[j] > pivot && reversed)) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i+1], &array[highindex]);
    return i+1;

}

/**
 * Implement the quickSort algorithm correctly
 */
void quickSort(int array[], int lowindex, int highindex, bool reversed) {
    if (lowindex < highindex) {
        int part = partition(array, lowindex, highindex, reversed);
        quickSort(array, lowindex, part-1, reversed);
        quickSort(array, part+1, highindex, reversed);
    }
}


