CXXFLAGS += -std=c++23 -O

main: main.cc
	g++ $(CXXFLAGS) $< -o main
	./main
	gnuplot plotsettings.gpi

.PHONY:clean
clean:
	rm main plot.png orbit_circle.txt orbit_ellipse.txt orbit_precession.txt orbit.txt
	