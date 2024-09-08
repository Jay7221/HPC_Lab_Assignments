#include<stdio.h>
#include<omp.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int count = 0;          // Current number of items in buffer
int in = 0;             // Index where the next produced item will go
int out = 0;            // Index where the next consumed item will come from

int produce_item(){
    static int item = 0;
    return ++item;
}

int consume_item(int item){
    printf("Item consumed: %d\n", item);
}

omp_lock_t lock;

void producer(){
    while(1){
        int item = produce_item();

        omp_set_lock(&lock);

        while(count == BUFFER_SIZE){
            omp_unset_lock(&lock);
#pragma omp flush(count)
            omp_set_lock(&lock);
        }

        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        ++count;

        omp_unset_lock(&lock);
    }
}

void consumer(){
    while(1){
        int item;

        omp_set_lock(&lock);

        while(count == 0){
            omp_unset_lock(&lock);
#pragma omp flush(count)
            omp_set_lock(&lock);
        }

        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        --count;
        consume_item(item);

        omp_unset_lock(&lock);
    }
}

int main(){

    omp_init_lock(&lock);

#pragma omp parallel
    {
#pragma omp single nowait
        {
            producer();
        }

#pragma omp single nowait
        {
            consumer();
        }
    }

    omp_destroy_lock(&lock);

    return 0;
}
