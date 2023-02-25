import time
import sys
import numpy as np

N = int(sys.argv[1])
iterations = int(sys.argv[2])

def dp(N,A,B):
    R = np.dot(A,B)
    return R

A = np.ones(N,dtype=np.float32)
B = np.ones(N,dtype=np.float32)

print(f'N:{N},iterations:{iterations}')


second_time=0

for i in range(iterations):
    t_start = time.monotonic_ns() 

    dp(N,A,B)

    t_end = time.monotonic_ns() 
    if(i>=iterations/2):
      second_time+=(t_end-t_start)

mean_exe_time = second_time/(iterations/2)

bandwidth = 2 * N / mean_exe_time

throughput = 2* N * 4 / mean_exe_time

print(f'N: {N}  <T>: {mean_exe_time/1000000000} sec  B:{bandwidth} GB/sec   F: {throughput} GFLOP/sec')