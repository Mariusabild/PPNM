CXXFLAGS += -Wall -std=c++23 -O

all: main plot_erf plot_error

main: main.cc 
	g++ $(CXXFLAGS) $< -o main
	./main > Out.txt
	cat Out.txt
plot_erf: erf_plot.gpi
	gnuplot erf_plot.gpi

plot_error: erf_error.gpi
	gnuplot $<

.PHONY:clean

clean:
	rm main erf_data.txt erf_plot.png