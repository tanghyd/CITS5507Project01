#include "merge_sort.h"



/* last-element partition function */
void merge(double *arr, double *temp, int size)
{
    // begin loop to copy from temp
    // to main array in sorted order
    int i = 0;
    int j = size/2;
    int n = 0;

    // loop if both subarrays have elements
    while (i<(size/2) && j<size)
    {
        // add smaller element to temp array
        if (arr[j] > arr[i])
        {
            temp[n] = arr[i];
            i++;
        }
        else 
        {
            temp[n] = arr[j];
            j++;
        }
        n++;
    }

    // if both conditions above not satisfied
    // then one subarray has been emptied
    // loop through remaining (sorted) elements
    while (i < (size/2))
    {
        temp[n] = arr[i];
        i++;
        n++;
    }

    while (j < size)
    {
        temp[n] = arr[j];
        j++;
        n++;
    }

    // copy temp array into main array
    memcpy(arr, temp, size*sizeof(double));
}


// computes merge sort algorithm on sub-array
// defined on the interval arr[low:high]
void merge_sort(double *arr, double *temp, int size)
{
    if (size < 2)
        return;

    // recursively sort subarrays
    // select sub-arrays by incrementing pointer positions
    merge_sort(arr, temp, size/2);
    merge_sort(arr + (size/2), temp + (size/2), size - (size/2));
    merge(arr, temp, size);
}

// computes merge sort algorithm on sub-array
// defined on the interval arr[low:high]
void merge_sort_tasks(double *arr, double *temp, int size, int cutoff)
{
    if (size < 2)
        return;

    // recursively sort subarrays
    // select sub-arrays by incrementing pointer positions
    #pragma omp task shared(arr, temp) if (size > cutoff)
    merge_sort_tasks(arr, temp, size/2, cutoff);

    #pragma omp task shared(arr, temp) if (size > cutoff)
    merge_sort_tasks(arr + (size/2), temp + (size/2), size - (size/2), cutoff);

    #pragma omp taskwait
    merge(arr, temp, size);

}



// computes merge sort algorithm on sub-array
// defined on the interval arr[low:high]
// void merge_sort_hybrid_tasks(double *arr, double *temp, int size, int cutoff)
// {
//     if (size < 2)
//         return;

//     if (size > cutoff)
//     {
//         #pragma omp parallel
//         {
//             #pragma omp single nowait
//             {
//                 // recursively sort subarrays
//                 // select sub-arrays by incrementing pointer positions
//                 #pragma omp task shared(arr, temp) // if (size > cutoff)
//                 merge_sort_tasks(arr, temp, size/2, cutoff);

//                 #pragma omp task shared(arr, temp) // if (size > cutoff)
//                 merge_sort_tasks(arr + (size/2), temp + (size/2), size - (size/2), cutoff);

//                 #pragma omp taskwait
//                 merge(arr, temp, size);
//             }
//         }
//     }
//     else
//     {
//         // else serial implementation
//         merge_sort(arr, temp, size/2);
//         merge_sort(arr + (size/2), temp + (size/2), size - (size/2));
//         merge(arr, temp, size);
//     }
// }


void merge_sort_sections(double *arr, double *temp, int size, int cutoff)
{
    if (size < 2)
        return;

    if (size > cutoff)
    {
        // recursively sort subarrays
        #pragma omp parallel shared(arr, temp)
        #pragma omp sections
        {
            #pragma omp section
            {
                // merge sort lower half
                merge_sort_sections(arr, temp, size/2, cutoff);
            }
            #pragma omp section
            {
                // merge sort upper half
                merge_sort_sections(arr + (size/2), temp + (size/2), size - (size/2), cutoff);
            }
        }
    }
    else
    {
        // else serial implementation
        merge_sort(arr, temp, size/2);
        merge_sort(arr + (size/2), temp + (size/2), size - (size/2));
    }
    merge(arr, temp, size);
}