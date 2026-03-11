CXXFLAGS += -Wall -Wextra -std=c++23 -O
rmax = 10
dr = 1


main: main.cc matrix.h jacobi.h
	g++ $(CXXFLAGS) $< -o main

wave.dat: main
	./main -rmax $(rmax) -dr $(dr) > wave.dat

plot: 
	gnuplot wave.gnuplot

.PHONY: clean
clean:
	rm main wave.dat wave.png