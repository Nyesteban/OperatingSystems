#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long int x = 0;

pthread_barrier_t bar;

void * thread(void *arg)
{
	  printf("Thread %d waiting for the barrier.\n", (int)arg);
	    
	    pthread_barrier_wait(&bar);
	      
	        printf("Thread %d passed the barrier.\n", (int)arg);
	           
	    
	             return 0;
	             }
	    
	             int
	             main (int argc, char **argv)
	             {
	               int n, m;
	                 
	                   n = atoi(argv[1]);
	    
	                    m = atoi(argv[2]);
	    
	                       pthread_barrier_init(&bar, 0, m);
	                         
	                           pthread_t *t;
	                             
	                               t = malloc(n * sizeof(pthread_t));
	    
	                                 int i;
	                                   
	                                     for (i = 0; i < n; i++)
	                                       {
	                                           pthread_create(&t[i], 0, thread, (void *)i);
	                                             }
	    
	                                               for (i = 0; i < n; i++)
	                                                 {
	                                                     pthread_join(t[i], 0);
	                                                       }
	                                                         
	                                                           pthread_barrier_destroy(&bar);
	    
	                                                             return 0;
	                                                             }
