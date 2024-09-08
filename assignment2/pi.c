#include<stdio.h>
#include<omp.h>

#define NUM_THREADS 4

int main(){
    // To calculate pi, we numerically integrate (4 / (1 + x * x)) 0 to 1
    static long num_steps = 10000000000;
    double step = 1.0 / (double)num_steps;
    double pi = 0;

    double start = omp_get_wtime();

#pragma omp parallel for reduction(+:pi) num_threads(NUM_THREADS) 
    for(long i = 0; i < num_steps; ++i){
        // Calculate the midpoint of ith strip
        double x = (i + 0.5) * step;
        double y = 4.0 / (1 + x * x);
        pi += y * step;
    }

    double end = omp_get_wtime();
    
    printf("Value of pi: %f\n", pi);
    printf("Time taken: %f\n", end - start);
    return 0;
}
