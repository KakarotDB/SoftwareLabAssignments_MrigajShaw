#include <iostream>

#define sizeExtend 16

const int UpperBound = (int)1e5;

namespace StackSystem {
template <typename T> class GrowingStack {
    T *array;
    int top;
    int currentCapacity;
    int maxLimit;

  public:
    GrowingStack(int n = 10);
    ~GrowingStack();
    GrowingStack(const GrowingStack<T> &other);
    GrowingStack<T> &operator=(const GrowingStack<T> &other);

    bool isEmpty() const { return top == -1; }
    bool isFull() const { return top == currentCapacity - 1; }

    T getTop() const {
        if (isEmpty())
            return T(); // Return default constructed value
        return array[top];
    }

    int getCapacity() const { return currentCapacity; }

    bool inflate(int amount = sizeExtend);
    bool push(T value);
    bool pop(T &poppedValue);
    void display() const;
};

// Constructor
template <typename T> GrowingStack<T>::GrowingStack(int n) {
    if (n <= 0)
        n = 10;
    currentCapacity = n;
    maxLimit = UpperBound;
    array = new T[currentCapacity]();
    top = -1;
}

// Destructor
template <typename T> GrowingStack<T>::~GrowingStack() { delete[] array; }

// Copy Constructor : Deep Copy
template <typename T>
GrowingStack<T>::GrowingStack(const GrowingStack<T> &other) {
    currentCapacity = other.currentCapacity;
    maxLimit = other.maxLimit;
    top = other.top;

    array = new T[currentCapacity];

    for (int i = 0; i <= top; i++)
        array[i] = other.array[i];
}

// Assignment operator overloading
template <typename T>
GrowingStack<T> &GrowingStack<T>::operator=(const GrowingStack<T> &other) {
    if (this == &other)
        return *this;

    delete[] array;

    currentCapacity = other.currentCapacity;
    maxLimit = other.maxLimit;
    top = other.top;

    array = new T[currentCapacity];

    for (int i = 0; i <= top; i++)
        array[i] = other.array[i];

    return *this;
}

template <typename T> bool GrowingStack<T>::inflate(int amount) {
    if (currentCapacity >= maxLimit) {
        return false;
    }

    int newCapacity = currentCapacity + amount;

    if (newCapacity > maxLimit)
        newCapacity = maxLimit;

    if (newCapacity <= currentCapacity)
        return false;

    T *newArray = new T[newCapacity];
    for (int i = 0; i <= top; i++)
        newArray[i] = array[i];

    delete[] array;

    array = newArray;
    currentCapacity = newCapacity;

    return true;
}

template <typename T> bool GrowingStack<T>::push(T value) {
    if (isFull()) {
        if (!inflate()) {
            return false;
        }
    }

    array[++top] = value;
    return true;
}

template <typename T> bool GrowingStack<T>::pop(T &poppedValue) {
    if (isEmpty()) {
        return false;
    }
    poppedValue = array[top--];
    array[top + 1] = T();
    return true;
}

template <typename T> void GrowingStack<T>::display() const {
    std::cout << "[ ";
    for (int i = 0; i <= top; i++)
        std::cout << array[i] << " ";
    std::cout << "]\n";
}
} // namespace StackSystem

int main() {
    using namespace std;
    using namespace StackSystem;

    int n = 10, poppedValue = 0;

    GrowingStack<int> stack1, stack2;

    for (int i = 0; i < n; i++)
        stack1.push(i + 1);
    for (int i = 0; i < n; i++)
        stack2.push(i + 11);

    cout << "Stack 1: ";
    stack1.display();
    cout << "Stack 2: ";
    stack2.display();

    GrowingStack<int> stack3;

    for (int i = 0; i < 2 * n; i++) {
        bool success = false;
        if (i % 2 == 0) {
            success = stack1.pop(poppedValue);
        } else {
            success = stack2.pop(poppedValue);
        }
        if (success) {
            stack3.push(poppedValue);
        }
    }

    cout << "Stack 3: ";
    stack3.display();

    GrowingStack<int> stack4 = stack3;

    cout << "Stack4 made using copy constructor (new growing stack created "
            "from existing one): \n";
    stack4.display();

    cout
        << "Stack4 updated using assignment operator overloading from stack2: ";
    stack4 = stack2;
    stack4.display();
    cout << "Stack2: ";
    stack2.display();

    // Demonstration with another type (double)
    cout << "\nDouble Stack Demo \n";
    GrowingStack<double> doubleStack;
    doubleStack.push(1.1);
    doubleStack.push(2.2);
    doubleStack.push(3.3);
    cout << "Double Stack: ";
    doubleStack.display();

    return 0;
}
