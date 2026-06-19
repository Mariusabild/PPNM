CXXFLAGS += -std=c++23 -O

all: main plot

main: main.cc
	g++ $(CXXFLAGS) $< -o main
	./main > Out.txt
	cat Out.txt

plot: orbit.gpi threebody.gpi damped_oscillator.gpi
	gnuplot orbit.gpi
	gnuplot threebody.gpi
	gnuplot damped_oscillator.gpi

.PHONY:clean
clean:
	rm main *.png orbit_circle.txt orbit_ellipse.txt orbit_precession.txt Out.txt
	