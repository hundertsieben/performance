# include <stdio.h>
# include <time.h>
# include "omp.h"

double calculate_pi(int);

int main() {
    int j, iterations = 100;
    double pi;

    printf("parallel pi calculation benchmark\n");
    for (j=0; j < iterations; j++){

            ///////////////////////////
            ////////BENCHMARK//////////
            pi=calculate_pi(9999999);
            ///////////////////////////

    }

    printf("pi is: %f\n", pi);
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

