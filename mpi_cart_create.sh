#!/bin/bash
#SBATCH -o mpi_cart_create.out
#SBATCH --reservation csci4850
#SBATCH -n 12

module load openmpi/gcc/64/1.10.7
rm -f /xfs2/courses/cs/csci4850/princewill.okorie/hpc/mpi_cart_create
mpic++ /xfs2/courses/cs/csci4850/princewill.okorie/hpc/mpi_cart_create.cpp -o /xfs2/courses/cs/csci4850/princewill.okorie/hpc/mpi_cart_create
mpirun /xfs2/courses/cs/csci4850/princewill.okorie/hpc/mpi_cart_create

exit 0
