CXXFLAGS = -std=c++23 -Wall -O

main: main.cc
	g++ $< $(CXXFLAGS) -o main
	echo Training, please wait...
	./main> Out.txt
	gnuplot plotA.gpi
	gnuplot plotB.gpi
	gnuplot plotC.gpi
	cat Out.txt

.PHONY:clean

clean:
	rm main *.png Out.txt fit.txt ode_exact.txt antiderivative.txt second_derivative.txt derivative.txt