#pragma once
#include<iostream>
#include<cstdio>
#include<cassert>
#include<cstdio>
#include<iomanip>
#include<cmath>
#include<string>
#include<vector>
#include<initializer_list>
#include<functional>
#include<ranges>
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

inline bool approx
(double x, double y, double acc=1e-6, double eps=1e-6){
	if(std::abs(x-y) < acc) return true;
	if(std::abs(x-y) < eps*std::max(std::abs(x),std::abs(y))) return true;
	return false;
	}

inline bool approx
(const vector& a, const vector& b, double acc=1e-6, double eps=1e-6){
	if(a.size() != b.size()) return false;
	for(int i=0;i<a.size();i++)
		if(!approx(a[i],b[i],acc,eps)) return false;
	return true;
	}

struct matrix {
	std::vector<pp::vector> cols; //datastruktur er vektor i vektor
	matrix()=default; //standard matrix uden argumenter
	matrix(int n,int m) : cols(m, pp::vector(n)) {} // konstruer matrix med m søjler og n rækker.
	matrix(const matrix& other)=default; //kopier matrix
	matrix(matrix&& other)=default; //flyt matrix
	matrix& operator=(const matrix& other)=default; 
	matrix& operator=(matrix&& other)=default;
	int size1() const {return cols.empty() ? 0 : cols[0].size(); } //antal rækker
	int size2() const {return cols.size();} //antal søjler
	inline double& operator()(int i, int j){return cols[j][i];}
	inline double& operator[](int i, int j){return cols[j][i];}
	inline const double& operator()(int i, int j)const{return cols[j][i];}
	inline const double& operator[](int i, int j)const{return cols[j][i];}
	inline vector& operator[](int i){return cols[i];}
	inline const vector& operator[](int i) const {return cols[i];}
//	void resize(int n, int m);
	void setid(){
		assert(size1()==size2());
		for(int i=0;i<size1();i++){
			SELF[i,i]=1;
			for(int j=i+1;j<size1();j++)SELF[i,j]=SELF[j,i]=0;
			}
		}
	matrix transpose() const{
		matrix R(size2(),size1());
		FOR1(i,SELF)
		FOR2(j,SELF)
			R[j,i]=SELF[i,j];
		return R;
	}

	matrix T() const {return transpose();}
	
	double get (int i, int j) {return cols[j][i];}
	void set(int i, int j, double value){cols[j][i] = value;}
//	vector get_col(int j);
//	void set_col(int j,vector& cj);

	matrix& operator+=(const matrix& B){
		for(int i=0;i<size2();i++)SELF[i]+=B[i];
		return *this;
		}
	matrix& operator-=(const matrix& B){
		for(int i=0;i<size2();i++)SELF[i]-=B[i];
		return *this;
		}
	matrix& operator*=(const double c){
		for(int i=0;i<size2();i++)SELF[i]*=c;
		return *this;
		}
	matrix& operator/=(const double c){
		for(int i=0;i<size2();i++)SELF[i]/=c;
		return *this;
		}
	matrix& operator*=(const matrix&);
	matrix  operator^(int);

	void print(std::string s="") const{
		printf("%s\n",s.c_str());
		for(int i=0;i<size1();i++){
			for(int j=0;j<size2();j++)printf("%10.3g ",SELF[i,j]);
			printf("\n");
		}
	}
};

inline matrix operator+(matrix A, const matrix& B){
	for(int i=0;i<A.size2();i++)A[i]+=B[i];
	return A;
	}

inline matrix operator-(matrix A, const matrix& B){
	for(int i=0;i<A.size2();i++)A[i]-=B[i];
	return A;
	}

inline matrix operator*(const matrix& A, const matrix& B){
	if(A.size2()!=B.size1()) throw std::invalid_argument("size mismatch");
	matrix R(A.size1(),B.size2());
	for(int k=0;k<A.size2();k++)
	for(int j=0;j<B.size2();j++) {
		double Bkj=B[k,j];
		for(int i=0;i<A.size1();i++)R[i,j]+=A[i,k]*Bkj;
		}
	return R;
	}

inline matrix operator*(matrix A, const double c){
	for(auto &col : A.cols) col*=c;
	return A;
	}
inline matrix operator*(const double c, matrix A){
	for(auto &col : A.cols) col*=c;
	return A;
	}
inline matrix operator/(matrix A, const double c){
	for(auto &col : A.cols) col/=c;
	return A;
	}
inline vector operator*(const matrix& A, const vector& v){
	vector r(A.size1());
	FOR2(j,A){
		double vj=v[j];
		FOR1(i,A) r[i]+=A[i,j]*vj;
		}
	return r;
	}
}//pp