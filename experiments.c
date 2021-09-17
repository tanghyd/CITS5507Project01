#include "experiments.h"

double time_quick_sort_serial(double *arr, int size)
{
    double start = omp_get_wtime();
    quick_sort(arr, 0, size-1);  // size-1 is final idx pos
    double end = omp_get_wtime();

    printf("Quick sort in %12.10fs. \n", end - start);
    if (check_array_order(arr, size) == 0)
        printf("### Above array is not sorted. ### \n");

    return end - start;
}

double time_quick_sort_tasks(double *arr, int size, int cutoff)
{
    double start = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        quick_sort_tasks(arr, 0, size-1, cutoff);
    }
    double end = omp_get_wtime();

    printf("Tasking quick sort in %12.10fs. \n", end - start);
    if (check_array_order(arr, size) == 0)
        printf("### Above array is not sorted. ### \n");
        
    return end - start;
}

double time_quick_sort_sections(double *arr, int size, int cutoff)
{
    double start = omp_get_wtime();
    quick_sort_sections(arr, 0, size-1, cutoff);
    double end = omp_get_wtime();

    printf("Sections quick sort in %12.10fs. \n", end - start);
    if (check_array_order(arr, size) == 0)
        printf("### Above array is not sorted. ### \n");
    
    return end - start;
}


// Merge Sort

double time_merge_sort_serial(double *arr, double *temp, int size)
{
    double start = omp_get_wtime();
    merge_sort(arr, temp, size);  // size-1 is final idx pos
    double end = omp_get_wtime();

    printf("Merge sort in %12.10fs. \n", end - start);
    if (check_array_order(arr, size) == 0)
        printf("### Above array is not sorted. ### \n");
    
    return end - start;
}

double time_merge_sort_tasks(double *arr, double *temp, int size, int cutoff)
{
    double start = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        merge_sort_tasks(arr, temp, size, cutoff);
    }   
    double end = omp_get_wtime();

    printf("Tasking merge sort in %12.10fs. \n", end - start);
    if (check_array_order(arr, size) == 0)
        printf("### Above array is not sorted. ### \n");
    
    return end - start;
}

double time_merge_sort_sections(double *arr, double *temp, int size, int cutoff)
{
    double start = omp_get_wtime();
    merge_sort_sections(arr, temp, size, cutoff);
    double end = omp_get_wtime();

    printf("Sections merge sort in %12.10fs. \n", end - start);
    if (check_array_order(arr, size) == 0)
        printf("### Above array is not sorted. ### \n");

    return end - start;
}

double time_enumeration_sort_serial(double *arr, double *temp, int size)
{
    double start = omp_get_wtime();
    enumeration_sort(arr, temp, size);
    double end = omp_get_wtime();

    printf("\nEnumeration sort in %12.10fs. \n", end - start);
    if (check_array_order(arr, size) == 0)
        printf("### Above array is not sorted. ### \n");

    return end - start;
}

double time_enumeration_sort_parallel(double *arr, double *temp, int size)
{
    double start = omp_get_wtime();
    enumeration_sort_parallel(arr, temp, size);
    double end = omp_get_wtime();

    printf("Parallel enumeration sort in %12.10fs. \n", end - start);
    if (check_array_order(arr, size) == 0)
        printf("### Above array is not sorted. ### \n");

    return end - start;
}