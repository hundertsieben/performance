// Pi is calculated with numerical integration. The algorithm was
// copied from
// http://www.appentra.com/parallel-computation-pi/
//
// author: Nora Marcus (nora_lynn.marcus@tu-dresden.de) 

#include <stdio.h>
#include <time.h>
#include "omp.h"
#include <inttypes.h>
#include <string.h>
#include <iostream>
#include <iomanip>

double calculate_pi(int);

int main( int argc, char *argv[] ) {

#ifdef _OPENMP
   std::cout << "Parallel calculation of pi using " << omp_get_max_threads() << " threads.\n";
   #pragma omp parallel
     if (omp_get_thread_num()==0)
       std::cout << "Use " << omp_get_num_threads() << " threads.\n";
#else
   std::cout << "Sequential calculation of pi.\n";
#endif
 
    double pi;
    int iterations=0;

    //int l = strlen(argv[1]);
 
    iterations = atoi(argv[1]);    

    for (int i=0; i<iterations; ++i){
            ///////////////////////////
            ////////BENCHMARK//////////
            pi=calculate_pi(9999999);
            ///////////////////////////
    }

    std::cout << "pi is " << std::fixed << std::setprecision(9) << pi << "\n";
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

