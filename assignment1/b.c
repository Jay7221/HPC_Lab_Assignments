#include<stdio.h>
#include<omp.h>

int main(){
    int num_threads;
    printf("Enter number of threads:\n");
    scanf("%d", &num_threads);
    omp_set_num_threads(num_threads);
    printf("This is hello from sequential thread %d\n", omp_get_thread_num());
#pragma omp parallel
    {
        printf("Hello from thread %d\n", omp_get_thread_num());
    }
    return 0;
}
