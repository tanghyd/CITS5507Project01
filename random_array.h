/* random_array.h */
#ifndef RANDOM_ARRAY
#define RANDOM_ARRAY

#include <stdio.h>
#include <stdlib.h>

// Functions to print an array
void fill_double_array(double arr[], int size);
void print_double_array(double arr[], int start, int end);
void copy_double_array(double arr[], double arr_copy[], int size);
void reset_double_array(double arr[], int size);
int check_array_order(double arr[], int size);

// void fill_int_array(int *arr, int size, int max);
void print_int_array(int arr[], int start, int end);

#endif