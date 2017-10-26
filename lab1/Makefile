all: gauss.elf gauss-seidel.elf


gauss.elf: gauss.cpp
	$(CXX) -O3 $^ -o $@

gauss-seidel.elf: gauss-seidel.cpp
	$(CXX) -O3 $^ -o $@

clean:
	rm -f gauss.elf gauss-seidel.elf

