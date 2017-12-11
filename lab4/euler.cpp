#include "common.h"

std::vector<point> solve(FTY f, double left, double right, double step, double start) {
    std::vector<point> points { {left, start} };
    for (double t = left + step; t < right + step; t += step) {
        auto y_k = points.back().y;
        points.emplace_back(point{ t, y_k + step * f(t, y_k) });
    }
    return points;
}

#include "main.cpp"
