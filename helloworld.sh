#!/bin/bash
#SBATCH -o helloworld_mpi.out
#SBATCH --reservation csci4850
#SBATCH -n 4

module load openmpi/gcc/64/1.10.7
rm -f /xfs2/courses/cs/csci4850/princewill.okorie/hpc/helloworld_mpi
mpic++ /xfs2/courses/cs/csci4850/princewill.okorie/hpc/helloworld.cpp -o /xfs2/courses/cs/csci4850/princewill.okorie/hpc/helloworld_mpi
mpirun /xfs2/courses/cs/csci4850/princewill.okorie/hpc/helloworld_mpi

exit 0
