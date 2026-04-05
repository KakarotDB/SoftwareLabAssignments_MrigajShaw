#include <chrono>
#include <iostream>
#include <thread>

namespace FleetManagementSystem {
enum class VehicleType { CAR, TRUCK, BUS };

class Vehicle {
  protected:
    int m_wheels;
    int m_seats;
    std::string m_fuel_type;
    int m_maximum_fuel_capacity;
    int m_current_fuel;
    int m_maximum_speed;
    int m_total_distance_travelled;
    std::string m_registration_number;

  public:
    Vehicle(int wheels, int seats, std::string fuel_type,
            int maximum_fuel_capacity, int maximum_speed,
            std::string registration_number)
        : m_wheels(wheels), m_seats(seats), m_fuel_type(fuel_type),
          m_maximum_fuel_capacity(maximum_fuel_capacity), m_current_fuel(0),
          m_maximum_speed(maximum_speed), m_total_distance_travelled(0),
          m_registration_number(registration_number) {}
    virtual ~Vehicle() = default;

    // getters
    int getWheels() const { return m_wheels; }
    int getSeats() const { return m_seats; }
    std::string getFuelType() const { return m_fuel_type; }
    int getMaxFuelCapacity() const { return m_maximum_fuel_capacity; }
    int getCurrentFuel() const { return m_current_fuel; }
    int getMaxSpeed() const { return m_maximum_speed; }
    int getTotalDistance() const { return m_total_distance_travelled; }
    std::string getRegistrationNumber() const { return m_registration_number; }

    // setters
    void setMaxSpeed(int speed) {
        if (speed > 0) {
            m_maximum_speed = speed;
        } else {
            std::cout << "[ERROR] Speed must be greater than 0.\n";
        }
    }
    void setRegistrationNumber(std::string regNum) {
        if (!regNum.empty()) {
            m_registration_number = regNum;
        } else {
            std::cout << "[ERROR] Registration number cannot be blank.\n";
        }
    }

    // action methods
    bool refuel(int amount) {
        if (amount < 0) {
            std::cout << "[ERROR] Cannot refuel by a negative amount!\n";
            return false;
        }

        if (m_current_fuel + amount <= m_maximum_fuel_capacity) {
            m_current_fuel += amount;
            return true;
        } else
            return false;
    }
    void addDistance(int distance) {
        if (distance > 0)
            m_total_distance_travelled += distance;
    }

    virtual void start();
    virtual void stop();
    virtual void displayInfo() const;
    virtual VehicleType getType() const = 0;
    //	virtual void saveInfo() const;
    //	virtual void loadInfo();
};

void Vehicle::start() {
    std::cout << "Starting vehicle....";

    char spin[] = {'|', '/', '-', '\\'};

    for (int i = 0; i < 30; i++) {
        std::cout << "\b" << spin[i % 4] << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << "\b \bStarted!" << std::endl;
}

void Vehicle::stop() {
    std::cout << "Stopping vehicle....";
    char spin[] = {'|', '/', '-', '\\'};

    for (int i = 0; i < 30; i++) {
        std::cout << "\b" << spin[i % 4] << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    };

    std::cout << "\b \bStopped!" << std::endl;
}

void Vehicle::displayInfo() const {
    std::cout << "Registration number: " << m_registration_number << std::endl
              << "| Wheels: " << m_wheels << std::endl
              << "| Seats: " << m_seats << std::endl
              << "| Fuel Type: " << m_fuel_type << std::endl
              << "| Maximum Fuel Capacity: " << m_maximum_fuel_capacity
              << std::endl
              << "| Current Fuel Amount: " << m_current_fuel << std::endl
              << "| Maximum speed: " << m_maximum_speed << std::endl
              << "| Total Distance Travelled: " << m_total_distance_travelled
              << std::endl;
}
} // namespace FleetManagementSystem

int main() {
    using namespace FleetManagementSystem;
    using namespace std;
}
