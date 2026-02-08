#include <iostream>
#define sizeExtend 16
#define Upper_Bound (int)1e5
using std::cin, std::cout, std::endl;

struct Point {
    int x, y;
};

namespace StackSystem {

struct GrowingStack {
    void **array; // Using void* to hold any data type
    int top;
    int currentSize;
    int currentMaxSize;
    int upperBound;
};

bool initializeStack(GrowingStack &s, const int n) {
    s.array = new void *[n];
    if (s.array == NULL)
        return false;
    s.top = -1;
    s.currentSize = 0;
    s.currentMaxSize = n;
    s.upperBound = Upper_Bound;
    return true;
}

bool inflate(GrowingStack &s, int = sizeExtend);

inline bool isEmpty(const GrowingStack &s) { return s.top == -1; }

inline bool isFull(const GrowingStack &s) {
    return s.currentSize == s.currentMaxSize;
}

inline bool isMaxCapacity(const GrowingStack &s) {
    return s.currentSize == s.upperBound;
}

bool inflate(GrowingStack &s, int amount) {
    if (s.currentMaxSize >= s.upperBound)
        return false;

    int newCapacity = s.currentSize + amount;

    void **newStackArray = new void *[newCapacity];
    if (!newStackArray)
        return false;

    for (int i = 0; i < s.currentSize; i++)
        newStackArray[i] = s.array[i];

    // Initialize new slots to NULL
    for (int i = s.currentSize; i < newCapacity; i++)
        newStackArray[i] = NULL;

    delete[] s.array;
    s.array = newStackArray;
    s.currentMaxSize = newCapacity;

    return true;
}

// Accepts a pointer to any type
bool push(GrowingStack &s, void *value) {
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

bool pop(GrowingStack &s, void *&poppedValue) {
    if (isEmpty(s))
        return false;
    poppedValue = s.array[s.top];
    s.array[s.top--] = NULL;
    s.currentSize--;
    return true;
}

} // namespace StackSystem

int main() {
    using namespace StackSystem;

    cout << "Integer Stack" << endl;
    int n = 5;
    GrowingStack intStack;
    initializeStack(intStack, n);

    for (int i = 1; i <= 5; i++) {
        push(intStack, new int(i * 10));
    }

    void *poppedVal;
    cout << "Popping ints: ";
    while (!isEmpty(intStack)) {
        pop(intStack, poppedVal);
        cout << *(int *)poppedVal << " "; // Cast back to int* and dereference
        delete (int *)poppedVal;
    }
    cout << endl << endl;

    cout << "Float Stack " << endl;
    GrowingStack floatStack;
    initializeStack(floatStack, 5);

    push(floatStack, new float(1.1f));
    push(floatStack, new float(2.2f));
    push(floatStack, new float(3.3f));

    cout << "Popping floats: ";
    while (!isEmpty(floatStack)) {
        pop(floatStack, poppedVal);
        cout << *(float *)poppedVal << " ";
        delete (float *)poppedVal;
    }
    cout << endl << endl;

    cout << "Struct Stack" << endl;
    GrowingStack pointStack;
    initializeStack(pointStack, 5);

    Point *p1 = new Point{1, 2};
    Point *p2 = new Point{3, 4};
    push(pointStack, p1);
    push(pointStack, p2);

    cout << "Popping structs: ";
    while (!isEmpty(pointStack)) {
        pop(pointStack, poppedVal);
        Point *p = (Point *)poppedVal;
        cout << p->x << p->y << " ";
        delete p;
    }
    cout << endl << endl;

    return 0;
}
