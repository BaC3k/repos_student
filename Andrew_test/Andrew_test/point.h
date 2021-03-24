#ifndef OOP_LAB5_POINT_H
#define OOP_LAB5_POINT_H

#include <iostream>
#include <type_traits>
#include <cmath>


template<class T>
struct point {
    T x;
    T y;
};

template<class T>
std::istream& operator>>(std::istream& is, point<T>& p) {
    is >> p.x >> p.y;
    return is;
}

template<class T>
std::ostream& operator<<(std::ostream& os, point<T> p) {
    os << '(' << p.x << ' ' << p.y << ')';
    return os;
}

#endif