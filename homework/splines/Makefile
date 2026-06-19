CXXFLAGS += -Wall -Wextra -std=c++23 -O

all: main plot plot_q plot_func plot_cubic plot_derivative
	cat Out.txt

main: main.cc splines.h
	g++ $(CXXFLAGS) $< -o main
	./main > Out.txt

plot: gnuplot_linear_spline.gpi
	gnuplot gnuplot_linear_spline.gpi

plot_q:
	gnuplot gnuplot_qspline.gpi

plot_func:
	gnuplot gnuplot_func.gpi

plot_cubic:
	gnuplot gnuplot_cubic.gpi

plot_derivative:
	gnuplot gnuplot_derivative.gpi

.PHONY:all clean

clean:
	rm main *.png *.txt