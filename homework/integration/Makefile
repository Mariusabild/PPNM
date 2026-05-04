CXXFLAGS += -Wall -std=c++23 -O

main: main.cc 
	g++ $(CXXFLAGS) $< -o main
	./main

plot: plot_erf.gpi
	gnuplot $<

.PHONY:clean

clean:
	rm main erf_data.txt erf_plot.png