class Complex {
private:
	float re, im;
public:
	Complex() : re(0.0), im (0.0) {}
	Complex(float r, float i) : re(r), im(i) {}
	

	float get_re() const { return  re; }
	float get_im() const { return im; }

	void set_re(float re) { this->re = re; }
	void set_im(float im) { this->im = im; }

	Complex operator + (const Complex&);
	Complex operator - (const Complex&);
	Complex operator - ();
	Complex& operator ++ ();
	Complex& operator ++ (int);
};