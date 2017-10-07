#include <iostream>
#include <iomanip>
#include <cmath>

// Input: linear system `Ax=b`,
//        where Ab is matrix A combined with vector b.
//        Size of Ab is (n, n+1).
// Output: x.
void solve(double **Ab, ssize_t n, double *x) {
    ssize_t base, r, c;
    double sum;

    // Forward elimination
    for (base = 0; base < n; base++) {
        // Select maximal element in the column;
        // optimize by skipping base row.
        c = base;
        size_t leading_row = base;
        double max_value = Ab[base][base];
        for (r = base + 1; r < n; r++) {
            double abs_val = fabs(Ab[r][c]);
            if (abs_val > max_value) {
                leading_row = r;
                max_value = abs_val;
            }
        }

        // Swap base row with with leading row
        std::swap(Ab[base], Ab[leading_row]);

        // Eliminate base column
        for (r = base + 1; r < n; r++) {
            double coef = Ab[r][base] / Ab[base][base];
            for (c = base; c <= n; c++) { // including vector B
                Ab[r][c] -= coef * Ab[base][c];
            }
        }
    }

    // Backward substitution
    for (base = n - 1; base >= 0; base--) {
        sum = 0.0;
        for (c = base + 1; c < n; c++) {
            sum += Ab[base][c] * x[c];
        }
        x[base] = (Ab[base][n] - sum) / Ab[base][base];
    }
}

int main() {
    double **Ab, *x;
    ssize_t n;

    std::cin >> n;

    Ab = new double*[n];
    for (auto i = 0; i < n; i++) {
        Ab[i] = new double[n + 1];
    }
    x = new double[n];

    for (auto row = 0; row < n; row++) {
        for (auto col = 0; col <= n; col++) { // including vector B
            std::cin >> Ab[row][col];
        }
    }

    solve(Ab, n, x);

    for (auto i = 0; i < n; i++) {
        std::cout << std::setw(16) << x[i];
    }
    std::cout << std::endl;

    delete[] x;
    for (auto i = 0; i < n; i++) {
        delete[] Ab[i];
    }
    delete[] Ab;

    return 0;
}

