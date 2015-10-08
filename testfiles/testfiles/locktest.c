/* 
Author: Ishan & Shashi
Description: A Program for testing the locks 
*/

#include "userlib/syscall.h"
#include "userlib/libnachos.h"

int num=0,x=1;
int lock;
int tid1,tid2,tid3;

void test1()
    {    
    	LockAcquire(lock);	/*Acquiring the lock by this thread*/
        x=10;
	n_printf("\n value of x inside test1 is %d", x);  
		
	Join(tid2);
    }

void test2()
    {   
	n_printf("\n value of x inside test2 is %d", x);
	LockRelease(lock);   /*releasing the lock by the other thread 
	            but eventually it will fail to do so since he is not the owner of the lock*/
    	x=20;
	    
    }

void test3()
    {   
	    n_printf("\n value of x inside test3 is %d", x);
     	LockAcquire(lock);
	    x=30;
	
    }

int main()
{
	lock = LockCreate("lock");
	tid1 = threadCreate("test1", test1);
    tid2 = threadCreate("test2", test2);
	tid3 = threadCreate("test3", test3);
	n_printf("value of shared var x in main is %d",x);
	return 0;

}
