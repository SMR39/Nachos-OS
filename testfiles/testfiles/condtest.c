/* 
Author: Ishan & Shashi
Description: A Program for testing the conditions wait and broadcast 
*/

#include "userlib/syscall.h"
#include "userlib/libnachos.h"

int num=0,y=1;
int cond;
int tid1,tid2,tid3;

void test1()
   {
	n_printf("\n Inside the first test now waiting for test3 to give latest value of y \n");
        CondWait(cond);/*Waiting for the signal*/
        y=y+20;
        n_printf("\n Test 1 is not waiting now and value of y is %d",y);
   }

void test2()
   {
        n_printf("\n Inside the second test now waiting for test3 to give latest value of y \n");
        CondWait(cond);/*Waiting for the signal*/
	y=y+10;
        n_printf("\n Test 2 is not waiting now and value of y is %d",y);

   }

void test3()
    {
    	n_printf("\n Test3 : Broadcasting");
    	CondBroadcast(cond);/*Signalling all the threads waiting in the waitqueue*/
	y+=10;
   	n_printf("\n value of x inside Test3 is %d", y);
    }

int main()
{

    cond = CondCreate("cond");
    tid1 = threadCreate("test1", test1);
    tid2 = threadCreate("test2", test2);
    tid3 = threadCreate("test3", test3);

    return 0;
}
