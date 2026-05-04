CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O

main: main.cc
	$(CXX) $(CXXFLAGS) main.cc -o main

out_cmd.txt: main
	./main -n 1 -n 2 -n 3 -n 4 -n 5 > out_cmd.txt
	cat out_cmd.txt

out_stdin.txt: main
	echo 1 2 3 4 5 | ./main > out_stdin.txt
	cat out_stdin.txt

out_file.txt: main
	echo "1 2 3 4 5" > input.txt
	./main --input input.txt --output out_file.txt
	cat out_file.txt

.PHONY: clean

clean:
	rm -f main out_*.txt input.txt