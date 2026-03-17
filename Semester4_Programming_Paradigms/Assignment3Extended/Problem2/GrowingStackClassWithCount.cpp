#include <iostream>
#define sizeExtend 16
const int UpperBound = (int)1e5;

namespace StackSystem {
class GrowingStack {
    int *array;
    int top;
    int currentCapacity;
    int maxLimit;
    bool valid;

    static int stackCount;
    static const int maxStacks = 5;

  public:
    GrowingStack(int n = 10);
    ~GrowingStack();
    GrowingStack(const GrowingStack &other);
    GrowingStack &operator=(const GrowingStack &other);

    static int getStackCount() { return stackCount; }
    bool isValid() const { return valid; }

    bool isEmpty() const { return valid && top == -1; }
    bool isFull() const { return valid && top == currentCapacity - 1; }
    int getTop() const {
        if (!valid || isEmpty())
            return -1;
        return array[top];
    }
    int getCapacity() const { return valid ? currentCapacity : 0; }
    bool inflate(int amount = sizeExtend);
    bool push(int value);
    bool pop(int &poppedValue);
    void display() const;
};

int GrowingStack::stackCount = 0;

// Constructor
GrowingStack::GrowingStack(int n) {
    if (stackCount >= maxStacks) {
        array = nullptr;
        top = -1;
        currentCapacity = 0;
        maxLimit = 0;
        valid = false;
        return;
    }
    if (n <= 0)
        n = 10;
    currentCapacity = n;
    maxLimit = UpperBound;
    array = new int[currentCapacity]();
    top = -1;
    valid = true;
    ++stackCount;
}

// Destructor
GrowingStack::~GrowingStack() {
    if (!valid)
        return;
    delete[] array;
    --stackCount;
}

// Copy Constructor
GrowingStack::GrowingStack(const GrowingStack &other) {
    if (stackCount >= maxStacks) {
        array = nullptr;
        top = -1;
        currentCapacity = 0;
        maxLimit = 0;
        valid = false;
        return;
    }
    currentCapacity = other.currentCapacity;
    maxLimit = other.maxLimit;
    top = other.top;
    array = new int[currentCapacity];
    for (int i = 0; i <= top; i++)
        array[i] = other.array[i];
    valid = true;
    ++stackCount;
}

// Assignment operator
GrowingStack &GrowingStack::operator=(const GrowingStack &other) {
    if (this == &other)
        return *this;
    if (valid)
        delete[] array;
    currentCapacity = other.currentCapacity;
    maxLimit = other.maxLimit;
    top = other.top;
    valid = other.valid;
    array = valid ? new int[currentCapacity] : nullptr;
    for (int i = 0; i <= top; i++)
        array[i] = other.array[i];
    return *this;
}

bool GrowingStack::inflate(int amount) {
    if (!valid)
        return false;
    if (currentCapacity >= maxLimit)
        return false;
    int newCapacity = currentCapacity + amount;
    if (newCapacity > maxLimit)
        newCapacity = maxLimit;
    if (newCapacity <= currentCapacity)
        return false;
    int *newArray = new int[newCapacity];
    for (int i = 0; i <= top; i++)
        newArray[i] = array[i];
    delete[] array;
    array = newArray;
    currentCapacity = newCapacity;
    return true;
}

bool GrowingStack::push(int value) {
    if (!valid)
        return false;
    if (isFull()) {
        if (!inflate())
            return false;
    }
    array[++top] = value;
    return true;
}

bool GrowingStack::pop(int &poppedValue) {
    if (!valid || isEmpty())
        return false;
    poppedValue = array[top--];
    array[top + 1] = 0;
    return true;
}

void GrowingStack::display() const {
    if (!valid) {
        std::cout << "[invalid stack]\n";
        return;
    }
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
    GrowingStack stack1, stack2;
    for (int i = 0; i < n; i++)
        stack1.push(i + 1);
    for (int i = 0; i < n; i++)
        stack2.push(i + 11);

    cout << "Stack 1: ";
    stack1.display();
    cout << "Stack 2: ";
    stack2.display();
    cout << "Stacks created so far: " << GrowingStack::getStackCount() << "\n";

    GrowingStack stack3;
    for (int i = 0; i < 2 * n; i++) {
        bool success = false;
        if (i % 2 == 0)
            success = stack1.pop(poppedValue);
        else
            success = stack2.pop(poppedValue);
        if (success)
            stack3.push(poppedValue);
    }
    cout << "Stack 3: ";
    stack3.display();

    GrowingStack stack4 = stack3;
    cout << "Stack4 made using copy constructor (new growing stack created "
            "from existing one): \n";
    stack4.display();
    cout
        << "Stack4 updated using assignment operator overloading from stack2: ";
    stack4 = stack2;
    stack4.display();
    cout << "Stack2: ";
    stack2.display();

    cout << "Total stacks alive: " << GrowingStack::getStackCount() << "\n";

    // stack1, stack2, stack3, stack4 = 4 stacks alive; limit is 5
    GrowingStack stack5;
    if (!stack5.isValid())
        cout << "stack5 creation failed: stack limit reached.\n";
    else
        cout << "Stack 5 created successfully.\n";

    // This should fail — limit of 5 already reached
    GrowingStack stack6;
    if (!stack6.isValid())
        cout << "stack6 creation failed: stack limit reached.\n";
    stack6.push(99);  // silently ignored
    stack6.display(); // prints [invalid stack]

    return 0;
}
