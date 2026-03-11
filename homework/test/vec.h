#pragma once
#include <vector>
#include <cmath>

namespace pp {

    struct vector {
        private:

        std::vector<double> data;

        public:

        void push_back(double value){
            data.push_back(value);
        }
        double& operator[](size_t i) {return data[i];} //Ændrer element i vektor
        const double& operator[](size_t i) const {return data[i];} // retunerer en reference til en double som ikke må ændres
        vector() = default; //defualt constructor
        vector(size_t n): data(n) {} //constructor med størrelse
        size_t size() const {return data.size();}

        vector& operator+=(const vector& other) {
            for(size_t i = 0; i < size(); i++) {data[i] += other[i];}
            return *this;
        }

        vector& operator-=(const vector& other) {
            for(size_t i = 0; i < size(); i++) {data[i] -= other[i];}
            return *this;
        }

        vector& operator/=(double scalar) {
            for(size_t i = 0; i < size(); i++) {data[i] /= scalar;}
            return *this;
        }

        vector& operator*=(double scalar) {
            for(size_t i = 0; i < size(); i++) {data[i] *= scalar;}
            return *this;
        }

        double norm() const{
            double value = 0;
            for(double x : data) {value += x*x;}
            return std::sqrt(value);
        }

        double scalar(const vector& other) const{
            double value = 0;
            for(size_t i = 0; i < size(); i++) {value += data[i] * other[i];}
            return value;
        }
        vector operator-() const {
            vector result = *this; 
            for(size_t i = 0; i < size(); i++) {result[i] = -result[i];}                
            return result;
        }
    };

    vector operator+(vector a, const vector& b) {
        a += b;
        return a;
    }
    vector operator-(vector a, const vector& b) {
        a -= b;
        return a;
    }
    vector operator/(vector a, double scalar) {
        a /= scalar;
        return a;
    }
    vector operator*(double scalar, vector a) {
        a *= scalar;
        return a;
    }
    vector operator*(vector a, double scalar) {
        a *= scalar;
        return a;
    }
}