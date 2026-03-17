#include <fstream>
#include <ios>
#include <iostream>
#include <limits>
#include <new>
#include <string>

namespace studentManagementSystem {
class Student {
    std::string m_name;
    int m_age;
    std::string m_department;
    int m_year;

    static Student *pool;
    static bool *freeSlots;
    static int poolSize;
    static int nextFreeIndex;

  public:
    Student() : m_name(""), m_age(0), m_department(""), m_year(0) {}

    static bool createStudentMemoryPool(int n = 100);
    static void deleteStudentMemoryPool();
    void *operator new(size_t size);
    void operator delete(void *pointer);

    void ReadStudentData(std::string name, int age, std::string department,
                         int year) {
        m_name = name;
        m_age = age;
        m_department = department;
        m_year = year;
    }

    bool ReadStudentData(std::ifstream &fileInput) {
        if (fileInput.is_open()) {
            std::getline(fileInput, m_name);
            fileInput >> m_age >> m_department >> m_year;
            fileInput.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return true;
        } else
            return false;
    }

    void PrintStudentData() const {
        std::cout << "---- Student Details ----" << std::endl;
        std::cout << "Name: " << m_name << std::endl;
        std::cout << "Age: " << m_age << std::endl;
        std::cout << "Department: " << m_department << std::endl;
        std::cout << "Year: " << m_year << std::endl;
        std::cout << "---------------------------" << std::endl;
    }

    bool PrintStudentData(std::ofstream &fileOutput) {
        if (fileOutput.is_open()) {
            fileOutput << m_name << std::endl;
            fileOutput << m_age << " " << m_department << " " << m_year << " "
                       << std::endl;
            return true;
        } else
            return false;
    }
};

Student *Student::pool = nullptr;
bool *Student::freeSlots = nullptr;
int Student::poolSize = 0;
int Student::nextFreeIndex = 0;

bool Student::createStudentMemoryPool(int n) {
    if (n <= 0)
        return false;

    if (pool != nullptr) {
        deleteStudentMemoryPool();
    }

    poolSize = n;
    pool = static_cast<Student *>(
        ::operator new[](n * sizeof(Student), std::nothrow));
    freeSlots = new (std::nothrow) bool[n];

    if (freeSlots == nullptr) {
        ::operator delete[](pool);
        pool = nullptr;
        poolSize = 0;
        return false;
    }

    for (int i = 0; i < n; i++) {
        freeSlots[i] = true;
    }
    nextFreeIndex = 0;

    return true;
}

void Student::deleteStudentMemoryPool() {
    if (!pool)
        return;

    ::operator delete[](pool);
    delete[] freeSlots;
    pool = nullptr;
    freeSlots = nullptr;
}

void *Student::operator new(size_t size) {
    if (pool) {
        for (int i = 0; i < poolSize; i++) {
            int index = (nextFreeIndex + i) % poolSize;
            if (freeSlots[index]) {
                freeSlots[index] = false;
                nextFreeIndex = (index + 1) % poolSize;
                return &pool[index];
            }
        }
    }
    // pool is full or doesn't exist - fall back to heap
    std::cout << "[Warning] Pool unavailable or full. Allocating from heap.\n";
    return ::operator new(size);
}

void Student::operator delete(void *pointer) {
    if (!pool || !pointer) {
        return;
    }

    Student *ptr = static_cast<Student *>(pointer);
    if (ptr < pool || ptr >= pool + poolSize) {
        ::operator delete(pointer);
        return;
    }

    int index = ptr - pool;
    freeSlots[index] = true;
}

} // namespace studentManagementSystem

int main() {
    using namespace studentManagementSystem;
    int n = 0;
    std::string name;
    int age;
    std::string department;
    int year;

    std::cout << "Enter number of students: ";
    std::cin >> n;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (!Student::createStudentMemoryPool(n)) {
        std::cout << "Memory pool creation failed!" << std::endl;
        return -1;
    }

    std::cout << "Memory pool created for " << n << " students." << std::endl;

    Student **students = new Student *[n];

    for (int i = 0; i < n; i++) {
        students[i] = new Student();
        std::cout << "Enter data for student " << i + 1 << std::endl;

        std::cout << "Name: ";
        std::getline(std::cin, name);

        std::cout << "Age: ";
        std::cin >> age;

        std::cout << "Department: ";
        std::cin >> department;

        std::cout << "Year: ";
        std::cin >> year;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        students[i]->ReadStudentData(name, age, department, year);
    }

    // Allocate one extra student beyond pool capacity to trigger heap fallback
    std::cout
        << "\nAllocating one extra student beyond pool to test fallback:\n";
    Student *extraStudent = new Student();
    extraStudent->ReadStudentData("Extra Student", 99, "TestDept", 5);
    extraStudent->PrintStudentData();

    std::cout << "\nSaving students to file students.txt" << std::endl;
    std::ofstream fileOutput("students.txt");
    for (int i = 0; i < n; i++)
        students[i]->PrintStudentData(fileOutput);
    fileOutput.close();

    std::cout << "\nVerifying data by reading back from file:" << std::endl;
    std::ifstream fileInput("students.txt");
    Student tempStudent;
    for (int i = 0; i < n; i++) {
        if (tempStudent.ReadStudentData(fileInput))
            tempStudent.PrintStudentData();
    }
    fileInput.close();

    std::cout << "\nFreeing all students from pool:" << std::endl;
    for (int i = 0; i < n; i++) {
        delete students[i];
    }
    delete extraStudent; // heap-allocated, routed to ::operator delete

    delete[] students;

    Student::deleteStudentMemoryPool();
    std::cout << "Memory pool destroyed." << std::endl;

    // Heap Fallback Demonstration
    std::cout << "\nHeap Fallback Demonstration" << std::endl;
    std::cout << "Creating a small pool of size 3 to fill it quickly."
              << std::endl;
    Student::createStudentMemoryPool(3);

    Student *d1 = new Student(); // pool slot 0
    Student *d2 = new Student(); // pool slot 1
    Student *d3 = new Student(); // pool slot 2 - pool now full

    std::cout << "Pool full. Allocating one more student:" << std::endl;
    Student *d4 = new Student(); // triggers [Warning], goes to heap

    std::cout << "\nFreeing pool slot 0 and reallocating:" << std::endl;
    std::cout << "d1 address (pool slot 0): " << (void *)d1 << std::endl;
    delete d1;
    Student *d5 = new Student(); // should reclaim slot 0
    std::cout << "d5 address (should match d1): " << (void *)d5 << std::endl;
    if (d5 == d1)
        std::cout << "[Confirmed] d5 reclaimed d1's pool slot." << std::endl;
    else
        std::cout << "[Unexpected] d5 did NOT reclaim d1's slot." << std::endl;
    delete d2;
    delete d3;
    delete d4;
    delete d5;
    Student::deleteStudentMemoryPool();
    std::cout << "End of Demonstration" << std::endl;

    return 0;
}
