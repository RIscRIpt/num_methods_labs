#!/usr/bin/env python

import numpy as np
import sys

N = int(input())

A = np.empty(shape=(N, N))
b = np.empty(shape=(N, 1))

for i in range(N):
    line = input().split()
    A[i] = list(map(float, line[:-1]))
    b[i] = float(line[-1])

x = np.linalg.solve(A, b)[:,0]
print("\t".join(map(str, x)))

