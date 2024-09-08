// b.c
#include<stdio.h>
#include<omp.h>

int main(){
    int sum = 0;
#pragma omp parallel reduction(+:sum)
    {
        int thread_id = omp_get_thread_num();
        printf("Thread id: %d, square: %d\n", thread_id, thread_id * thread_id);
        sum += thread_id * thread_id;
    }
    printf("Sum of square of thread id's: %d\n", sum);
    return 0;
}
