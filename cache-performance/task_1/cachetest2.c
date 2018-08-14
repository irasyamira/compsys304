/* do not add other includes */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

double getTime(){
  struct timeval t;
  double sec, msec;
  
  while (gettimeofday(&t, NULL) != 0);
  sec = t.tv_sec;
  msec = t.tv_usec;
  
  sec = sec + msec/1000000.0;
  
  return sec;
}
 
/* for task 1 only */
void usage(void)
{
	fprintf(stderr, "Usage: cachetest1/2 [--repetitions M] [--array_size N]\n");
	exit(1);
}

int main (int argc, char *argv[])
{

	unsigned int N_array[11] = {8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608};
	unsigned int M_array[11] = {10000,10000,10000,10000,10000,5000,5000,2000,2000,1000,500};
	unsigned int N = 0;
	unsigned int M = 0;
	
	/* variables for task 1 */
	double t1 = 0.0;
	double t2 = 0.0; 
	unsigned int i = 0;
	unsigned int j = 0;
	long x = 0;
	
	/* declare variables; examples, adjust for task */
	int *a, *b, *temp;
	double sum_array = 0.0;
			
	for (int k = 0; k < 11; k++) {
		N = N_array[k];
		M = M_array[k];	

		/* parameter parsing task 1 */
		for (i = 1; i < (unsigned)argc; i++) {
			if (strcmp(argv[i], "--repetitions") == 0) {
				i++;
				if (i < argc)
					sscanf(argv[i], "%u", &M);
				else
					usage();
			} else if (strcmp(argv[i], "--array_size") == 0) {
				i++;
				if (i < argc)
					sscanf(argv[i], "%u", &N);
				else
					usage();
			} else 
				usage();
		}

		
		/* allocate memory for arrays; examples, adjust for task */
		a = malloc(N*sizeof(int));
		b = malloc(N*sizeof(int));
		
		/* initialise arrray elements */
		for (i = 0; i < N; i++){
			a[i] = i;
		}
		for (i = 0; i < N; i++){
			b[i] = i;
		}
		for (i = 0; i < N; i++){
			// Generate a random index number that does not exceed N
			x = (rand()*rand()) % N;
			// Swapping
			temp = b[i];
			b[i] = b[x];
			b[x] = temp;
		}
		
		t1 = getTime();
		/* code to be measured goes here */
		/***************************************/
		for (i = 0; i < M; i++){
			for (j = 0; j < N; j++){
				sum_array += a[b[j]];
			}
		}	
		/***************************************/
		t2 = getTime(); 
		
		/* output; examples, adjust for task */
		printf("time: %6.2f secs\n",(t2 - t1));
		printf("Sum: %d\n",sum_array);
		printf("k: %d N: %d and M: %d\n",k,N,M);
		printf("Time per iteration: %6.9f ns\n", 1000000000*((t2-t1)/(N*M)));
		
		/* IMPORTANT: also print the result of the code, e.g. the sum_array, 
		 * otherwise compiler might optimise away the code */
	  
		/* free memory; examples, adjust for task */
		free(a);
		free(b);
	}	
	return 0;  
}
