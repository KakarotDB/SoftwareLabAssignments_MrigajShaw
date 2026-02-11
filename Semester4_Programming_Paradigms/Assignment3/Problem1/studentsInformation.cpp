#include <fstream>
#include <iostream>
#include <string>

namespace studentManagementSystem {
class Student {
    std::string m_name;
    int m_age;
    std::string m_department;
    int m_year;

  public:
    Student() {
        m_name = "";
        m_age = 0;
        m_department = "";
        m_year = 0;
    }

    void ReadStudentData(std::string name, int age, std::string department,
                         int year) {
        m_name = name;
        m_age = age;
        m_department = department;
        m_year = year;
    }

    bool ReadStudentData(std::ifstream &file) {
        if (file.is_open()) {
            file >> m_name >> m_age >> m_department >> m_year;
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
            fileOutput << m_name << " " << m_age << " " << m_department << " "
                       << m_year << " " << std::endl;
            return true;
        } else
            return false;
    }
};
} // namespace studentManagementSystem

int main() {
    using namespace studentManagementSystem;

    Student s1;
    s1.ReadStudentData("Mrigaj", 20, "CST", 2028);
    s1.PrintStudentData();

    std::ofstream file("students.txt");

    if (s1.PrintStudentData(file))
        std::cout << "Succesfully wrote student data to file students.txt"
                  << std::endl;
    else {
        std::cout << "[ERROR] Could not write to file!" << std::endl;
        return -1;
    }

    file.close();

    Student s2;

    std::ifstream inputFile("students.txt");

    if (s2.ReadStudentData(inputFile)) {
        std::cout << "[SUCCESS] Data read from file into s2" << std::endl;
    } else {
        std::cout << "[ERROR] Could not read from the file" << std::endl;
        return -1;
    }

    inputFile.close();

    std::cout << "Student details loaded from file: " << std::endl;
    s2.PrintStudentData();

    return 0;
}
