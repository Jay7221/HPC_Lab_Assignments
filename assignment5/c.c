// c.c
#include<stdio.h>
#include<omp.h>

int main(){
    int Aryabhatta = 10;
#pragma omp parallel firstprivate(Aryabhatta)
    {
        int thread_id = omp_get_thread_num();
        printf("Thread id: %d, product: %d\n", thread_id, thread_id * Aryabhatta);
    }
    return 0;
}
