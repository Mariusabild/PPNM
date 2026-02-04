CXX = g++ -std=c++23
CXXFLAGS += -Wall -Wextra -Werror

Out.txt: main
	./main > Out.txt
	cat Out.txt

main: main.cc approx.cc 

.PHONY: clean
clean:
	rm -rf Out.txt main
