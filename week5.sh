#!/bin/bash
#SBATCH -o week5.out
#SBTACH --reservation=csci4850
#SBTACH -n 4

/bin/hostname
srun -l /bin/hostname
srun -l /bin/pwd

exit 0
