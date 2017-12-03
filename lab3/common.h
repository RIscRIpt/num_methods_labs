#include <iostream>
#include <set>
#include <functional>
#include <type_traits>
#include <cmath>

struct root {
    double value;
    size_t iterations;

    root(double value, size_t iterations)
        : value(value)
        , iterations(iterations)
    {}
    
    root(const root&) = default;
    root(root&&) = default;

    root& operator=(const root&) = default;
    root& operator=(root&&) = default;
};

bool operator<(const root &lhs, const root &rhs) { return lhs.value < rhs.value; }
bool operator<(const root &lhs, const double rhs) { return lhs.value < rhs; }

using roots = std::set<root, std::less<>>;

bool can_insert(const roots &results, const double value, const double epsilon) {
    bool can = true;
    auto lb = results.lower_bound(value);
    if (lb != results.begin())
        can = can && fabs(std::prev(lb)->value - value) > 2 * epsilon;
    if (lb != results.end())
        can = can && fabs(lb->value - value) > 2 * epsilon;
    return can;
}

