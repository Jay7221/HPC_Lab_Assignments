// a.c
#include<stdio.h>
#include<omp.h>

int main(){
    char* family[] = {"Jay", "Ajay", "Vijay", "Sunita", "Nitin", "Suhas"};
    int n = sizeof(family) / sizeof(family[0]);
#pragma omp parallel num_threads(n)
    {
        int thread_id = omp_get_thread_num();
        printf("Thread: %d, Family member: %s\n", thread_id, family[thread_id]);
    }
    return 0;
}
