/**
 * CSE 330 Assignment 1 Threading using TCB's
 * Travis Delly
 * 1210230252
 * 
*/

#include <unistd.h>
#include "sem.h"

Semaphore *empty;
Semaphore *full;


int buffer[5];

int in = 0;
int out = 0;

void producer(){
    while(1 > 0){
        P(empty);
		
		buffer[in] = rand();
		
		printf("Produced: %i\nBuffer[%d]\n", buffer[in], in);
		
		sleep(1);
		
		in = (in+1) % 5;
		
		V(full);
    }
}

void consumer (){
    while(1 > 0){
        P(full);
		
		printf("Consumed: %i\nBuffer[%d]\n", buffer[out], out);
		
		buffer[out] = -1;
		
		sleep(1);
		
		out = (out+1) % 5;
		
		V(empty);
    }
}


int main(){
    RunQ = (struct Queue*)malloc (sizeof (struct Queue));
    RunQ->head = NULL;

	full = malloc(sizeof(Semaphore));
	empty = malloc(sizeof(Semaphore));

	InitSem(full, 0);
	InitSem(empty, 5);

    start_thread(consumer,1);
    start_thread(producer,2);
    start_thread(consumer,3);
    start_thread(consumer,4);
    start_thread(consumer,5);
    run();

    return 1;
}