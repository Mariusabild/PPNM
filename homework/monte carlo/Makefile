CXXFLAGS += -Wall -std=c++23 -O

all: main plot

main: main.cc
	g++ $(CXXFLAGS) $< -o main
	./main > Out.txt
	cat Out.txt

plot: circle_plot.gpi quasi_plot.gpi
	gnuplot circle_plot.gpi
	gnuplot quasi_plot.gpi

.PHONY: clean

clean:
	rm main *.png *.txt