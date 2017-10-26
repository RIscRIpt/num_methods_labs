#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

struct point {
    double x, y;
};

std::istream& operator>>(std::istream &is, point &p) {
    return is >> p.x >> p.y;
}

std::ostream& operator<<(std::ostream &os, point &p) {
    return os << '(' << p.x << "; " << p.y << ')';
}

std::vector<std::vector<double>>
solve(std::vector<point> &points, size_t order)
{
    double coef;
    std::vector<std::vector<double>> result;
    result.resize(order + 1);
    for (size_t row = 0; row < order + 1; row++) {
        // build only lower triangular matrix (because upper == lower)
        result[row].resize(row + 2);
        // left-hand side
        for (size_t col = 0; col < row + 1; col++) {
            coef = 0.0;
            for (auto &&point : points) {
                coef += pow(point.x, row) * pow(point.x, col);
            }
            result[row][col] = coef;
        }
        // right-hand side
        coef = 0.0;
        for (size_t i = 0; i < points.size(); i++) {
            coef += points[i].y * pow(points[i].x, row);
        }
        result[row].back() = coef;
    }
    return result;
}

int main() {
    size_t order;
    size_t pointCount;
    std::vector<point> points;

    std::cin >> order;
    std::cin >> pointCount;
    points.resize(pointCount);
    for (auto &&point : points) {
        std::cin >> point;
    }

    auto coefficients = solve(points, order);
    assert(coefficients.size() == order + 1);
    std::cout << coefficients.size() << std::endl;
    for (size_t row = 0; row < order + 1; row++) {
        for (size_t col = 0; col < row + 1; col++)
            std::cout << coefficients[row][col] << '\t';
        for (size_t col = row + 1; col < order + 1; col++)
            std::cout << coefficients[col][row] << '\t';
        std::cout << coefficients[row].back() << '\n';
    }
    std::cout.flush();

    return 0;
}

