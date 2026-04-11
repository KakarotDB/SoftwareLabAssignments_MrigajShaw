#include <iostream>
#define pi 3.14

namespace ShapeStackSystem {
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
    Triangle(double base = 0.0, double height = 0.0)
        : m_base(base), m_height(height) {}
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
    Rectangle(double length = 0.0, double breadth = 0.0)
        : m_length(length), m_breadth(breadth) {}
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
    ShapeStack(int size = 0) : m_size(size), m_top(-1) {
        m_stack = new Shape *[size];

        for (int i = 0; i < size; i++) {
            m_stack[i] = nullptr;
        }
    }

    ~ShapeStack() {
        for (int i = 0; i < m_size; i++) {
            delete m_stack[i];
        }

        delete[] m_stack;
    }

    bool push(Shape *shape);
    bool pop(Shape *shape);
    void display() const;
    double totalArea() const;
};

bool ShapeStack::push(Shape *shape) {
    if (shape == nullptr || m_top + 1 == m_size)
        return false;

    if (Triangle *t = dynamic_cast<Triangle *>(shape)) {
        m_stack[++m_top] = new Triangle(*t);
    } else if (Rectangle *t = dynamic_cast<Rectangle *>(shape)) {
        m_stack[++m_top] = new Rectangle(*t);
    } else if (Circle *t = dynamic_cast<Circle *>(shape)) {
        m_stack[++m_top] = new Circle(*t);
    } else
        return false;

    return true;
}

bool ShapeStack::pop(Shape *shape) {
    if (m_top == -1 || shape == nullptr)
        return false;

    Shape *topShape = m_stack[m_top];

    if (Triangle *topTri = dynamic_cast<Triangle *>(topShape)) {
        Triangle *destTri = dynamic_cast<Triangle *>(shape);
        if (!destTri)
            return false;
        *destTri = *topTri;
    } else if (Rectangle *topRect = dynamic_cast<Rectangle *>(topShape)) {
        Rectangle *destRect = dynamic_cast<Rectangle *>(shape);
        if (!destRect)
            return false;
        *destRect = *topRect;
    } else if (Circle *topCirc = dynamic_cast<Circle *>(topShape)) {
        Circle *destCirc = dynamic_cast<Circle *>(shape);
        if (!destCirc)
            return false;
        *destCirc = *topCirc;
    } else {
        return false;
    }

    delete m_stack[m_top];
    m_stack[m_top] = nullptr;
    m_top--;
    return true;
}

void ShapeStack::display() const {
    if (m_top == -1) {
        std::cout << "ShapeStack is empty.\n";
        return;
    }

    std::cout << "ShapeStack Contents\n";
    for (int i = m_top; i >= 0; i--) {
        std::cout << "Stack [" << i << "]: ";
        if (dynamic_cast<Triangle *>(m_stack[i])) {
            std::cout << "Triangle\n";
        } else if (dynamic_cast<Rectangle *>(m_stack[i])) {
            std::cout << "Rectangle\n";
        } else if (dynamic_cast<Circle *>(m_stack[i])) {
            std::cout << "Circle\n";
        } else {
            std::cout << "Unknown Shape\n";
        }
    }
    std::cout << "---------------------------\n";
}

double ShapeStack::totalArea() const {
    double total = 0.0;
    for (int i = 0; i <= m_top; i++) {
        total += m_stack[i]->area();
    }
    return total;
}

} // namespace ShapeStackSystem

int main() {
    using namespace ShapeStackSystem;

    ShapeStack stack(5);

    Triangle t(3.0, 4.0);
    Rectangle r(5.0, 2.0);
    Circle c(2.5);

    std::cout << "Pushing Shapes \n";
    stack.push(&t);
    stack.push(&r);
    stack.push(&c);

    stack.display();

    std::cout << "\nTotal Area in Stack: " << stack.totalArea() << "\n\n";

    std::cout << "Popping Shapes \n";

    Circle poppedCircle;
    if (stack.pop(&poppedCircle)) {
        std::cout << "Successfully popped! Details:\n";
        poppedCircle.display();
    } else {
        std::cout << "Failed to pop.\n";
    }

    Rectangle poppedRect;
    if (stack.pop(&poppedRect)) {
        std::cout << "\nSuccessfully popped! Details:\n";
        poppedRect.display();
    } else {
        std::cout << "Failed to pop.\n";
    }

    std::cout << "\nRemaining Stack \n";
    stack.display();

    return 0;
}
