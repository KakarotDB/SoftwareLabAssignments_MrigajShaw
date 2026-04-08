#include <iostream>
#define pi 3.14

class Shape {
	public:
		virtual void read() = 0;
		virtual void display() const = 0;
		virtual double area() const = 0;
		virtual ~Shape() = default;
};

class Triangle : public virtual Shape {
	double m_base, m_height;

	public:
		Triangle(double base = 0.0, double height = 0.0) : m_base(base), m_height(height) {}
		void read() override;
		void display() const override;
		double area() const override { return 0.5 * m_base * m_height; }
};

void Triangle::read() {
	std::cout << "Enter base: ";
	std::cin >> m_base;
	std::cout << "Enter height: ";
	std::cin >> m_height;
}

void Triangle::display() const {
	std::cout << "Triangle: " << "\n";
	std::cout << "| base = " << m_base << "\n";
	std::cout << "| height = " << m_height << "\n";
}

class Rectangle : public virtual Shape {
	double m_length, m_breadth;

	public:
		Rectangle(double length = 0.0, double breadth = 0.0): m_length(length), m_breadth(breadth) {}
		void read() override;
		void display() const override;
		double area() const override { return m_length * m_breadth; }
};

void Rectangle::read() {
	std::cout << "Enter length: ";
	std::cin >> m_length;
	std::cout << "Enter breadth: ";
	std::cin >> m_breadth;
}

void Rectangle::display() const {
	std::cout << "Rectangle: " << "\n";
	std::cout << "| length = " << m_length << "\n";
	std::cout << "| breadth = " << m_breadth << "\n";
}

class Circle : public virtual Shape {
	double m_radius;

	public:
		Circle(double radius = 0.0) : m_radius(radius) {}
		void read() override;
		void display() const override;
		double area() const override { return pi * m_radius * m_radius; } 
};

void Circle::read() {
	std::cout << "Enter radius: ";
	std::cin >> m_radius;
}

void Circle::display() const {
	std::cout << "Circle: " << "\n";
	std::cout << "| radius = " << m_radius << "\n";
}

class ShapeStack {
	Shape **m_stack;
	int m_size;
	int m_top;

	public:
		ShapeStack(int size = 0): m_size(size), m_top(-1) {
			m_stack = new int*[size];

			for(int i = 0; i < size; i++) {
				m_stack[i] = nullptr;
			}
		}

		~ShapeStack() {
			for(int i = 0; i < size; i++) {
				delete[] stack[i];
			}

			delete[] stack;
		}

		bool push(Shape *shape);
		bool pop(Shape *shape);
		void display() const;
		double totalArea() const;
}

bool ShapeStack::push(Shape *shape) {
	if(shape == nullptr || m_top + 1 == m_size) return false;

	m_stack[++top] = Shape;
	return true;
}

bool ShapeStack::pop(Shape *shape) {
	if(top == -1 || shape == nullptr) return false;
	
	shape = stack[top];
	delete stack[top];
	
	top--;
	return true;
}

void display() const {
	std::cout << "Current stack:
}
