.PHONY: plots

all: least_squares.elf spline.elf


least_squares.elf: least_squares.cpp
	$(CXX) -std=c++17 -O3 $^ -o $@

spline.elf: spline.cpp
	$(CXX) -std=c++17 -O3 $^ -o $@

plots: plot least_squares.R spline.R $(shell find points/ -type f)
	for i in {0..9}; do ./plot OLS points/task1 plots/task1o$$i.png no $$i; done
	for i in {0..9}; do ./plot OLS points/task2 plots/task2o$$i.png no $$i; done
	for i in {0..9}; do ./plot both points/task1 plots/task1B$$i.png no $$i; done
	for i in {0..9}; do ./plot both points/task2 plots/task2B$$i.png no $$i; done
	./plot spline points/task1 plots/task1s$i.png no
	./plot spline points/task2 plots/task2s$i.png no

clean:
	rm -f least_squares.elf

