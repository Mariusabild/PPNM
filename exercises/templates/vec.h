#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <complex>

template<typename T>
struct identity { using type = T; };

template<typename T>
struct vec {
    T x, y, z;

    vec(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}
    vec() : vec(T{}, T{}, T{}) {}
    vec(const vec&) = default;
    vec(vec&&) = default;
    vec& operator=(const vec&) = default;
    vec& operator=(vec&&) = default;

    vec& operator+=(const vec& other) { x += other.x; y += other.y; z += other.z; return *this; }
    vec& operator-=(const vec& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
    vec& operator*=(const T& s) { x *= s; y *= s; z *= s; return *this; }
    vec& operator/=(const T& s) { x /= s; y /= s; z /= s; return *this; }

    void print(const std::string& s = "") const {
        if (!s.empty()) std::cout << s;
        std::cout << "(" << x << "," << y << "," << z << ")\n";
    }

    T dot(const vec& other) const { return x * other.x + y * other.y + z * other.z; }

    vec cross(const vec& other) const {
        return vec(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
    }

    // Denne version af norm virker for både int, double og std::complex
    double norm() const {
        using std::abs; using std::sqrt;
        double nx = static_cast<double>(abs(x));
        double ny = static_cast<double>(abs(y));
        double nz = static_cast<double>(abs(z));
        return sqrt(nx*nx + ny*ny + nz*nz);
    }
};

template<typename T> vec<T> operator+(vec<T> a, const vec<T>& b) { return a += b; }
template<typename T> vec<T> operator-(vec<T> a, const vec<T>& b) { return a -= b; }
template<typename T> vec<T> operator-(const vec<T>& v) { return vec<T>(-v.x, -v.y, -v.z); }
template<typename T> vec<T> operator*(vec<T> v, typename identity<T>::type s) { return v *= s; }
template<typename T> vec<T> operator*(typename identity<T>::type s, vec<T> v) { return v *= s; }
template<typename T> vec<T> operator/(vec<T> v, typename identity<T>::type s) { return v /= s; }

template<typename T>
std::ostream& operator<<(std::ostream& os, const vec<T>& v) {
    return os << "(" << v.x << "," << v.y << "," << v.z << ")";
}

template<typename T>
bool approx(const vec<T>& a, const vec<T>& b, double acc = 1e-6, double eps = 1e-6) {
    using std::abs;
    return abs(a.x - b.x) <= acc + eps*abs(a.x) && 
           abs(a.y - b.y) <= acc + eps*abs(a.y) && 
           abs(a.z - b.z) <= acc + eps*abs(a.z);
}