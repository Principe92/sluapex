#!/bin/bash
#SBATCH -o mpi_collective_sum.out
#SBATCH --reservation csci4850
#SBATCH -n 4

module load openmpi/gcc/64/1.10.7
rm -f /xfs2/courses/cs/csci4850/princewill.okorie/hpc/mpi_collective_sum
mpic++ /xfs2/courses/cs/csci4850/princewill.okorie/hpc/mpi_collective_sum.cpp -o /xfs2/courses/cs/csci4850/princewill.okorie/hpc/mpi_collective_sum
mpirun /xfs2/courses/cs/csci4850/princewill.okorie/hpc/mpi_collective_sum

exit 0
