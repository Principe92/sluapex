#!/bin/bash
#SBATCH -o mpi_collective_allgather.out
#SBATCH --reservation csci4850
#SBATCH -n 4

module load openmpi/gcc/64/1.10.7
rm -f /xfs2/courses/cs/csci4850/princewill.okorie/hpc/mpi_collective_allgather
mpic++ /xfs2/courses/cs/csci4850/princewill.okorie/hpc/mpi_collective_allgather.cpp -o /xfs2/courses/cs/csci4850/princewill.okorie/hpc/mpi_collective_allgather
mpirun /xfs2/courses/cs/csci4850/princewill.okorie/hpc/mpi_collective_allgather

exit 0
