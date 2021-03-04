#!/bin/bash
#SBATCH -o mpi_p2p_block.out
#SBATCH --reservation csci4850
#SBATCH -n 4

module load openmpi/gcc/64/1.10.7
rm -f /xfs2/courses/cs/csci4850/princewill.okorie/hpc/mpi_p2p_block
mpic++ /xfs2/courses/cs/csci4850/princewill.okorie/hpc/mpi_p2p_block.cpp -o /xfs2/courses/cs/csci4850/princewill.okorie/hpc/mpi_p2p_block
mpirun /xfs2/courses/cs/csci4850/princewill.okorie/hpc/mpi_p2p_block

exit 0
