#include <iostream>
#include <iterator>
#include <vector>
#include <functional>

std::vector<double>
solve3d(ssize_t size,
        std::function<double(size_t j, size_t i)> a,
        std::function<double(size_t j)> b,
        double b_k)
{
    ssize_t k;
    std::vector<double> alpha(size), beta(size);
    alpha[0] = a(0,1) / a(0,0);
    beta[0] = b(0) / a(0,0);
    for (k = 1; k < size - 1; k++) {
        alpha[k] = a(k,k+1) / (a(k,k) - a(k,k-1) * alpha[k-1]);
        beta[k] = (b(k) - a(k,k-1) * beta[k-1]) / (a(k,k) - a(k,k-1) * alpha[k-1]);
    }
    alpha[k] = a(k,k+1) / (a(k,k) - a(k,k-1) * alpha[k-1]);
    beta[k] = (b_k - a(k,k-1) * beta[k-1]) / (a(k,k) - a(k,k-1) * alpha[k-1]);
    std::vector<double> x(size);
    x[k] = beta[k];
    for (; k >= 0; k--) {
        x[k] = beta[k] - alpha[k] * x[k+1];
    }
    return x;
}

std::vector<double>
solve3d(std::vector<double> coefficients)
{
    ssize_t size;
    if ((coefficients.size() + 2) % 4 != 0) {
        throw std::runtime_error("coefficients.size() is not valid!");
    }
    size = (coefficients.size() + 2) / 4;
    auto a = [&](size_t j, size_t i) { return coefficients[j * 3 + i]; };
    auto b = [&](size_t j) { return coefficients[j * 4 + 2]; };
    return solve3d(size, a, b, coefficients.back());
}

int main() {
    std::vector<double> coefficients(
            (std::istream_iterator<double>(std::cin)),
            (std::istream_iterator<double>())
            );
    try {
        auto xs = solve3d(coefficients);
        for (auto &&x : xs) {
            std::cout << x << '\t';
        }
        std::cout << std::endl;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

