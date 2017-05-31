// Pi is calculated with numerical integration. The algorithm was
// copied from
// http://www.appentra.com/parallel-computation-pi/
//
// author: Nora Marcus (nora_lynn.marcus@tu-dresden.de) 

# include <stdio.h>
# include <time.h>
# include "omp.h"
# include <gmon.h>


double calculate_pi(int);
extern int isgprof;

int main( int argc, char *argv[] ) {
    double pi;
    int i;

    for (i=0; i<argc; i=i+1){
        if (argv[i]=="gprof"){
            isgprof = 1;
        }
        else{
            isgprof = 0;
        }
    }

    if(isgprof){
        gmon_start_all_thread_timers();
    }

    printf("parallel pi calculation benchmark\n");

            ///////////////////////////
            ////////BENCHMARK//////////
            pi=calculate_pi(9999999);
            ///////////////////////////


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

        if(isgprof){
            gmon_thread_timer(1);
        }

        #pragma omp for reduction(+:sum) schedule(static)
        for (i=0; i<num_steps; i=i+1){
            x=(i+0.5)*step;
            sum = sum + 4.0/(1.0+x*x);
        }
        
        if(isgprof){ 
            gmon_thread_timer(0);
        }
    }
    return step*sum;
}

