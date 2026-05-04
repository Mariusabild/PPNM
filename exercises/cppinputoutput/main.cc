#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream>

int main(int argc, char* argv[]){
    std::string infile="", outfile="";
    std::vector<double> numbers;

    for(int i = 1; i < argc; i++){
        std::string arg = argv[i];

        if(arg == "-n" && i+1 < argc){
            numbers.push_back(std::stod(argv[++i]));
        }
        else if(arg == "--input" && i+1 < argc){
            infile = argv[++i];
        }
        else if(arg == "--output" && i+1 < argc){
            outfile = argv[++i];
        }
    }

    
    if(!infile.empty() && !outfile.empty()){
        std::ifstream myinput(infile);
        std::ofstream myoutput(outfile);

        if(myinput.is_open() && myoutput.is_open()){
            double x;
            while(myinput >> x){
                myoutput << x << " " << std::sin(x) << " " << std::cos(x) << std::endl;
            }
        } else {
            std::cerr << "Error opening files\n";
            return EXIT_FAILURE;
        }
    }

    
    else if(!numbers.empty()){
        for(auto n : numbers){
            std::cout << n << " " << std::sin(n) << " " << std::cos(n) << "\n";
        }
    }

    
    else{
        double x;
        while(std::cin >> x){
            std::cout << x << " " << std::sin(x) << " " << std::cos(x) << std::endl;
        }
    }

    return EXIT_SUCCESS;
}