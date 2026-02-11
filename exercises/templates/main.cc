#include<iostream>

template<typename T>
void echo(const T& arg){
    std::cout << "echo: arg= " << arg << "\n";
}
template<typename T>
struct bar {
    T datum;
    void print() {
        std::cout << "bar: datum = " << datum << "\n";
    }
};

int main(){
    echo(1);
    echo(1.235);
    echo("hello");
    bar<int> intbar {1};
    bar<double> doublebar {1.234};
    bar<std::string> stringbar {"hello"};

}