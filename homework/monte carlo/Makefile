CXXFLAGS += -Wall -std=c++23 -O

main: main.cc
	g++ $(CXXFLAGS) $< -o main
	./main

plot: circle_plot.gpi
	gnuplot circle_plot.gpi

.PHONY: clean

clean:
	rm main plot.png