/**
 * CSE 330 Assignment 1 Threading using TCB's
 * Travis Delly
 * 1210230252
 * 
*/

#include <unistd.h>
#include "sem.h"

Semaphore *s1;
Semaphore *s2;
Semaphore *s3;

int randomNumber;

void thread1(){
    while( 1 > 0 ){
        randomNumber = rand();
        V(s2);
        V(s3);
        P(s1);
        P(s2);
    }
}

void thread2(){
    while(1 > 0){
        p(s2);
        if(randomNumber % 2 == 0){
            printf("Thread 2 %d\n", randomNumber);

            sleep(1);
        }

        v(s1);
    }
}

void thread3(){
    while(1 > 0){
        p(s2);
        if(randomNumber % 2 != 0){
            printf("Thread 3 %d\n", randomNumber);

            sleep(1);
        }

        v(s1);
    }
}




int main(){
    RunQ = (struct Queue*)malloc (sizeof (struct Queue));
    RunQ->head = NULL;

	s1 = malloc(sizeof(Semaphore));
    s2 = malloc(sizeof(Semaphore));
    s3 = malloc(sizeof(Semaphore));

	InitSem(s1, 0);
	InitSem(s2, 0);
    InitSem(s3, 0);

    start_thread(thread1,1);
    start_thread(thread2,2);
    start_thread(thread3,3);

    run();

    return 1;
}