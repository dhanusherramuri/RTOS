#include<pthread.h>
#include<stdlib.h>
#include <stdio.h>

#define N 3

static void *square (void *arg){
    int n = *(int *)arg;
    int *result = malloc(sizeof *result);
    // printf("\nWorker got ID : %d\n",id);
    *result = n * n;
    return result;
}

int main(void){
    pthread_t tid;
    int input = 7;
    void *ret;

    pthread_create(&tid,NULL,square,&input);

    printf("Squared = %d\n", *(int *)ret);
    free(ret);
    return 0;

}