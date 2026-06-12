CXXFLAGS += -Wextra -std=c++23 -O

all: main plot

main: main.cc matrix.h qr.h lsfit.h
	g++ $(CXXFLAGS) main.cc -o main
	./main > Out.txt

plot: plotsettings.gpi
	gnuplot plotsettings.gpi

clean:
	rm main decay.png data.txt