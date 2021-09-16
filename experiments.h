/* experiments.h */
#ifndef EXPERIMENTS
#define EXPERIMENTS

#include <omp.h>
#include "random_array.h"
#include "quick_sort.h"
#include "merge_sort.h"
#include "enumeration_sort.h"

// quick sort
double time_quick_sort_serial(double *arr, int size);
double time_quick_sort_tasks(double *arr, int size, int cutoff);
double time_quick_sort_sections(double *arr, int size, int cutoff);

// merge sort
double time_merge_sort_serial(double *arr, double *temp, int size);
double time_merge_sort_tasks(double *arr, double *temp, int size, int cutoff);
double time_merge_sort_sections(double *arr, double *temp, int size, int cutoff);

// enumeration sort
double time_enumeration_sort_serial(double *arr, double *temp, int size);
double time_enumeration_sort_parallel(double *arr, double *temp, int size);

#endif 