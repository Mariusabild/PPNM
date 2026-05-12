CXX += -std=c++23
CXXFLAGS += -Wall -Wextra -Werror

main: main.cc approx.cc 
	$(CXX) $(CXXFLAGS) $^ -o main
	./main > Out.txt
	cat Out.txt

.PHONY: clean
clean:
	rm -rf Out.txt main
