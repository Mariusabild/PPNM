#include<iostream>
#include<vector>

int main(){
    double a = 0.1;
    double b = a;
    std::vector<double> v {1,2,3};
    auto u=v; //LAv en kopi af v og gem i u
    //auto& w=v; //Refererer til v. Hvis vi ændrer v så ændres w.
    if(a==b) std::cout << "a==b\n";
    else std::cout << "a!=b\n";
    for(size_t i=0; i<v.size(); i++) std::cout << " " << v[i] << "\n";
    return 0;

    int i = 10
    while(i<20;){
        std::cout << i;
        i--;
    }
}