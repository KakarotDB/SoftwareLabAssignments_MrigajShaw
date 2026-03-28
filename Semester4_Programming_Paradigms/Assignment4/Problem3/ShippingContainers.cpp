#include <iostream>
#define pi 3.14

namespace WarehouseContainers {

class Container {
  public:
    virtual void read() = 0;
    virtual double Volume() const = 0;
    virtual ~Container() = default;
};

class Box : public Container {
    double m_length, m_breadth, m_height;

  public:
    Box(double length = 0.0, double breadth = 0.0, double height = 0.0)
        : m_length(length), m_breadth(breadth), m_height(height) {}

    void read() override {
        std::cout << "Enter length: ";
        std::cin >> m_length;

        std::cout << "Enter breadth: ";
        std::cin >> m_breadth;

        std::cout << "Enter height: ";
        std::cin >> m_height;
    }

    double Volume() const override { return m_length * m_breadth * m_height; }
};

class Cylinder : public Container {
    double m_radius, m_height;

  public:
    Cylinder(double radius = 0.0, double height = 0.0)
        : m_radius(radius), m_height(height) {}

    void read() override {
        std::cout << "Enter radius: ";
        std::cin >> m_radius;
        std::cout << "Enter height: ";
        std::cin >> m_height;
    }

    double Volume() const override {
        return pi * m_radius * m_radius * m_height;
    }
};

class Pyramid : public Container {
    double m_length, m_breadth, m_height;

  public:
    Pyramid(double length = 0.0, double breadth = 0.0, double height = 0.0)
        : m_length(length), m_breadth(breadth), m_height(height) {}

    void read() override {
        std::cout << "Enter base length: ";
        std::cin >> m_length;

        std::cout << "Enter base breadth: ";
        std::cin >> m_breadth;

        std::cout << "Enter height of pyramid: ";
        std::cin >> m_height;
    }

    double Volume() const override {
        return (m_length * m_breadth * m_height) / 3.0;
    }
};
} // namespace WarehouseContainers

int main() {
    using namespace std;
    using namespace WarehouseContainers;

    int n;
    cout << "All dimensions will be assumed to be in centimeters (cm)" << endl;
    cout << "How many containers are in the warehouse? ";
    cin >> n;

    Container **warehouse = new Container *[n];

    for (int i = 0; i < n; i++) {
        int choice;
        cout << "\nContainer " << i + 1
             << " type (1=Box, 2=Cylinder, 3=Pyramid): ";
        cin >> choice;

        if (choice == 1) {
            warehouse[i] = new Box();
        } else if (choice == 2) {
            warehouse[i] = new Cylinder();
        } else {
            warehouse[i] = new Pyramid();
        }

        warehouse[i]->read();
    }

    double totalVolume = 0;
    for (int i = 0; i < n; i++) {
        totalVolume += warehouse[i]->Volume();
    }

    cout << "\nTotal volume occupied: " << totalVolume << " cubic cm\n";

    for (int i = 0; i < n; i++) {
        delete warehouse[i];
    }
    delete[] warehouse;

    return 0;
}
