# include <stdio.h>
# include <time.h>
# include "omp.h"

int main() {
    
    int i, num_steps;
    double sum, x, step, pi;
    
    int j, iterations = 100;
    double time[iterations];
    double avg, start, end, delta;

    num_steps=3;

    printf("parallel pi digits calculation benchmark\nexecution time in seconds: ");
    for (j=0; j < iterations; j++){
	    start=omp_get_wtime();
	    ///////////////////////////
	    ////////BENCHMARK//////////
	    x=0;
            sum = 0.0;
            step = 1.0/(double)num_steps;
            #pragma omp parallel private(i,x) 
            {
            #pragma omp for reduction(+:sum) schedule(static)
            for (i=0; i<num_steps; i=i+1){
            x=(i+0.5)*step;
            sum = sum + 4.0/(1.0+x*x);
            }
            }
            pi=step*sum;
	    ///////////////////////////
	    end=omp_get_wtime();

	    delta = end - start;
     	    time[j] = delta;
    }

    for (j=0; j<iterations; j++){
        avg+=time[j];
    }

    avg=avg/iterations;
    printf("%f\n", avg);

    return 0;
}


