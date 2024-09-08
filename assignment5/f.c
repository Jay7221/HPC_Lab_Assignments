// f.c
#include<stdio.h>
#include<omp.h>

void printSeries(int x, int n){
    for(int i = 1; i <= n; ++i){
        printf("%d. Thread: %d, Series of %d: %d\n", i, omp_get_thread_num(), x, x * i);
    }
}

int main(){
    int n = 10;
#pragma omp parallel
    {
#pragma omp single nowait
        {
            printSeries(2, n);
        }
#pragma omp single nowait
        {
            printSeries(4, n);
        }
    }
    return 0;
}
