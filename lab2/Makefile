all: least_squares.elf spline.elf


least_squares.elf: least_squares.cpp
	$(CXX) -O3 $^ -o $@

spline.elf: spline.cpp
	$(CXX) -O3 $^ -o $@

clean:
	rm -f least_squares.elf

