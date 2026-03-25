#pragma once
#include<iostream>
#include<cassert>
#include<cstdio>
#include<iomanip>
#include<cmath>
#include<string>
#include<vector>
#include<initializer_list>
#include<functional>
#define SELF (*this)
#define FOR(i,V) for(int i=0;i<V.size();i++)
#define FOR1(i,A) for(int i=0;i<A.size1();i++)
#define FOR2(j,A) for(int j=0;j<A.size2();j++)

namespace pp{

struct vector {
	std::vector<double> data;

    //Nedenstående er constructere, derfor har de samme navn som klassen, og ingen returtype
	vector() = default; //lav vektor uden argumenter
	vector(int n) : data(n) {} //lav vektor med given størrelse n og indgange 0 
	vector(std::initializer_list<double> list) : data(list) {} //lav en vektor med given størrelse og indange
	vector(const vector&) = default; //kopier
	vector(vector&&) noexcept = default; //flyt data fra en vektor til en anden

	vector& operator=(const vector&) = default; //kopier
	vector& operator=(vector&&) noexcept = default; //flyt

	inline int size() const {return data.size();} //antal elementer i en vektor
//	auto n(){return std::views::iota(0,size());}
//	void resize(int n) {data.resize(n);}
	inline double& operator[](int i) {return data[i];} //vis et element i en vektor
	inline const double& operator[](int i) const {return data[i];} //reference version, her kopieres

	vector& operator+=(const vector& other){
		FOR(i,SELF) SELF[i]+=other[i];
		//for(int i:n())SELF[i]+=other[i];
		return SELF;
		}

	vector& operator-=(const vector& other){
		FOR(i,SELF) SELF[i]-=other[i];
		return SELF;
		}

	vector& operator*=(double c){
		FOR(i,SELF) SELF[i]*=c;
		return SELF;
		}

	vector& operator/=(double c){
		FOR(i,SELF) SELF[i]/=c;
		return SELF;
		}

	double norm() const {
		double sum2=0;
		FOR(i,SELF) sum2+=SELF[i]*SELF[i];
		return std::sqrt(sum2);
	}

	void print(std::string s="") const {
		std::cout<<s;
//		for(auto &x : data) std::cout<<x<<" ";
		for(auto &x : data) printf("%10.3g ",x);
		std::cout<<"\n";
	}

    //Afbild elementer vha. en funktion f.eks. x -> x^2
	vector map(std::function<double(double)> f) const{
		vector r(size());
		FOR(i,SELF) r.data[i]=f(data[i]);
		return r;
	}

}; //vector

inline vector operator+(vector a, const vector& b){ a+=b ; return a; }
inline vector operator-(vector a)                 { a*=-1; return a; }
inline vector operator-(vector a, const vector& b){ a-=b ; return a; }
inline vector operator*(vector a, const double c) { a*=c ; return a; }
inline vector operator*(const double c, vector a) { a*=c ; return a; }
inline vector operator/(vector a, const double c) { a/=c ; return a; }
}