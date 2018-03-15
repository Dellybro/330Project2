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

void P(Semaphore *v) {

    if ( v->value > 0){
        v->value--;
    } else {
        

		struct TCB_t *current = DelQueue(RunQ);
		AddQueue(RunQ, current);
		swapcontext(&(current->context), &(RunQ->head->context));

        P(v);  
    }
}

void V(Semaphore *v){
    v->value++;


    if (v->value <= 0) 
	{	
		RotateQ(RunQ);
	}
	yield();
}