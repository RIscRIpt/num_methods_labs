#!/usr/bin/env python

import os
import sys
import numpy as np
import subprocess as sp

def main():
    current_dir = os.path.dirname(os.path.realpath(__file__))
    problem_id = sys.argv[1]
    solver = current_dir + "/" + sys.argv[2] + ".elf"
    extra_args = ' '.join(sys.argv[3:]) if len(sys.argv) > 3 else ""

    with open(current_dir + "/problems/" + problem_id, 'r') as prob_file:
        AB = np.matrix(prob_file.read().rstrip('\n').replace('\n', ';'))

    A = AB[:,:-1]
    B = AB[:,-1]

    def m_to_str(m):
        return ' '.join(' '.join(str(cell) for cell in row) for row in np.array(m))

    def solve(A, B):
        problem = "{} {} {}".format(
                A.shape[0],
                extra_args,
                m_to_str(np.concatenate((A, B), axis=1))
                )
        sp_solver = sp.run([solver], input=problem.encode("utf-8"), stdout=sp.PIPE)
        return np.matrix(';'.join(sp_solver.stdout.decode("utf-8").split('\n')[-2].split()))

    X = solve(A, B)
    print("X:")
    print(X.T)
    print("Residual:")
    print((B - A * X).T)

if __name__ == "__main__":
    main()

