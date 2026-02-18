#include <fstream>
#include <ios>
#include <iostream>
#include <limits>
#include <string>

namespace studentManagementSystem {
class Student {
    std::string m_name;
    int m_age;
    std::string m_department;
    int m_year;
	static Student* pool;

  public:
    Student() {
        m_name = "";
        m_age = 0;
        m_department = "";
        m_year = 0;
    }

	static bool createStudentMemoryPool(int n);
	static bool deleteStudentMemoryPool();
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
            // Clears newline left by last integer read in file
            // so next student's name is read correctly
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

Student::pool = NULL;
Student::createStudentMemoryPool(int n) {
	pool = new Student [n];
}

} // namespace studentManagementSystem

int main() {
    using namespace studentManagementSystem;
    int n = 0;
    Student *students = NULL;
    std::string name;
    int age;
    std::string department;
    int year;

    std::cout << "Enter number of students: ";
    std::cin >> n;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    students = new Student[n];

    if (!students) {
        std::cout << "Memory allocation failed!" << std::endl;
        return -1;
    }

    for (int i = 0; i < n; i++) {
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

        students[i].ReadStudentData(name, age, department, year);
    }

    std::cout << "Saving students to file students.txt" << std::endl;
    std::ofstream fileOutput("students.txt");

    for (int i = 0; i < n; i++)
        students[i].PrintStudentData(fileOutput);

    fileOutput.close();

    std::cout << std::endl;

    std::cout << "Verifying data by reading back from file: " << std::endl;
    std::ifstream fileInput("students.txt");

    Student tempStudent;

    for (int i = 0; i < n; i++) {
        if (tempStudent.ReadStudentData(fileInput)) {
            tempStudent.PrintStudentData();
        }
    }

    fileInput.close();

    delete[] students;

    return 0;
}
