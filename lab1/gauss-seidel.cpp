#include <iostream>
#include <iomanip>
#include <cmath>

bool solve(float **Ab, ssize_t n, float *x, float eps) {
    ssize_t i, j;
    float acc, prev_acc = HUGE_VALF;
    do {
        acc = 0.0f;
        for (i = 0; i < n; i++) {
            float denom = Ab[i][i];
            float new_xi = Ab[i][n] / denom;
            for (j = 0; j < n; j++) {
                if (i == j)
                    continue;
                new_xi -= Ab[i][j] / denom * x[j];
            }
            acc = std::fmaxf(acc, fabs(new_xi - x[i]));
            x[i] = new_xi;
        }
        if (acc >= prev_acc)
            return false;
        prev_acc = acc;
    } while (acc > eps);
    return true;
}

int main() {
    float **Ab, *x, eps;
    ssize_t n;

    std::cin >> n;
    std::cin >> eps;

    Ab = new float*[n];
    for (auto i = 0; i < n; i++) {
        Ab[i] = new float[n + 1];
    }
    x = new float[n];

    for (auto row = 0; row < n; row++) {
        for (auto col = 0; col <= n; col++) { // including vector B
            std::cin >> Ab[row][col];
        }
        x[row] = 0.0;
    }

    bool succeeded = solve(Ab, n, x, eps);

    if (succeeded) {
        for (auto row = 0; row < n; row++) {
            for (auto col = 0; col <= n; col++) { // including vector B
                std::cout << std::setw(16) << Ab[row][col];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
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

