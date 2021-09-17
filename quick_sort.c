/* quick_sort.h */

#include "quick_sort.h"


// utility function to swap two elements
void swap(double *a, double *b)
{
    double temp = *a;
    *a = *b;
    *b = temp;
}


/* last-element partition function */
int partition (double *arr, int low, int high)
{
    double pivot = arr[high];
    int i = low - 1;

    // loop through partitioned array indices
    for (int j = low; j < high; j++)
    {
        // if current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);  // pass mem address of array
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}


/* recursive quicksort */
void quick_sort(double *arr, int low, int high)
{
    {
        if (low >= 0 && high >= 0)
        {        
            if (low < high)
            {
                /* pi is the "partitioning index, where
                arr[pi] is swapped to correct location*/
                int pi = partition(arr, low, high);

                // separately sort elements before and after pi
                // #pragma omp task firstprivate(arr, low, pi)
                quick_sort(arr, low, pi - 1);
                quick_sort(arr, pi + 1, high);
            }
        }
    }
}


/* parallel recursive quicksort - tasking */
void quick_sort_tasks(double *arr, int low, int high, int cutoff)
{
    {
        if (low >= 0 && high >= 0)
        {        
            if (low < high)
            {
                // pi is the partitioning index, where
                // arr[pi] is swapped to correct location
                int pi = partition(arr, low, high);

                // separately sort elements before and after pivot
                // serial if array bigger than cutoff
                #pragma omp task shared(arr) firstprivate(low, pi) if (high - low > cutoff)
                {
                    quick_sort_tasks(arr, low, pi - 1, cutoff);
                }
                #pragma omp task shared(arr) firstprivate(pi, high) if (high - low > cutoff)
                {
                    quick_sort_tasks(arr, pi + 1, high, cutoff);
                }
            }
        }
    }
}


/* parallel recursive quicksort - sections */
void quick_sort_sections(double *arr, int low, int high, int cutoff)
{
    if (low >= 0 && high >= 0 && low < high)
    {        
        /* pi is the "partitioning index, where
        arr[pi] is swapped to correct location*/
        int pi = partition(arr, low, high);

        if (high - low > cutoff)
        {
            // array large enough to warrant parallelism
            #pragma omp parallel shared(arr)
            #pragma omp sections
            {
                #pragma omp section
                {
                    quick_sort_sections(arr, low, pi - 1, cutoff);
                }
                #pragma omp section
                {
                    quick_sort_sections(arr, pi + 1, high, cutoff);
                }
            }
        }
        else
        {
            // serial implementation
            quick_sort(arr, low, pi - 1);
            quick_sort(arr, pi + 1, high);
        }
    }
}