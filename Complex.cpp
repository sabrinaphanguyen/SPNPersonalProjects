//STUDENT ID: 20470614

#include "Complex.h"
#include <iostream>
#include <cstdio>

using namespace std;

string Complex::Div_By_Zero_Exception::what() { // implements the constructors
    return "Divide by zero exception";
}

string Complex::Div_By_Zero_Exception::to_string() {
    return "Divide by zero exception";
}

Complex& Complex::operator=(const Complex& rhs) {
    if (this != &rhs) { // defines the function (not done in the header file)
        _real = rhs._real;
        _imag = rhs._imag;
    }
    return *this;
}

bool Complex::operator==(const Complex& that) const {
    return (_real == that._real) && (_imag == that._imag);
}

bool Complex::operator<(const Complex& that) const {
    return norm() < that.norm();
}

Complex Complex::operator+(const Complex& that) const {
    return Complex(_real + that._real, _imag + that._imag);
}

Complex Complex::operator-(const Complex& that) const {
    return Complex(_real - that._real, _imag - that._imag);
}

Complex Complex::operator*(const Complex& that) const {
    return Complex(_real * that._real - _imag * that._imag, _real * that._imag + _imag * that._real);
}

Complex Complex::reciprocal() const {
    double denominator = _real * _real + _imag * _imag;
    if (denominator <= FLOOR)
        throw Div_By_Zero_Exception();
    return Complex(_real / denominator, -_imag / denominator);
}

Complex Complex::operator/(const Complex& that) const {
    return (*this) * (that.reciprocal());
}

string Complex::to_string() const {
    char buf[100];
    sprintf(buf, "(%.11g,%.11g)", _real, _imag);
    return string(buf);
}

ostream& operator<<(ostream& os, const Complex& x) {
    os << x.to_string();
    return os;
}
