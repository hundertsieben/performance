#!/bin/bash
#SBATCH -J pi_benchmark
#SBATCH -p haswell
#SBATCH --nodes=1
#SBATCH --exclusive
#SBATCH --time=00:02:00

number_threads=12
number_iterations=100

module load perf/r94
export OMP_NUM_THREADS=$number_threads

srun ./pi $number_iterations

exit
