#include "common.h"

roots find_roots(
        std::function<double(double)> f,
        double left,
        double right,
        const double epsilon
        )
{
    roots results;
    std::vector<std::pair<double, double>> intervals;

    intervals.emplace_back(std::make_pair(left, right));

    while (!intervals.empty()) {
        auto [oleft, oright] = intervals.back();
        intervals.pop_back();

        left = oleft;
        right = oright;

        std::cerr << "\nInterval: " << left << "; " << right << '\n';

        double prev_middle;
        bool has_root = true;
        size_t iterations = 0;
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
            } else if (left <= X2 && X2 <= right) {
                X = X2;
            } else {
                // No root can be found!
                has_root = false;
                break;
            }

            // Choose what to replace (left, or right?)
            if (middle <= X && X <= right) {
                left = middle;
            } else {
                right = middle;
            }
            prev_middle = middle;
            middle = X;

            iterations++;

            std::cerr << '[' << iterations << ']'
                << '\t' << fabs(middle - prev_middle) << '\t' << middle << '\n';
        } while (fabs(middle - prev_middle) > epsilon);

        if (has_root
                && middle - oleft > epsilon
                && oright - middle > epsilon)
        {
            intervals.emplace_back(std::make_pair(oleft, middle - epsilon));
            intervals.emplace_back(std::make_pair(middle + epsilon, oright));
        } else {
            continue;
        }

        if (can_insert(results, middle, epsilon))
            results.emplace(middle, iterations);
    }

    return results;
}

#include "main.h"

