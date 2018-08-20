#!/bin/bash
#SBATCH -J pi_benchmark
#SBATCH -p haswell
#SBATCH --nodes=1
#SBATCH --exclusive
#SBATCH --time=00:02:00
#SBATCH --cpus-per-task=12
#SBATCH --tasks-per-node=1

number_threads=12
number_iterations=100

cd /scratch/s7330426/
cp /home/s7330426/performance/pi ./

#module load perf/r94

export OMP_NUM_THREADS=$number_threads

#perf record -o ./perf.data -e branches,branch-misses,bus-cycles,cache-misses,cache-references,cpu-cycles,instructions,ref-cycles srun ./pi $number_iterations

srun perf record -o ./perf.data ./pi $number_iterations

cp ./perf.data /home/s7330426/performance/

exit
