#include <iostream>
#include <iomanip>
#include <vector>
#include <iterator>
#include <functional>

struct point {
    double x, y;
};

std::istream& operator>>(std::istream &is, point &p) {
    return is >> p.x >> p.y;
}

std::ostream& operator<<(std::ostream &os, point &p) {
    return os << '(' << p.x << "; " << p.y << ')';
}

struct coefficients {
    size_t size;
    std::vector<double> a;
    std::vector<double> b;
    std::vector<double> c;
    std::vector<double> d;

    coefficients(size_t size) :
        size(size),
        a(size),
        b(size),
        c(size),
        d(size)
    {
    }
};

inline void
solveTridiagonal(std::vector<double> &x, size_t offset,
        std::function<double(size_t j, size_t i)> a,
        std::function<double(size_t j)> b)
{
    ssize_t k;
    ssize_t size = x.size() - offset;
    std::vector<double> alpha(size), beta(size);
    alpha[0] = a(0,1) / a(0,0);
    beta[0] = b(0) / a(0,0);
    for (k = 1; k < size; k++) {
        alpha[k] = a(k,k+1) / (a(k,k) - a(k,k-1) * alpha[k-1]);
        beta[k] = (b(k) - a(k,k-1) * beta[k-1]) / (a(k,k) - a(k,k-1) * alpha[k-1]);
    }
    x[k + offset] = beta[k];
    for (; k >= 0; k--) {
        x[k + offset] = beta[k] - alpha[k] * x[k + offset + 1];
    }
}

coefficients
interpolate(std::vector<point> &points)
{
    ssize_t size = points.size() - 1;
    coefficients coefs(size);
    auto h = [&](size_t i) {
        return points[i + 1].x - points[i].x;
    };
    auto a = [&](size_t j, size_t i) -> double {
        if (j > i) return h(j + 1);
        else if (j < i) return h(j + 1);
        else return 2 * (h(j) + h(j + 1));
    };
    auto b = [&](size_t j) {
        return 3 * (
                (points[j + 2].y - points[j + 1].y) / h(j + 1) -
                (points[j + 1].y - points[j + 0].y) / h(j + 0)
                );
    };
    coefs.c[0] = 0;
    solveTridiagonal(coefs.c, 1, a, b);
    for (ssize_t i = 0; i < size; i++) {
        coefs.a[i] = points[i].y;
        coefs.d[i] = (coefs.c[i + 1] - coefs.c[i]) / (3 * h(i));
        coefs.b[i] = (points[i + 1].y - points[i].y) / h(i) - (coefs.c[i + 2] + 2 * coefs.c[i + 1]) * h(i) / 3.0;
    }
    return coefs;
}

int main() {
    std::vector<point> points(
            (std::istream_iterator<point>(std::cin)),
            (std::istream_iterator<point>())
            );
    auto table = interpolate(points);
    for (size_t i = 0; i < table.size; i++) {
        std::cout
            /* << i + 1 << "\t" */
            << std::setw(12) << table.a[i] << "\t"
            << std::setw(12) << table.b[i] << "\t"
            << std::setw(12) << table.c[i] << "\t"
            << std::setw(12) << table.d[i] << "\n";
    }
    std::cout << std::endl;
    return 0;
}

