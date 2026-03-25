#include <iostream>
#include <string>

namespace EmployeeInformationSystem {
	class Person {
		std::string m_name;
		int m_age;
		std::string m_gender;

		public:
			Person(std::string name = "N/A", int age = 0, std::string gender = "N/A") : m_name(name), m_age(age), m_gender(gender) {}
	}
}
