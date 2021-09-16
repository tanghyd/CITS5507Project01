/* random_array.h */
#include "random_array.h"

// fills an array with random doubles
void fill_double_array(double arr[], int size)
{
    // #pragma omp parallel for firstprivate(arr, size, max)
    for (int i = 0; i < size; i++)
    {
        arr[i] = (double)rand()/RAND_MAX; // range 0. to 1.
    }
}

void copy_double_array(double arr[], double arr_copy[], int size)
    {   
        for (int i = 0; i < size; i++)
        {
            arr_copy[i] = arr[i];
        }
    }

void reset_double_array(double arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = 0;
    }

}

void print_double_array(double arr[], int start, int end)
{
    for (int i = start; i < end; i++)
    {
        printf("%.15f ", arr[i]);
    }
    printf("\n");
}

// returns 1 if array is correctly sorted, else 0.
int check_array_order(double arr[], int size)
{
    int sorted = 1;
    for (int i=0; i < size-1; i++)
    {
        if (arr[i] > arr[i+1])
        {
            sorted = 0;
            // printf("%g at %d > %g at %d\n", arr[i], i, arr[i+1], i+1);
            break;
        }
    }
    
    return sorted;
}

// fills an array with random integers - can set a max limit
// void fill_int_array(int *arr, int size, int max)
// {
//     // #pragma omp parallel for firstprivate(arr, size, max)
//     for (int i = 0; i < size; i++)
//     {
//         if (max > 0) {
//             *arr++ = rand() % max;  // pseudo-random 0 < int < max
//         } else {
//             *arr++ = rand();  // pseudo-random 0 < int < RAND_MAX
//         }
//         // arr++;
//     }
// }


void print_int_array(int arr[], int start, int end)
{
    for (int i = start; i < end; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// void print_int_array(int *arr, int size)
// {
//     for (int i = 0; i < size; i++)
//     {
//         // printf("%d ", *arr);
//         // arr++;
//     }
//     printf("\n");
// }