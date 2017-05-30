# include <stdio.h>
# include <time.h>
# include "omp.h"

double calculate_pi(int);

int main() {
    int j, iterations = 100;
    double time[iterations];
    double avg, start, end, delta, pi;

    printf("parallel pi calculation benchmark\nexecution time in seconds: ");
    for (j=0; j < iterations; j++){

	    start=omp_get_wtime();
	    ///////////////////////////
	    ////////BENCHMARK//////////
	    pi=calculate_pi(2048);
	    ///////////////////////////
	    end=omp_get_wtime();

	    delta = end - start;
     	    time[j] = delta;
    }

    for (j=0; j<iterations; j++){
        avg+=time[j];
    }
    
    avg=avg/iterations;
    printf("%.15f, and pi is: %f\n", avg, pi);

    return 0;
}

double calculate_pi(int num_steps){

    int i;
    double sum, x, step;
   
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
    return step*sum;
}
