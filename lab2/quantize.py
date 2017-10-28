#!/usr/bin/env python
from math import *
import numpy as np

import sys

try:
    equation = sys.argv[1]
    left     = float(sys.argv[2])
    right    = float(sys.argv[3])
    delta    = float(sys.argv[4])
except:
    print("Usage: \"equation\" from to delta")
    sys.exit(1)

y = lambda x: eval(equation)
for x in np.arange(left, right + delta, delta):
    print("{}\t{}".format(x, y(x)))

