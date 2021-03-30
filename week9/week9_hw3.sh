#!/bin/bash
#SBATCH -o week9_hw3.out
#SBATCH --reservation csci4850
#SBATCH -n 4

module load openmpi/gcc/64/1.10.7
rm -f /xfs2/courses/cs/csci4850/princewill.okorie/hpc/week9/week9_hw3
mpic++ /xfs2/courses/cs/csci4850/princewill.okorie/hpc/week9/week9_hw3.cpp -o /xfs2/courses/cs/csci4850/princewill.okorie/hpc/week9/week9_hw3

mpirun /xfs2/courses/cs/csci4850/princewill.okorie/hpc/week9/week9_hw3

exit 0
