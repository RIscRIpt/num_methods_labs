#include "common.h"

std::vector<point> solve(FTY f, double left, double right, double step, double start) {
    std::vector<point> points { {left, start} };
    for (double t = left + step; t < right + step; t += step) {
        auto [t_k, y_k] = points.back();
        auto f_1 = f(t_k, y_k);
        auto f_2 = f(t_k + step / 2.0, y_k + step / 2.0 * f_1);
        auto f_3 = f(t_k + step / 2.0, y_k + step / 2.0 * f_2);
        auto f_4 = f(t, y_k + step * f_3);
        points.emplace_back(point{
                t,
                y_k + step / 6.0 * (f_1 + 2 * f_2 + 2 * f_2 + f_4)
                });
    }
    return points;
}

#include "main.cpp"
