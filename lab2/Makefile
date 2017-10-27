all: least_squares.elf solve3d.elf


least_squares.elf: least_squares.cpp
	$(CXX) -O3 $^ -o $@

solve3d.elf: solve3d.cpp
	$(CXX) -O3 $^ -o $@

clean:
	rm -f least_squares.elf

