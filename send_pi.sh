#!/bin/bash
#SBATCH -J pi_benchmark
#SBATCH -p haswell
#SBATCH --nodes=1
#SBATCH --exclusive
#SBATCH --time=00:00:02

number_threads=12
number_iterations=100
i=0


module load gprof
export BG_GMON_START_THREAD_TIMERS="all"
export OMP_NUM_THREADS=$number_threads


while [ $i -le $number_iterations ]; do
    gprof srun ./pi gprof > pi.stat
    let i=i+1 
done

exit
