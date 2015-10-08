/* 
Author: Ishan & Shashi
Description: A Program for simple producer/consumer using semaphores and threads 
*/
 
#include <libnachos.h>
#include <syscall.h>

/* For Two threads */
void Producer();  
void Consumer();

int data;             
int numRun;
int empty,full,mutex,pid,cid;

int main() {

  numRun = 5;
  empty = SemCreate("emptybuf",1);  /* initializing value of emptybuf */
  full = SemCreate("fulbuf",0);     /* initializing value of fullbuf */
  mutex = SemCreate("mutexuf",1);   /* initializing value of mutex */

  n_printf("main started\n");
  pid = threadCreate("Prods", Producer); /* Creating a thread for producer*/
  cid = threadCreate("Cons", Consumer);  /* Creating a thread for consumer*/
  n_printf("main done\n");
  return 0;
}

/* Producing 1 to numRun into the data buffer */
void Producer() {
  int produced;
  n_printf("Producer created\n");
  for (produced = 0; produced < numRun; produced++) {
    P(empty);
    P(mutex);           /* Protecting the shared variable using semaphores*/
    data = produced;
    V(mutex);
    V(full);
  }
}

/* Consuming numRun items from the buffer and giving out the sum */
void Consumer() {
  int total = 0, consumed;
  n_printf("Consumer created\n");
  for (consumed = 0; consumed < numRun; consumed++) {
    P(full);
    P(mutex);
    total = total+data;    /* Protecting the shared variable using semaphores*/
    V(mutex);
    V(empty);
  }
  n_printf("for %d iterations, the total is %d\n", numRun, total);
}
