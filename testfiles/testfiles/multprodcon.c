/* 
Author: Ishan & Shashi
Description: A Program for multiple producer/consumer using semaphores and threads 
*/

#include <userlib/libnachos.h>
#include <userlib/syscall.h>
#define BUF_SIZE 3
#define NUM_TRANSACTIONS 4
#define NUM_PROD 2
#define NUM_CONS 2

int buffer[BUF_SIZE];
int n = 0;
static int prod_num=1; /* global variable to check the particular producer and consumer*/
int empty = 0;


int prod, cons, mutex; /* Creating three semaphores*/


void produce(int x) /* Producing the data */
{
	P(prod);
	P(mutex);
	n_printf("\n produce %d",x);
	buffer[empty] = x;
	empty = (empty+1)%BUF_SIZE;
	n++;
	V(mutex);
	V(cons);
}

void consume()   /* consuming the data */
{
	P(cons);
	P(mutex);
	n_printf("\n Consume %d",buffer[(BUF_SIZE + empty - n) % BUF_SIZE]);
	n--;
	V(mutex);
	V(prod);
}

int producer(int arg) /* Producer */
{
	int i;
	for(i=0;i<NUM_TRANSACTIONS;i++)
		produce(i+10*prod_num); /* number to distinguish the producers from each other */
	return 0;
}

int consumer(int arg)/* Consumer */
{
	int i;
	for(i=0;i<NUM_TRANSACTIONS;i++)
		consume();
	return 0;
}

int main()
{
    /* Creating the three sempahores */
	prod = SemCreate("prod",BUF_SIZE);
	cons = SemCreate("cons",0);
	mutex = SemCreate("crit",1);

	int tid[NUM_PROD+NUM_CONS];

	int i,j;
	//create producers
	for(i=0;i<NUM_PROD;i++)
	{
		
		tid[i] = threadCreate("Producer", producer);
		prod_num++;
	}
	//create consumers
	for(j=0;j<NUM_CONS;j++)
	{
		tid[i+j] = threadCreate("Consumer", consumer);
		
	}
	
	//join producers and consumers
	for(i=0;i<NUM_PROD+NUM_CONS;i++)
	{
		Join(tid[i]);
	}
	return 0;
	SemDestroy(prod);
	SemDestroy(cons);
	SemDestroy(mutex);
}
