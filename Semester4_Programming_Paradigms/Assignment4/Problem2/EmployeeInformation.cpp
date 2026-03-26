#include <iostream>
#include <string>

namespace EmployeeInformationSystem {

class Person {
  protected:
    std::string m_name;
    int m_age;
    std::string m_gender;

  public:
    Person(std::string name = "N/A", int age = 0, std::string gender = "N/A")
        : m_name(name), m_age(age), m_gender(gender) {}

    virtual void read() {
        std::cout << "Enter name: ";
        std::getline(std::cin, m_name);
        std::cout << "Enter age: ";
        std::cin >> m_age;
        std::cout << "Enter gender: ";
        std::cin >> m_gender;
    }

    virtual void display() const {
        std::cout << "Name: " << m_name << std::endl
                  << "Age: " << m_age << std::endl
                  << "Gender: " << m_gender << std::endl;
    }
};
class Employee : virtual public Person {
  protected:
    int m_employee_ID;
    double m_salary;

  public:
    Employee(std::string name = "N/A", int age = 0, std::string gender = "N/A",
             int employee_ID = -1, double salary = 0)
        : Person(name, age, gender), m_employee_ID(employee_ID),
          m_salary(salary) {}

    void read() override {
        std::cout << "Enter employee ID: ";
        std::cin >> m_employee_ID;
        std::cout << "Enter employee salary: ";
        std::cin >> m_salary;
    }

    void display() const override {
        std::cout << "Employee ID: " << m_employee_ID << std::endl
                  << "Salary: " << m_salary << std::endl;
    }
};
class Specialist : virtual public Person {
  protected:
    std::string m_department;
    std::string m_skillset;

  public:
    Specialist(std::string name = "N/A", int age = 0,
               std::string gender = "N/A", std::string department = "N/A",
               std::string skillset = "N/A")
        : Person(name, age, gender), m_department(department),
          m_skillset(skillset) {}

    void read() override {
        std::cout << "Enter department: ";
        std::getline(std::cin, m_department);
        std::cout << "Enter skillset: ";
        std::getline(std::cin, m_skillset);
    }

    void display() const override {
        std::cout << "Department: " << m_department << std::endl
                  << "Skillset: " << m_skillset << std::endl;
    }
};
class Developer : public Employee, public Specialist {
  protected:
    std::string m_project;
    int m_Years_Of_Experience;

  public:
    Developer(std::string name = "N/A", int age = 0, std::string gender = "N/A",
              int employee_ID = -1, double salary = 0,
              std::string department = "N/A", std::string skillset = "N/A",
              std::string project = "N/A", int Years_Of_Experience = 0)
        : Person(name, age, gender),
          Employee(name, age, gender, employee_ID, salary),
          Specialist(name, age, gender, department, skillset),
          m_project(project), m_Years_Of_Experience(Years_Of_Experience) {}

    void read() override {
        Person::read();
        Employee::read();
        std::cin.ignore();
        Specialist::read();
        std::cout << "Enter project: ";
        std::getline(std::cin, m_project);
        std::cout << "Enter years of experience: ";
        std::cin >> m_Years_Of_Experience;
    }

    void display() const override {
        Person::display();
        Employee::display();
        Specialist::display();
        std::cout << "Project: " << m_project << std::endl
                  << "Years of Experience: " << m_Years_Of_Experience
                  << std::endl;
    }
};

class SystemAdmin : public Employee {
  protected:
    int m_WorkLoad; // workload in number of server tickets
  public:
    SystemAdmin(std::string name = "N/A", int age = 0,
                std::string gender = "N/A", int employee_ID = -1,
                double salary = 0.0, int WorkLoad = 0)
        : Person(name, age, gender),
          Employee(name, age, gender, employee_ID, salary),
          m_WorkLoad(WorkLoad) {}

    void read() override {
        Person::read();
        Employee::read();

        std::cout
            << "Enter workLoad (number of server tickets) as an integer: ";
        std::cin >> m_WorkLoad;
    }

    void display() const override {
        Person::display();
        Employee::display();

        std::cout << "WorkLoad: " << m_WorkLoad << std::endl;
    }
};

class Trainee : public Specialist {
  protected:
    int m_duration; // duration in days
    double m_stipend;

  public:
    Trainee(std::string name = "N/A", int age = 0, std::string gender = "N/A",
            std::string department = "N/A", std::string skillset = "N/A",
            int duration = 0, int stipend = 0)
        : Person(name, age, gender),
          Specialist(name, age, gender, department, skillset),
          m_duration(duration), m_stipend(stipend) {};

    void read() override {
        Person::read();
        std::cin.ignore();
        Specialist::read();

        std::cout << "Enter duration in days: ";
        std::cin >> m_duration;
        std::cout << "Enter stipend in INR: ";
        std::cin >> m_stipend;
    }

    void display() const override {
        Person::display();
        Specialist::display();

        std::cout << "Duration: " << m_duration << " days" << std::endl
                  << "Stipend: " << m_stipend << std::endl;
    }
};
} // namespace EmployeeInformationSystem
int main() {
    using namespace std;
    using namespace EmployeeInformationSystem;

    Developer dev("Alice Johnson", 29, "Female", 1001, 95000.0, "Engineering",
                  "C++, Python, React", "Inventory Management System", 5);

    SystemAdmin admin("Bob Smith", 35, "Male", 1002, 72000.0, 14);

    Trainee trainee("Carol Das", 22, "Female", "Data Science", "Python, SQL",
                    90, 15000);

    cout << "Developer: " << endl;
    dev.display();
    cout << "---------------------" << endl;
    cout << "SystemAdmin: " << endl;
    admin.display();
    cout << "---------------------" << endl;
    cout << "Trainee: " << endl;
    trainee.display();
    cout << "---------------------" << endl;

    cout << "Developer: " << endl;
    Developer dev2;
    dev2.read();
    cout << "---------------------" << endl;
    dev2.display();
    cout << "---------------------" << endl;

    cin.ignore();
    cout << "Trainee: " << endl;
    Trainee t;
    t.read();
    cout << "---------------------" << endl;
    t.display();
    cout << "---------------------" << endl;

    cout << "SystemAdmin: " << endl;
    SystemAdmin s;
    cin.ignore();
    s.read();
    cout << "---------------------" << endl;
    s.display();
    cout << "---------------------" << endl;

    return 0;
}
