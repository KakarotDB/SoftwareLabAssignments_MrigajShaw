#include <iostream>

namespace Complex{
	class ComplexNumber {
		int m_real;
		int m_imaginary;

		public:
			ComplexNumber(int real = 0, int imaginary = 0) : m_real(real), m_imaginary(imaginary) {}

			ComplexNumber(const ComplexNumber &other) {
				m_real = other.m_real;
				m_imaginary = other.m_imaginary;
			}

			ComplexNumber operator=(const ComplexNumber &other) {
				if(this != &other) {
					m_real = other.m_real;
					m_imaginary = other.m_imaginary;
				}
				return *this;
			}

			ComplexNumber operator+(const ComplexNumber &other) {
				return ComplexNumber(m_real + other.m_real, m_imaginary + other.m_imaginary);
			}

			void display() const {
				std::cout << m_real << "+" << m_imaginary << "i" << std::endl;
			}

			friend ComplexNumber operator-(const ComplexNumber &first, const ComplexNumber &second);
	};

	ComplexNumber operator-(const ComplexNumber &first, const ComplexNumber &second) {
		return ComplexNumber(first.m_real - second.m_real, first.m_imaginary - second.m_imaginary);
	}
}

int main() {
	using namespace std;
	using namespace Complex;
	ComplexNumber c1(1,1);
	ComplexNumber c2(2,2);
	cout << "c1 : ";
	c1.display();
	cout << "c2 : ";
	c2.display();

	ComplexNumber c3;
	c3 = c2 - (2, 3);
	cout << "c3 : "; c3.display();

	return 0;
}
