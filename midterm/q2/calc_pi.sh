#!/bin/bash
#SBATCH -o calc_pi.out
#SBATCH --reservation csci4850
#SBATCH -n 32

module load openmpi/gcc/64/1.10.7
rm -f /xfs2/courses/cs/csci4850/princewill.okorie/hpc/midterm/calc_pi
mpic++ /xfs2/courses/cs/csci4850/princewill.okorie/hpc/midterm/calc_pi.cpp -o /xfs2/courses/cs/csci4850/princewill.okorie/hpc/midterm/calc_pi

mpirun -np 1 /xfs2/courses/cs/csci4850/princewill.okorie/hpc/midterm/calc_pi 100
mpirun -np 2 /xfs2/courses/cs/csci4850/princewill.okorie/hpc/midterm/calc_pi 100
mpirun -np 4 /xfs2/courses/cs/csci4850/princewill.okorie/hpc/midterm/calc_pi 100
mpirun -np 8 /xfs2/courses/cs/csci4850/princewill.okorie/hpc/midterm/calc_pi 100
mpirun -np 16 /xfs2/courses/cs/csci4850/princewill.okorie/hpc/midterm/calc_pi 100
mpirun -np 32 /xfs2/courses/cs/csci4850/princewill.okorie/hpc/midterm/calc_pi 100

exit 0
