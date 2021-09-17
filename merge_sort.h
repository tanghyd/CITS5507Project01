/* merge_sort.h */
#ifndef MERGE_SORT
#define MERGE_SORT

#include <string.h>

/* the main function to implement mergesort */ 
void merge(double *arr, double *temp, int size);

// serial
void merge_sort(double *arr, double *temp, int size);

// parallel (with hybrid cutoff)
void merge_sort_tasks(double *arr, double *temp, int size, int cutoff);
void merge_sort_sections(double *arr, double *temp, int size, int cutoff);
// void merge_sort_hybrid_tasks(double *arr, double *temp, int size, int cutoff);

#endif