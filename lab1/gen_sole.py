#!/usr/bin/env python

import sys
import random

def main():
    size = int(sys.argv[1])
    eps = sys.argv[2] if len(sys.argv) > 2 else ""
    print(size)
    print(eps)

    X = [random.randint(-10, +10) for _ in range(size)]

    for i in range(size):
        b = 0
        for j in range(size):
            if i != j:
                coef = random.randint(-10, +10)
            else:
                coef = random.randint(10 * size, 20 * size)
            b += coef * X[j]
            print(coef, end='\t')
        print(b)

    print(X)

if __name__ == "__main__":
    main()

