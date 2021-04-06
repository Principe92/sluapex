#!/bin/bash
#SBATCH -o mpi_cart_shift.out
#SBATCH --reservation csci4850
#SBATCH -n 12

module load openmpi/gcc/64/1.10.7
rm -f /xfs2/courses/cs/csci4850/princewill.okorie/hpc/mpi_cart_shift
mpic++ /xfs2/courses/cs/csci4850/princewill.okorie/hpc/mpi_cart_shift.cpp -o /xfs2/courses/cs/csci4850/princewill.okorie/hpc/mpi_cart_shift
mpirun /xfs2/courses/cs/csci4850/princewill.okorie/hpc/mpi_cart_shift

exit 0
