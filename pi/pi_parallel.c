// The program counts Pi using Leibniz series: sum((-1)^n / (2n + 1)) = Pi / 4; n = 0 : +inf 
// Parallel version
// Compile with -fopenmp

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

#define ITER_CNT 10000

int main(int argc, char** argv) {
	int n, it_part;
    int i;
    int NUM_THREADS = 0;
    if (argc > 1) {
        NUM_THREADS = atoi(argv[1]);
        omp_set_num_threads(NUM_THREADS);
    } else {
        NUM_THREADS = omp_get_num_threads();
    }
    printf("%d\n", NUM_THREADS);

    double* part = (double*)calloc(NUM_THREADS, sizeof(double));
    
	double tic = omp_get_wtime(); 
    #pragma omp parallel private(i, n, it_part)
    {
        n = omp_get_thread_num();
        #pragma omp for 
        for (i = 0; i < ITER_CNT; i++) {
	        part[n] += pow(-1, i) / (2 * i + 1);
            it_part = i;
            int m;
            for (m = 0; m < 1e5; m++){};  // empty cycle to see benefits of parallel program
        } 
        printf("Нить %d закончила %d итерацию, сумма %lf\n", n, it_part, 4 * part[n]);
    }

    double sum = 0;
    for (int i = 0; i < NUM_THREADS + 1; i++) {
        sum += part[i];
    } 
	double pi_appr = sum * 4;
	double toc = omp_get_wtime();
    
    printf("Pi == %lf\ntime == %lf sec\n", pi_appr, toc - tic);
    free(part);
    return 0;
}