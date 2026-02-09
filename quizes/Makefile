CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23

Out.txt: quiz
	./quiz > Out.txt

main: quiz.cc

.PHONY: clean
clean:
	rm -rf Out.txt quiz