#include <iostream>
#define sizeExtend 16
#define Upper_Bound (int)1e5
using std::cin, std::cout, std::endl;

struct Point {
    int x, y;
};

namespace StackSystem {

template <typename T> struct GrowingStack {
    T *array;
    int top;
    int currentSize;
    int currentMaxSize;
    int upperBound;
};

template <typename T> bool initializeStack(GrowingStack<T> &s, const int n) {
    s.array = new T[n];
    if (s.array == NULL)
        return false;
    s.top = -1;
    s.currentSize = 0;
    s.currentMaxSize = n;
    s.upperBound = Upper_Bound;
    return true;
}

template <typename T> bool inflate(GrowingStack<T> &s, int = sizeExtend);

template <typename T> inline bool isEmpty(const GrowingStack<T> &s) {
    return s.top == -1;
}

template <typename T> inline bool isFull(const GrowingStack<T> &s) {
    return s.currentSize == s.currentMaxSize;
}

template <typename T> inline bool isMaxCapacity(const GrowingStack<T> &s) {
    return s.currentSize == s.upperBound;
}

template <typename T> bool inflate(GrowingStack<T> &s, int amount) {
    if (s.currentMaxSize >= s.upperBound)
        return false;

    int newCapacity = s.currentSize + amount;

    T *newStackArray = new T[newCapacity];
    if (!newStackArray)
        return false;

    // Copy existing elements
    for (int i = 0; i < s.currentSize; i++)
        newStackArray[i] = s.array[i];

    // Initialize new slots with default value of T
    for (int i = s.currentSize; i < newCapacity; i++)
        newStackArray[i] = T{};

    delete[] s.array;
    s.array = newStackArray;
    s.currentMaxSize = newCapacity;

    return true;
}

template <typename T> bool push(GrowingStack<T> &s, const T value) {
    if (isMaxCapacity(s))
        return false;

    if (isFull(s)) {
        if (!inflate(s))
            return false;
    }

    s.array[++s.top] = value;
    s.currentSize++;
    return true;
}

template <typename T>
bool push(GrowingStack<T> &s, const T *values, int count) {
    if (count <= 0)
        return true;

    if (s.currentSize + count > s.upperBound)
        return false;

    if (s.currentSize + count > s.currentMaxSize) {
        int amountNeeded = (count > sizeExtend) ? count : sizeExtend;
        if (!inflate(s, amountNeeded)) {
            return false;
        }
    }

    for (int i = 0; i < count; i++) {
        s.array[++s.top] = values[i];
    }
    s.currentSize += count;
    return true;
}

template <typename T> bool pop(GrowingStack<T> &s, T &poppedValue) {
    if (isEmpty(s))
        return false;
    poppedValue = s.array[s.top];
    s.array[s.top--] = T{}; // T{} is calling default constructor where it will
                            // go back to its initialized value
    s.currentSize--;
    return true;
}

} // namespace StackSystem

int main() {
    using namespace StackSystem;
    cout << "Integer Stack" << endl;
    int n = 5;
    GrowingStack<int> intStack;
    initializeStack(intStack, n);

    for (int i = 1; i <= 5; i++)
        push(intStack, i * 10);

    int poppedInt;
    cout << "Popping ints: ";
    while (!isEmpty(intStack)) {
        pop(intStack, poppedInt);
        cout << poppedInt << " ";
    }
    cout << endl << endl;

    cout << "Float Stack " << endl;
    GrowingStack<float> floatStack;
    initializeStack(floatStack, 5);

    push(floatStack, 1.1f);
    push(floatStack, 2.2f);
    push(floatStack, 3.3f);

    float poppedFloat;
    cout << "Popping floats: ";
    while (!isEmpty(floatStack)) {
        pop(floatStack, poppedFloat);
        cout << poppedFloat << " ";
    }
    cout << endl << endl;

    cout << "Struct Stack" << endl;
    GrowingStack<Point> pointStack;
    initializeStack(pointStack, 5);

    Point p1 = {1, 2};
    Point p2 = {3, 4};
    push(pointStack, p1);
    push(pointStack, p2);

    Point poppedPoint;
    cout << "Popping structs: ";
    while (!isEmpty(pointStack)) {
        pop(pointStack, poppedPoint);
        cout << poppedPoint.x << poppedPoint.y << " ";
    }
    cout << endl << endl;

    /*
     * While it is possible to instantiate a GrowingStack<char*>
     * it is dangerous and we generally avoid doing it
     * Why? Because of the following reasons :
     *  - Shallow copy :
     *      - The stack would store the pointer to the character array.
     *        and not the string itself. If the original string somehow changes
     *        or goes out of scope, the stack would hold a dangling pointer
     *  - Memory management issues :
     *      - If a character array was allocating dynamically using "new",
     *        simply popping the pointer or deleting the stack array would not
     *        actually free the actual string memory which may lead to memory
     *        leaks
     *
     * Instead of GrowingStack<char*>, using the in built string class would
     * prove to be more beneficial and safer
     */

    return 0;
}
