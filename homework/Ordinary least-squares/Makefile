CXXFLAGS += -Wextra -std=c++23 -O

main: main.cc matrix.h qr.h lsfit.h
	g++ $(CXXFLAGS) main.cc -o main
	./main

plot: plotsettings.gpi
	gnuplot plotsettings.gpi

all: main plot

clean:
	rm main decay.png data.txt