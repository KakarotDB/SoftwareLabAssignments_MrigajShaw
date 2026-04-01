#include <iostream>
#include <thread>
#include <chrono>

namespace FleetManagementSystem{
class Vehicle {
	int m_wheels;
	int m_seats;
	std::string m_fuel_type;
	int m_maximum_fuel_capacity;
	int m_current_fuel;
	int m_maximum_speed;
	int m_total_distance_travelled;
	std::string m_registration_number;

	public:

	Vehicle(int wheels = 0, int seats = 0, std::string fuel_type = "N/A", int maximum_fuel_capacity = 0, int current_fuel = 0, int maximum_speed = 0, int total_distance_travelled = 0, std::string registration_number = "N/A")
		: m_wheels(wheels), m_seats(seats), m_fuel_type(fuel_type), m_maximum_fuel_capacity(maximum_fuel_capacity), m_current_fuel(current_fuel), m_maximum_speed(maximum_speed), m_total_distance_travelled(total_distance_travelled), m_registration_number(registration_number) {}

	virtual void start(); 
	virtual void stop();
	virtual void displayInfo() const; 
//	virtual void saveInfo() const;
//	virtual void loadInfo();
};

void Vehicle::start() {
	std::cout << "Starting vehicle....";

	char spin[] = {
		'|', '/', '-', '\\'
	};

	for(int i = 0; i < 30; i++) {
		std::cout << "\b" << spin[i % 4] << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	std::cout << "\b \bStarted!" << std::endl;
}

void Vehicle::stop() {
	std::cout << "Stopping vehicle....";
	char spin[] = {
		'|', '/', '-', '\\'
	};
	
	for(int i = 0; i < 30; i++) {
		std::cout << "\b" << spin[i % 4] << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	};

	std::cout << "\b \bStopped!" << std::endl;
}

void Vehicle::displayInfo() const {
	std::cout << "Number of wheels: " << m_wheels << std::endl;
	std::cout << "Number of seats: " << m_seats << std::endl;
	std::cout << "Fuel type: " << m_fuel_type << std::endl;
	std::cout << "Maximum fuel capacity(L): " << m_maximum_fuel_capacity << std::endl;
	std::cout << "Current fuel amount((L): " << m_current_fuel << std::endl;
	std::cout << "Maximum speed(kmph): " << m_maximum_speed << std::endl;
	std::cout << "Total distance travelled(km): " << m_total_distance_travelled << std::endl;
	std::cout << "Registration number: " << m_registration_number << std::endl;
}
}

int main() {
	using namespace FleetManagementSystem;
	Vehicle p(4, 4, "Diesel", 10, 5, 200, 50, "XX000001");
	p.start();
	p.displayInfo();
	p.stop();
}
