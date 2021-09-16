# CITS5507 Project 1

This repository stores the code used to implement serial and parallel implementations of quick sort, merge sort, and enumeration sorting using C and OpenMP.

## Setup

Code was run on a machine with the following specifications:

- Operating System: Ubuntu 18.04.5 LTS
- CPU: AMD Ryzen Threadripper 2920X 12-Core Processor
- RAM: 62.7GB

Source code was compiled with the following command:

`gcc -fopenmp -o main main.c experiments.c quick_sort.c merge_sort.c enumeration_sort.c random_array.c`

Running `./main` saves .csv files to the `results/` directory.
Data analysis on the stored results are done in Python and plotting figures are created using the `matplotlib` library.

## Experiment Summary

Each sorting algorithm was tested with multiple trials over a varied number of OpenMP threads, input array sizes, and cut-off thresholds (i.e. the sub-array threshold to switch from serial to parallel).

### Quick Sort

Quick sort with a last-index partition was implemented with a serial, tasking, and sections implementation.

### Merge Sort

Merge sort was implemented with a serial, tasking, and section implementation.

### Enumeration Sort

Enumeration sort was implemented with a serial and parallel for implementation, with a limit on array size of 100,000 (due to the poor scaling of this algorithm for larger arrays).

