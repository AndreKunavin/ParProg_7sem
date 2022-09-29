// The program counts Pi using Leibniz series: sum((-1)^n / (2n + 1)) = Pi / 4 
// Compile with -fopenmp

#include <stdio.h>
#include <math.h>
#include <omp.h>

#define ITER_CNT 10000
int main(int argc, char** argv) {
	int i;
	double sum = 0;
	double tic = omp_get_wtime(); 
	for (i = 0; i < ITER_CNT; i++)
	{
		sum += pow(-1, i) / (2 * i + 1); 
		int m;
		for (m = 0; m < 1e5; m++){};	// empty cycle to see benefits of parallel program
	}
	double toc = omp_get_wtime();
	double pi_appr = sum * 4;
	printf("Pi == %lf\ntime == %lf\n", pi_appr, toc - tic);

	printf("%ld\n", sizeof(size_t));
}
