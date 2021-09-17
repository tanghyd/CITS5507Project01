#include <omp.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "random_array.h"
#include "experiments.h"

#define MAX_THREADS 4  // 2**4 = 16
#define TRIALS 5

#define RUN_QUICK_SORT 1
#define RUN_MERGE_SORT 1
#define RUN_ENUM_SORT 1

int main(void)
{
    // // disable dynamic thread teams
    omp_set_dynamic(0);

    // random seed init -- call only once
    srand(time(NULL));
    // srand(42);

    // test run    
    // int n_arrays = 1;
    // int n_cutoffs = 1;
    // int ARRAY_SIZES[1] = {10000000};
    // int CUT_OFFS[1] = {100};

    // full run
    int n_arrays = 9;
    int n_cutoffs = 2;
    int ARRAY_SIZES[9] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000, 10000000};
    int CUT_OFFS[2] = {0, 100};  // min array size to run parallelism

    int size;
    int cutoff;

    // output .csv to save experiment runtime results
    FILE *fptr;
    char file_name[] = "results/results.csv";

    double run_start = omp_get_wtime();
    fptr = fopen(file_name, "a");
    if (fptr)
    {  
        // headers
        // fprintf(fptr, "algorithm,construct,threads,size,cutoff,duration\n");

        for (int s = 0; s < n_arrays; s++)
        {
            size = ARRAY_SIZES[s];
            
            // static memory array
            // double random_arr[ARRAY_SIZE];  // randomly generated array
            // double arr[ARRAY_SIZE];  // array to sort copied from random array
            // double temp[ARRAY_SIZE]; // workspace array for merge/enumeration sort

            // dynamic memory array
            double *random_arr = malloc(size * sizeof(double));
            double *arr = malloc(size * sizeof(double));
            double *temp = malloc(size * sizeof(double));
            
            // build array of random doubles in [0, 1]
            fill_double_array(random_arr, size);

            // print_double_array(random_arr, 0, 5);
            // print_double_array(random_arr, size-5, size);

            printf("Trials: %d\n", TRIALS);
            printf("\nSerial:\n");

            for (int i=0; i < TRIALS; i++)
            {
                // SERIAL
                printf("\nTrial %d:\n", i);
                cutoff = 0;
                
                if (RUN_QUICK_SORT)
                {
                    // copy array and write quick sort serial results
                    copy_double_array(random_arr, arr, size);
                    fprintf(
                        fptr, "quick,serial,%d,%d,%d,%.17g\n",
                        1, size, cutoff, time_quick_sort_serial(arr, size)
                    );
                }
                
                if (RUN_MERGE_SORT)
                {
                    // merge sort serial
                    reset_double_array(temp, size);  // reset to 0
                    copy_double_array(random_arr, arr, size);
                    fprintf(
                        fptr, "merge,serial,%d,%d,%d,%.17g\n",
                        1, size, cutoff, time_merge_sort_serial(arr, temp, size)
                    );  
                }

                // ENUMERATION SORT
                
                // Enumeration sort not viable for arrays bigger than the stack
                if (size <= 100000 && RUN_ENUM_SORT)
                {   
                    // enumeration sort serial
                    reset_double_array(temp, size);  // reset to 0
                    copy_double_array(random_arr, arr, size);
                    fprintf(
                        fptr, "enumeration,serial,%d,%d,%d,%.17g\n",
                        1, size, cutoff, time_enumeration_sort_serial(arr, temp, size)
                    );
                }
            }

            // loop through each thread
            for (int n = 1; n < MAX_THREADS+1; n++)
            {
                int num_threads = (int)pow(2,n);  // 2, 4, 8, 16
                omp_set_num_threads(num_threads);
                printf("\nOpenMP Threads: %d\n", omp_get_max_threads());

                // loop through each hybrid cutoff setting
                for (int c = 0; c < n_cutoffs; c++)
                {
                    cutoff = CUT_OFFS[c];
                    printf("Array Size: %d | ", size);
                    printf("Cutoff Size: %d | ", cutoff);

                    // loop through experiments n=TRIALS times
                    for (int i=0; i < TRIALS; i++)
                    {
                        printf("\nTrial %d:\n", i);

                        if (RUN_QUICK_SORT)
                        {
                            // parallel quick sort - tasks
                            copy_double_array(random_arr, arr, size);
                            fprintf(
                                fptr, "quick,tasks,%d,%d,%d,%.17g\n",
                                num_threads, size, cutoff, time_quick_sort_tasks(arr, size, cutoff)
                            );


                            // parallel quick sort - sections
                            copy_double_array(random_arr, arr, size);
                            fprintf(
                                fptr, "quick,sections,%d,%d,%d,%.17g\n",
                                num_threads, size, cutoff, time_quick_sort_sections(arr, size, cutoff)
                            );
                        }


                        // MERGE SORT

                        if (RUN_MERGE_SORT)
                        {
                            // parallel merge sort - tasks
                            reset_double_array(temp, size);  // reset to 0
                            copy_double_array(random_arr, arr, size);
                            fprintf(
                                fptr, "merge,tasks,%d,%d,%d,%.17g\n",
                                num_threads, size, cutoff, time_merge_sort_tasks(arr, temp, size, cutoff)
                            );

                            // parallel sections merge sort
                            reset_double_array(temp, size);  // reset to 0
                            copy_double_array(random_arr, arr, size);
                            fprintf(
                                fptr, "merge,sections,%d,%d,%d,%.17g\n",
                                num_threads, size, cutoff, time_merge_sort_sections(arr, temp, size, cutoff)
                            );
                        }

                        // ENUMERATION SORT
                        
                        // Enumeration sort not viable for arrays bigger than the stack
                        if (size <= 100000 && RUN_ENUM_SORT)
                        {   
                            // enumeration sort parallel
                            reset_double_array(temp, size);  // reset to 0
                            copy_double_array(random_arr, arr, size);
                            fprintf(
                                fptr, "enumeration,parallel,%d,%d,%d,%.17g\n",
                                num_threads, size, cutoff, time_enumeration_sort_parallel(arr, temp, size)
                            );
                        }
                    }
                }
            }

            // free memory as we remake arrays with new size
            free(temp);
            free(arr);
            free(random_arr);
        }
    }
    else
    {
        printf("Failed to open file\n");
    }
    fclose(fptr);

    double run_end = omp_get_wtime();
    printf("\nAll experiments completed in %.17gs.\n", run_end - run_start);

    return 0;
}