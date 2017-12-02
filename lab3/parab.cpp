#include <iostream>
#include <set>
#include <functional>
#include <type_traits>
#include <cmath>

constexpr double pi = M_PI;
#include "function.h"

bool can_insert(const std::set<double> &results, const double value, const double epsilon) {
    bool can = true;
    auto lb = results.lower_bound(value);
    if (lb != results.begin())
        can = can && fabs(*std::prev(lb) - value) > 2 * epsilon;
    if (lb != results.end())
        can = can && fabs(*lb - value) > 2 * epsilon;
    return can;
}

std::set<double> parab(std::function<double(double)> f, double left, double right, const double epsilon) {
    std::set<double> results;
    std::vector<std::pair<double, double>> intervals;

    intervals.emplace_back(std::make_pair(left, right));

    while (!intervals.empty()) {
        auto [oleft, oright] = intervals.back();
        intervals.pop_back();

        left = oleft;
        right = oright;

        std::cout << "ITERATION: " << left << ' ' << right << std::endl;

        double middle = left / 2 + right / 2;
        do {
            double x_0 = left;
            double x_1 = middle;
            double x_2 = right;

            double y_0 = f(x_0);
            double y_1 = f(x_1);
            double y_2 = f(x_2);

            double denom_0 = (x_0 - x_1) * (x_0 - x_2);
            double a_0 = y_0 / denom_0;
            double b_0 = -y_0 * (x_1 + x_2) / denom_0;
            double c_0 = y_0 * x_1 * x_2 / denom_0;

            double denom_1 = (x_1 - x_0) * (x_1 - x_2);
            double a_1 = y_1 / denom_1;
            double b_1 = -y_1 * (x_0 + x_2) / denom_1;
            double c_1 = y_1 * x_0 * x_2 / denom_1;

            double denom_2 = (x_2 - x_0) * (x_2 - x_1);
            double a_2 = y_2 / denom_2;
            double b_2 = -y_2 * (x_0 + x_1) / denom_2;
            double c_2 = y_2 * x_0 * x_1 / denom_2;

            double A = a_0 + a_1 + a_2;
            double B = b_0 + b_1 + b_2;
            double C = c_0 + c_1 + c_2;

            double D = sqrt(B * B - 4 * A * C);

            double part1_x = -B / (2 * A);
            double part2_x = D / (2 * A);

            // Choose X, which belongs [left; right]
            double X1 = part1_x + part2_x;
            double X2 = part1_x - part2_x;
            double X;
            if (left <= X1 && X1 <= right) {
                X = X1;
            } else {
                X = X2;
            }

            // Choose what to replace (left, or right?)
            if (middle <= X && X <= right) {
                left = middle;
            } else {
                right = middle;
            }
            middle = X;
        } while (right - left > epsilon /*&& fabs(f(right) - f(left)) > epsilon*/);

        if (middle - oleft > epsilon
        && oright - middle > epsilon) {
            intervals.emplace_back(std::make_pair(oleft, middle));
            intervals.emplace_back(std::make_pair(middle, oright));
        } else {
            continue;
        }

        if (can_insert(results, middle, epsilon))
            results.insert(middle);
    }

    return results;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "usage: " << argv[0] << " left right epsilon\n";
        return 1;
    }
    double left = atof(argv[1]);
    double right = atof(argv[2]);
    double epsilon = atof(argv[3]);
    auto results = parab(f, left, right, epsilon);
    for (auto r : results)
        std::cout << r << '\n';
    return results.empty() ? -1 : 0;
}
