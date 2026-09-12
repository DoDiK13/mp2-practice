#include "../include/complex.hpp"

Complex Complex:: operator + (const Complex& tmp) const  {
	return Complex(this->re + tmp.re, this->im + tmp.im);
}

Complex Complex:: operator - (const Complex& tmp) const{
	return Complex(this->re - tmp.re, this->im - tmp.im);
}

Complex Complex ::operator * (const Complex& tmp) const {
	return Complex(
		re * tmp.re - im * tmp.im,
		re * tmp.im + im * tmp.re
	);
}

Complex Complex::operator/(const Complex& tmp) const {
	float denom = tmp.re * tmp.re + tmp.im * tmp.im;
	if (denom == 0.0) {
		throw "Деление на ноль";
	}
	return Complex(
		(re * tmp.re + im * tmp.im) / denom,
		(im * tmp.re - re * tmp.im) / denom
	);
}

Complex Complex:: operator - ()const  {
	return Complex(-this->re, -this->im);
}

Complex& Complex:: operator++() {
	this->re++;
	this->im++;
	return *this;
}

Complex Complex:: operator++(int) {
	Complex old =  *this;
	++(*this);
	return old;
}

bool Complex::operator == (const Complex& tmp) const {
	return (this->re == tmp.re) && (this->im == tmp.im);
}

bool Complex::operator != (const Complex& tmp) const {
	return (this->re != tmp.re) || (this->im != tmp.im);
}

std::ostream& operator <<(std::ostream& os, const Complex& tmp) {
	os << "Цалая чатсь: " << tmp.re << std::endl;
	os << "Мнимая чатсь: " << tmp.im << std::endl;
	return os;
}

std::istream& operator>>(std::istream& is, Complex& tmp) {
	is >> tmp.re;
	is >> tmp.im;
	return is;
}