.PHONY: plots

all: least_squares.elf spline.elf


least_squares.elf: least_squares.cpp
	$(CXX) -std=c++17 -O3 $^ -o $@

spline.elf: spline.cpp
	$(CXX) -std=c++17 -O3 $^ -o $@

plots: plot least_squares.R spline.R $(shell find points/ -type f)
	./plot OLS points/task1 plots/task1ols3.png no 3
	./plot OLS points/task2 plots/task2ols3.png no 3
	./plot spline points/task1 plots/task1spline.png no
	./plot spline points/task2 plots/task2spline.png no

clean:
	rm -f least_squares.elf

