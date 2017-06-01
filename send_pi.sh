#!/bin/bash
#SBATCH -J pi_benchmark
#SBATCH -p haswell
#SBATCH --nodes=1
#SBATCH --exclusive
#SBATCH --time=00:00:02

number_threads=12
number_iterations=100

module load perf
export OMP_NUM_THREADS=$number_threads

perf record ./pi 10
# srun ./pi

exit
