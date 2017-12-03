#include <iostream>
#include <cmath>

constexpr double pi = M_PI;
#include "function.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "usage: " << argv[0] << " left right epsilon\n";
        return 1;
    }
    double left = atof(argv[1]);
    double right = atof(argv[2]);
    double epsilon = atof(argv[3]);
    auto results = find_roots(f, left, right, epsilon);
    for (auto r : results) {
        std::cout << r.value << '\n';
        std::cerr << '[' << r.iterations << ']' << '\t' << r.value << '\n';
    }
    return results.empty() ? -1 : 0;
}

