#include "threads.h"

/*

how to block process
pop from runQ and push into wait Q & Yield only sees runQ

pop from wait Q push into runQ
*/

typedef struct Semaphore {
    int value;
    TCB_t *thread;
} Semaphore;

void InitSem(Semaphore *sem, int value){
    sem->thread = NULL;
    sem->value = value;
}

void P(Semaphore *sem) {

    if ( sem->value > 0){
        sem->value--;
    } else {
        

		struct TCB_t *current = DelQueue(RunQ);
		AddQueue(RunQ, current);
		swapcontext(&(current->context), &(RunQ->head->context));

        P(sem);  
    }
}

void V(Semaphore *sem){
    sem->value++;


    if (sem->value <= 0) {	
		RotateQ(RunQ);
	}

	yield();
}