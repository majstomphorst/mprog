/****************************************************************************
 * helpers.c
 * Programmeren 01 - pset 03 - exercise 01
 * By Maxim Stomphorst
 * 
 * This file contains 2 function:
 * - search
 *   Searches for a number in an array that is sorted from small to large.
 *            input: value   = The value its searching for.
 *                   values  = The array that is searched.
 *                   n       = The length of the array (values).
 *           output: false   = Value is not found or value is negative.
 *                   true    = Value is found.
 * - sort
 *   Sorts an array from small to large the sorting methode is selection sort.
 *            input: values  = The array that is to be sorted.
 *                   n       = The length of the array (values).
 *           output:         = Array (values) is sorted.
***************************************************************************/

#include <cs50.h>
#include "helpers.h"

bool search(int value, int values[], int n)
{
    // checking for negative
    if (value < 0)
    {
        return false;
    }
    
    // determining the lowwer an upper boundaries of values
    int low = 0;
    int up = n;
    
    // stop when low and up are in the same spot
    while (low <= up)
    {
        // getting middle
        int middle = (low + up) / 2;
        
        // if value is smaller than middel
        if (value < values[middle])
        {
            // move upper boundarie to middel and because middel is check - 1 
            up = (middle - 1);
        }
        // if value is bigger than middel
        else if (value > values[middle])
        {
            // move lowwer boundarie to middel and because middel is check + 1 
            low = middle + 1;
        }
        // if value is found return true
        else 
        {
            return true;
        }
    }
    // if value is not found return false
    return false;
}

void sort(int values[], int n)
{
    // gowing through array (values) one by one 
    // than scanning for lowest number but excluding ith
    for (int i = 0; i < n - 1; i++)
    {
        // selecting ith letter as lowest 
        int low = i;
        
        // gowing through array again looking for lowest number start from ith
        for (int j = i; j < n; j++)
        {
            // if value is lower than jth number
            if (values[low] > values[j])
            {
                // update lowest number
                low = j;
            }
        }
        // putting lowest number at ith (swapping the two numbers)
        int swap = values[low];
        values[low] = values[i];
        values[i] = swap;   
    }
    // done return
    return;
}