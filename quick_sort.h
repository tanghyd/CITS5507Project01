/* quick_sort.h */
#ifndef QUICK_SORT
#define QUICK_SORT

// utility function to swap two elements
void swap(double* a, double* b);

// pivot by last element in array
int partition(double arr[], int low, int high);

// serial implementation
void quick_sort(double arr[], int low, int high);

// parallel (with hybrid cutoff)
void quick_sort_tasks(double arr[], int low, int high, int cutoff);
void quick_sort_sections(double arr[], int low, int high, int cutoff);

#endif