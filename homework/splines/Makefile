CXXFLAGS += -Wall -Wextra -std=c++23 -O

main: main.cc splines.h
	g++ $(CXXFLAGS) $< -o main

plot: gnuplot.gpi
	./main
	gnuplot gnuplot.gpi

plot_q:
	./main
	gnuplot gnuplot_qspline.gpi

plot_func:
	./main
	gnuplot gnuplot_func.gpi

plot_cubic:
	./main
	gnuplot gnuplot_cubic.gpi

.PHONY:clean

clean:
	rm main qspline.png plot.png