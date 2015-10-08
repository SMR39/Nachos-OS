/* 
Author: Ishan & Shashi
Description: Program to test threads in Nachos
*/

#include "userlib/syscall.h"
#include "userlib/libnachos.h"


void SimpleThread(int arg)
{   
    int num;
    for (num = 0; num < 5; num++) 
    {
        n_printf("*** thread %d looped %d times\n", arg, num);
        Yield();
    }
}


void ThreadTest()
{   
    int tid;
    tid = threadCreate("smr", SimpleThread); /* Creating a thread */
    n_printf("Entering SimpleTest");
    SimpleThread(2); /* Calling the function with argument 
                                        to distinguish between the threads */
}


int main()
{
	ThreadTest();
	return 0;
}

