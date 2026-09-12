#pragma once
#include <iostream>

class Complex {
private:
    float re, im;
public:
    Complex() : re(0.0), im(0.0) {}
    Complex(float r, float i) : re(r), im(i) {}
    Complex(float r) : re(r), im(0) {}

    float get_re() const { return  re; }
    float get_im() const { return im; }

    void set_re(float re) { this->re = re; }
    void set_im(float im) { this->im = im; }

    Complex operator+(const Complex& ) const;
    Complex operator-(const Complex& ) const;
    Complex operator*(const Complex& ) const;
    Complex operator/(const Complex& ) const;

    Complex operator-() const;

    Complex& operator++();
    Complex operator++(int);

    bool operator==(const Complex& ) const;
    bool operator!=(const Complex& ) const;

    friend std::ostream& operator<<(std::ostream& os, const Complex& tmp);
    friend std::istream& operator>>(std::istream& is, Complex& tmp);
};