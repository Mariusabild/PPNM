CXXFLAGS += -Wall -Werror -std=c++23 -O

main: main.cc
	g++ $< $(CXXFLAGS) -o main
	./main > Out.txt
	cat Out.txt

.PHONY:clean

clean:
	rm main Out.txt