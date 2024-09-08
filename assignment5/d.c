// d.c
#include<stdio.h>
#include<omp.h>

int main(){
    int n = 20;
    int sum = 0;
#pragma omp parallel for reduction(+:sum)
    for(int i = 1; i <= n; ++i){
        sum += i;
    }
    printf("The sum of first %d natural numbers is %d\n", n, sum);
    return 0;
}
