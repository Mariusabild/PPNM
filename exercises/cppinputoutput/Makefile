CXX = g++ 
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O

Out.txt: main
	./main > Out.txt
	cat Out.txt

main: main.cc

.PHONY:clean

clean:
	rm -rf Out.txt main