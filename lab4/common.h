#include <iostream>
#include <vector>
#include <functional>
#include <cmath>

#include "function.h"

using FTY = std::function<double(const double, const double)>;

struct point { double t, y; };

std::vector<point> solve(FTY f, double y0, double left, double right, double step);

