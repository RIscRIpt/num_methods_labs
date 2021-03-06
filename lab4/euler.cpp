#include "common.h"

std::vector<point> solve(
        FTY f, double y0,
        double left, double right,
        double step)
{
    std::vector<point> points { {left, y0} };
    for (double t = left + step; t < right + step; t += step) {
        auto y_k = points.back().y;
        points.emplace_back(point{ t, y_k + step * f(t, y_k) });
    }
    return points;
}

#include "main.cpp"
