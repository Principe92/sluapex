#!/bin/bash
#SBATCH -o matrix.out
#SBATCH --reservation csci4850
#SBATCH -n 4

module load openmpi/gcc/64/1.10.7
rm -f /xfs2/courses/cs/csci4850/princewill.okorie/hpc/final/matrix
mpic++ /xfs2/courses/cs/csci4850/princewill.okorie/hpc/final/matrix.cpp -o /xfs2/courses/cs/csci4850/princewill.okorie/hpc/final/matrix

mpirun -np 16 /xfs2/courses/cs/csci4850/princewill.okorie/hpc/final/matrix 4

# mpirun -np 1 /xfs2/courses/cs/csci4850/princewill.okorie/hpc/final/matrix 1440
# mpirun -np 4 /xfs2/courses/cs/csci4850/princewill.okorie/hpc/final/matrix 1440
# mpirun -np 9 /xfs2/courses/cs/csci4850/princewill.okorie/hpc/final/matrix 1440
# mpirun -np 16 /xfs2/courses/cs/csci4850/princewill.okorie/hpc/final/matrix 1440

# mpirun -np 1 /xfs2/courses/cs/csci4850/princewill.okorie/hpc/final/matrix 2880
# mpirun -np 4 /xfs2/courses/cs/csci4850/princewill.okorie/hpc/final/matrix 2880
# mpirun -np 9 /xfs2/courses/cs/csci4850/princewill.okorie/hpc/final/matrix 2880
# mpirun -np 16 /xfs2/courses/cs/csci4850/princewill.okorie/hpc/final/matrix 2880

exit 0
