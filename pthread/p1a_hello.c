#include<pthread.h>
#include<stdio.h>

static void *hello(void *args){
    (void)args;
    printf("Hello from the new thread\n");
    return NULL;
}

int main(void){
    pthread_t tid;
    pthread_create(&tid, NULL, hello, NULL);
    pthread_join(tid, NULL);

    printf("Thread Finished, main exists\n");
    return 0;
}