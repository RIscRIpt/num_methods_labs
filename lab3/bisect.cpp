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

std::set<double> bisect(std::function<double(double)> f, double left, double right, const double epsilon) {
    std::set<double> results;
    std::vector<std::pair<double, double>> intervals;

    intervals.emplace_back(std::make_pair(left, right));

    while (!intervals.empty()) {
        auto [oleft, oright] = intervals.back();
        intervals.pop_back();

        left = oleft;
        right = oright;

        double middle;
        do {
            middle = left / 2 + right / 2;
            if (f(left) * f(middle) <= 0)
                right = middle;
            else
                left = middle;
        } while (right - left > epsilon);
        
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
    auto results = bisect(f, left, right, epsilon);
    for (auto r : results)
        std::cout << r << '\n';
    return results.empty() ? -1 : 0;
}

