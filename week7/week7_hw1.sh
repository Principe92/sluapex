#!/bin/bash
#SBATCH -o week7_hw1.out
#SBATCH --reservation csci4850
#SBATCH -n 32

module load openmpi/gcc/64/1.10.7
rm -f /xfs2/courses/cs/csci4850/princewill.okorie/hpc/week7/week7_hw1
mpic++ /xfs2/courses/cs/csci4850/princewill.okorie/hpc/week7/week7_hw1.cpp -o /xfs2/courses/cs/csci4850/princewill.okorie/hpc/week7/week7_hw1

mpirun -np 2 /xfs2/courses/cs/csci4850/princewill.okorie/hpc/week7/week7_hw1 500000000
mpirun -np 4 /xfs2/courses/cs/csci4850/princewill.okorie/hpc/week7/week7_hw1 500000000
mpirun -np 8 /xfs2/courses/cs/csci4850/princewill.okorie/hpc/week7/week7_hw1 500000000
mpirun -np 16 /xfs2/courses/cs/csci4850/princewill.okorie/hpc/week7/week7_hw1 500000000
mpirun -np 32 /xfs2/courses/cs/csci4850/princewill.okorie/hpc/week7/week7_hw1 500000000

exit 0
