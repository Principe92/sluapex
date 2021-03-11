#!/bin/bash
#SBATCH -o pi_mc_mpi.out
#SBATCH --reservation csci4850
#SBATCH -n 32

module load openmpi/gcc/64/1.10.7
rm -f /xfs2/courses/cs/csci4850/princewill.okorie/hpc/week6/pi_mc_mpi
mpic++ /xfs2/courses/cs/csci4850/princewill.okorie/hpc/week6/week6_hw1.cpp -o /xfs2/courses/cs/csci4850/princewill.okorie/hpc/week6/pi_mc_mpi

mpirun -np 1 /xfs2/courses/cs/csci4850/princewill.okorie/hpc/week6/pi_mc_mpi
mpirun -np 2 /xfs2/courses/cs/csci4850/princewill.okorie/hpc/week6/pi_mc_mpi
mpirun -np 4 /xfs2/courses/cs/csci4850/princewill.okorie/hpc/week6/pi_mc_mpi
mpirun -np 8 /xfs2/courses/cs/csci4850/princewill.okorie/hpc/week6/pi_mc_mpi
mpirun -np 16 /xfs2/courses/cs/csci4850/princewill.okorie/hpc/week6/pi_mc_mpi
mpirun -np 32 /xfs2/courses/cs/csci4850/princewill.okorie/hpc/week6/pi_mc_mpi

exit 0
