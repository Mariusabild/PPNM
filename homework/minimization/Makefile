CXXFLAGS = -std=c++23 -Wall -O

main: main.cc
	g++ $< $(CXXFLAGS) -o main
	./main < higgs.data.txt > Out.txt
	gnuplot higgs.gpi
	cat Out.txt

.PHONY:clean

clean:
	rm main *.png fit.txt data.txt Out.txt