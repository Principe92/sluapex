#!/bin/bash
#SBATCH -o mpi_comm_split.out
#SBATCH --reservation csci4850
#SBATCH -n 12

module load openmpi/gcc/64/1.10.7
rm -f /xfs2/courses/cs/csci4850/princewill.okorie/hpc/mpi_comm_split
mpic++ /xfs2/courses/cs/csci4850/princewill.okorie/hpc/mpi_comm_split.cpp -o /xfs2/courses/cs/csci4850/princewill.okorie/hpc/mpi_comm_split
mpirun /xfs2/courses/cs/csci4850/princewill.okorie/hpc/mpi_comm_split

exit 0
