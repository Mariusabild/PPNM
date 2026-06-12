CXXFLAGS += -Wall -Wextra -std=c++23 -O

all: main plot plot_q plot_func plot_cubic

main: main.cc splines.h
	g++ $(CXXFLAGS) $< -o main
	./main > Out.txt

plot: gnuplot.gpi
	gnuplot gnuplot.gpi

plot_q:
	gnuplot gnuplot_qspline.gpi

plot_func:
	gnuplot gnuplot_func.gpi

plot_cubic:
	gnuplot gnuplot_cubic.gpi

.PHONY:all clean plot plot_q plot_func plot_cubic

clean:
	rm main *.png