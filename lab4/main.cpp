#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
    if (argc != 5) {
        std::cerr << "usage: " << argv[0] << " left right step start_condition\n";
        return 1;
    }
    double left = atof(argv[1]);
    double right = atof(argv[2]);
    double step = atof(argv[3]);
    double start = atof(argv[4]);
    auto points = solve(f, left, right, step, start);
    for (auto [t, y] : points)
        std::cout << t << '\t' << y << '\n';
}

