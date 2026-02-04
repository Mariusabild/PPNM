CXX = g++ -std=c++23
CXXFLAGS += -Wall -Wextra -Werror -O
LDLIBS += -lstdc++ -lm

Out.txt: main
#	./main > Out.txt
	./$< > $@ 

main: main.o 

.PHONY:clean
clean:
	rm -f Out.txt main