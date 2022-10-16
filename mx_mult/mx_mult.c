#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include "mx.h"


int main(int argc, char* argv[]) 
{    
    int NUM_THREADS = 0;
    if (argc > 1) {
        NUM_THREADS = atoi(argv[1]);
        omp_set_num_threads(NUM_THREADS);
    } else {
        NUM_THREADS = omp_get_num_threads() + 1;
    }
    //printf("%d\n", NUM_THREADS);

    srand(time(0));
    int rows_a = 1000;
    int rows_b = 1000;
    int columns = 1000;
    int** A = rand_mx(rows_a, columns);
    int** B = rand_mx(rows_b, columns);
    int** C = alloc_mx(rows_a, rows_b);

    int** B_t = transpose(B, rows_b, columns);
    
    // let's count A * B^T
    
    double tic = omp_get_wtime(); 

    #pragma omp parallel 
    {   
        /* A * B - slow bacause here we don't use cache wisely
        #pragma omp for 
        for (int i = 0; i < columns; i++) {
            for (int j = 0; j < columns; j++) {
                for (int k = 0; k < columns; k++) {
                    C[i][j] += A[i][k] * B[k][j];    
                }
            }
        }
        */
	// fast - A * B^T
        #pragma omp for
        for (int i = 0; i < rows_a; i++) {
            for (int j = 0; j < rows_b; j++) {
                C[i][j] = scalar_product(A[i], B[j], columns);
            }
        }
             
    }

    double toc = omp_get_wtime();
    
    printf("time == %lf sec\n", toc - tic);
    
    /*
        print_mx(A, rows_a, columns);
        print_mx(B_t, columns, rows_b);
        print_mx(C, rows_a, rows_b);
    */
    
    free_mx(B_t, columns);
    free_mx(A, rows_a);
    free_mx(B, rows_b);
    free_mx(C, rows_a);
    
    return 0;
}
