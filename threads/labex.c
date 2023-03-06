#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


typedef struct
{
	  int a;
	    
	    int b;
} thread_arg;

typedef struct
{
	  int sum;
	    
	    int prod;
} thread_ret;

void * thread(void *arg)
{
	  thread_arg a;
	    
	    a = *(thread_arg *)arg;

	      printf("%d %d Random message.\n", a.a, a.b);

	        thread_ret *r; 
		  
		  r = malloc(sizeof(thread_ret));
		    
		    r->sum = a.a + a.b;
		      
		      r->prod = a.a * a.b;

		        free(arg);

			  return (void *)r;
}

int main (int argc, char **argv)
{
	  int n;
	    
	    n = atoi(argv[1]);
	      
	      pthread_t *t;
	        
	        t = malloc(n * sizeof(pthread_t));

		  thread_ret **r;
		    
		    r = malloc(n * sizeof(thread_ret*));

		      int i;
		        
		        for (i = 0; i < n; i++)
				  {
					      thread_arg *a;
					          
					          a = malloc(sizeof(thread_arg));
						      
						      a->a = i;
						          
						          a->b = 5 * i - 7;
							    
							      pthread_create(&t[i], 0, thread, (void *)a);
							        }

			  for (i = 0; i < n; i++)
				    {
					        pthread_join(t[i], (void *)&r[i]);
						  }

			    free(t);

			      for (i = 0; i < n; i++)
				        {
						    printf("%d %d\n", r[i]->sum, r[i]->prod);
						        free(r[i]);
							  }

			        free(r);
				  return 0;
}
