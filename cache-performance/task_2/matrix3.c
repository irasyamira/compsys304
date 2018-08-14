/* do not add other includes */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

double getTime() {
	struct timeval t;
	double sec, msec;

	while (gettimeofday(&t, NULL) != 0);
	sec = t.tv_sec;
	msec = t.tv_usec;

	sec = sec + msec/1000000.0;
  
  return sec;
}

int main (int argc, char *argv[])
{
	double t1, t2; 

	/* variables for task 2 */
	unsigned int N = 1000; 
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int k = 0;
	unsigned int kk = 0;
	unsigned int jj = 0;
	unsigned int max_j = 0;
	unsigned int max_k = 0;
	unsigned int cache_line = 32;

	/* declare variables; examples, adjust for task */
	double *a,*b,*c;
	double sum_ab = 0.0;

	/* allocate memory for arrays; examples, adjust for task */
	a = malloc(N*N*sizeof(double));
	b = malloc(N*N*sizeof(double));
	c = malloc(N*N*sizeof(double));

	// Initialise array a with current value of i
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			*(a + i*N + j) = i;
		}
	}

	// Initialise array b with current value of i
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			*(b + i*N + j) = i;
		}
	}
	
	kk = 0;
	jj = 0;
	t1 = getTime();
	/* code to be measured goes here */
	/***************************************/
	while (kk < N) {
		while (jj < N) {
			for (i = 0; i < N; i++) {
				if((jj + cache_line) < N) {
				  max_j = jj + cache_line;
				} else {
				  max_j = N;
				}
				for (j = jj; j < max_j; j++) {
					if((kk + cache_line) < N) {
						max_k = kk + cache_line;
					} else{
						max_k = N;
					}
					sum_ab = 0.0;
					for (k = kk; k < max_k; k++) {
						sum_ab = sum_ab + *(a + i*N + k) * *(b + k*N + j);
					}
					*(c + i*N + j) = sum_ab;
				}
			}
			// Increment jj count by cache_line size (move on to next block)
			jj = jj + cache_line;
		}
		// Increment kk count by cache_line size (move on to next block)
		kk = kk + cache_line;
	}
	/***************************************/
	t2 = getTime(); 

	/* output; examples, adjust for task */
	printf("Time: %6.2f secs\n",(t2 - t1));
	printf("Sum: %d\n", sum_ab);

	/* free memory; examples, adjust for task */
	free(a);
	free(b);
	free(c);

	return 0;  
}
