CXXFLAGS = -Wextra -Werror -std=c++23 -O
LDLIBS += -lstdc++ -lm 

Out.txt : main
	./main > Out.txt
	cat Out.txt

main: main.o
	$(CXX) $(CXXFLAGS) main.o -o main $(LDLIBS)

main.o: main.cc vec.h
	$(CXX) $(CXXFLAGS) -c main.cc

.PHONY: clean
clean:
	$(RM) main main.o Out.txt

test:
	@echo CXX
	@echo $(CXX)
	@echo $(RM)
	@echo $(CC)
	@echo $(SHELL)
