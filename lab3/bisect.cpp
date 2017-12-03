#include "common.h"

roots find_roots(std::function<double(double)> f, double left, double right, const double epsilon) {
    roots results;
    std::vector<std::pair<double, double>> intervals;

    intervals.emplace_back(std::make_pair(left, right));

    while (!intervals.empty()) {
        auto [oleft, oright] = intervals.back();
        intervals.pop_back();

        left = oleft;
        right = oright;

        size_t iterations = 0;
        double middle;
        do {
            middle = left / 2 + right / 2;
            if (f(left) * f(middle) <= 0)
                right = middle;
            else
                left = middle;
            iterations++;
        } while (right - left > epsilon);
        
        if (middle - oleft > epsilon
        && oright - middle > epsilon) {
            intervals.emplace_back(std::make_pair(oleft, middle));
            intervals.emplace_back(std::make_pair(middle, oright));
        } else {
            continue;
        }

        if (can_insert(results, middle, epsilon))
            results.emplace(middle, iterations);
    }

    return results;
}

#include "main.h"

