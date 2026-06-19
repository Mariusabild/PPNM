CXXFLAGS = -std=c++23 -Wall -O

main: main.cc
	g++ $< $(CXXFLAGS) -o main
	./main > Out.txt
	cat Out.txt
	gnuplot hydrogen.gpi

.PHONY:clean

clean:
	rm main *.svg Out.txt