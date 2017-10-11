#include <iostream>
#include <iomanip>
#include <cmath>

bool solve(double **Ab, ssize_t n, double *x, double eps) {
    int iteration = 0;
    ssize_t i, j;
    double acc, prev_acc = HUGE_VALF;
    do {
        std::cout << "I = " << iteration << std::endl;
        acc = 0.0f;
        for (i = 0; i < n; i++) {
            double denom = Ab[i][i];
            double new_xi = Ab[i][n] / denom;
            for (j = 0; j < n; j++) {
                if (i == j)
                    continue;
                new_xi -= Ab[i][j] / denom * x[j];
            }
            acc = std::fmaxf(acc, fabs(new_xi - x[i]));
            x[i] = new_xi;
        }
        std::cout << "X = ";
        for (auto i = 0; i < n; i++) {
            std::cout << std::setw(16) << x[i];
        }
        std::cout << std::endl;
        std::cout << "ACC = " << acc << std::endl;
        if (acc >= prev_acc)
            return false;
        prev_acc = acc;
        iteration++;
    } while (acc > eps);
    return true;
}

int main() {
    double **Ab, *x, eps;
    ssize_t n;

    std::cin >> n;
    std::cin >> eps;

    Ab = new double*[n];
    for (auto i = 0; i < n; i++) {
        Ab[i] = new double[n + 1];
    }
    x = new double[n];

    for (auto row = 0; row < n; row++) {
        for (auto col = 0; col <= n; col++) { // including vector B
            std::cin >> Ab[row][col];
        }
        x[row] = 0.0;
    }

    bool succeeded = solve(Ab, n, x, eps);

    if (succeeded) {
        for (auto i = 0; i < n; i++) {
            std::cout << std::setw(16) << x[i];
        }
        std::cout << std::endl;
    } else {
        std::cout << "does not converge" << std::endl;
    }

    delete[] x;
    for (auto i = 0; i < n; i++) {
        delete[] Ab[i];
    }
    delete[] Ab;

    return 0;
}

