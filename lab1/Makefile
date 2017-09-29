all: gauss.elf gauss-seidel.elf


gauss.elf: gauss.cpp
	$(CXX) $^ -o $@

gauss-seidel.elf: gauss-seidel.cpp
	$(CXX) $^ -o $@

clean:
	rm -f gauss.elf gauss-seidel.elf

