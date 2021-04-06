#!/bin/bash
#SBATCH -o mpi_type_vector.out
#SBATCH --reservation csci4850
#SBATCH -n 2

module load openmpi/gcc/64/1.10.7
rm -f /xfs2/courses/cs/csci4850/princewill.okorie/hpc/mpi_type_vector
mpic++ /xfs2/courses/cs/csci4850/princewill.okorie/hpc/mpi_type_vector.cpp -o /xfs2/courses/cs/csci4850/princewill.okorie/hpc/mpi_type_vector
mpirun /xfs2/courses/cs/csci4850/princewill.okorie/hpc/mpi_type_vector

exit 0
