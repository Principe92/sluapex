#!/usr/bin/python
import torch
import sys

print('PyTorch CUDA available:', torch.cuda.is_available())
print('Device Name:', torch.cuda.get_device_name(0))

print('Python VERSION:', sys.version)
print('pyTorch VERSION:', torch.__version__)
print('CUDA VERSION', )
from subprocess import call
call(["nvcc", "--version"])

#! nvcc --version
print('CUDNN VERSION:', torch.backends.cudnn.version())
print('Number CUDA Devices:', torch.cuda.device_count())
print('Devices')
call(["nvidia-smi", "--format=csv", "--query-gpu=index,name,driver_version,memory.total,memory.used,memory.free"])
print('Active CUDA Device: GPU', torch.cuda.current_device())
print ('Available devices ', torch.cuda.device_count())
print ('Current cuda device ', torch.cuda.current_device())


