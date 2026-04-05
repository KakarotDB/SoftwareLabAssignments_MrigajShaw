#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
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
            std::cout << "Speed must be greater than 0.\n";
        }
    }
    void setRegistrationNumber(std::string regNum) {
        if (!regNum.empty()) {
            m_registration_number = regNum;
        } else {
            std::cout << "Registration number cannot be blank.\n";
        }
    }

    // action methods
    bool refuel(int amount) {
        if (amount < 0) {
            std::cout << "Cannot refuel by a negative amount!\n";
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
    virtual void saveInfo(std::ofstream &out) const;
    virtual void loadInfo(std::ifstream &in);

  protected:
    void showSpinner() const;
    std::string getVehicleTypeName() const;
};

std::string Vehicle::getVehicleTypeName() const {
    switch (getType()) {
    case VehicleType::CAR:
        return "Car";
    case VehicleType::TRUCK:
        return "Truck";
    case VehicleType::BUS:
        return "Bus";
    default:
        return "Vehicle";
    }
}

void Vehicle::showSpinner() const {
    char spin[] = {'|', '/', '-', '\\'};
    for (int i = 0; i < 30; i++) {
        std::cout << "\b" << spin[i % 4] << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void Vehicle::start() {
    std::cout << "Starting " << getVehicleTypeName() << "....";
    showSpinner();
    std::cout << "\b \bStarted!" << std::endl;
}

void Vehicle::stop() {
    std::cout << "Stopping " << getVehicleTypeName() << "....";
    showSpinner();
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

void Vehicle::saveInfo(std::ofstream &out) const {
    // We separate data with spaces to make it easy to read with std::ifstream
    out << static_cast<int>(getType()) << " " << m_wheels << " " << m_seats
        << " " << m_fuel_type << " " << m_maximum_fuel_capacity << " "
        << m_current_fuel << " " << m_maximum_speed << " "
        << m_total_distance_travelled << " " << m_registration_number;
}

void Vehicle::loadInfo(std::ifstream &in) {
    in >> m_wheels >> m_seats >> m_fuel_type >> m_maximum_fuel_capacity >>
        m_current_fuel >> m_maximum_speed >> m_total_distance_travelled >>
        m_registration_number;
}

class Car : public Vehicle {
  private:
    std::string m_car_body;

  public:
    Car(int seats = 0, std::string fuel_type = "N/A",
        int maximum_fuel_capacity = 0, int maximum_speed = 0,
        std::string registration_number = "N/A", std::string car_body = "N/A")
        : Vehicle(4, seats, fuel_type, maximum_fuel_capacity, maximum_speed,
                  registration_number),
          m_car_body(car_body) {}

    VehicleType getType() const override { return VehicleType::CAR; }

    void displayInfo() const override {
        Vehicle::displayInfo();
        std::cout << "| Car Body: " << m_car_body << "\n";
    }

    void saveInfo(std::ofstream &out) const override {
        Vehicle::saveInfo(out);
        out << " " << m_car_body << "\n";
    }

    void loadInfo(std::ifstream &in) override {
        Vehicle::loadInfo(in);
        in >> m_car_body;
    }
};

class Truck : public Vehicle {
  private:
    int m_number_axles;
    double m_cargo_capacity_tonnes;

  public:
    Truck(int wheels = 0, int seats = 0, std::string fuel_type = "N/A",
          int maximum_fuel_capacity = 0, int maximum_speed = 0,
          std::string registration_number = "N/A", int number_axles = 0,
          double cargo_capacity_tonnes = 0)
        : Vehicle(wheels, seats, fuel_type, maximum_fuel_capacity,
                  maximum_speed, registration_number),
          m_number_axles(number_axles),
          m_cargo_capacity_tonnes(cargo_capacity_tonnes) {}

    VehicleType getType() const override { return VehicleType::TRUCK; }

    void displayInfo() const override {
        Vehicle::displayInfo();
        std::cout << "| Number of Axles: " << m_number_axles << "\n";
        std::cout << "| Cargo Capacity in tonnes: " << m_cargo_capacity_tonnes
                  << "\n";
    }

    void saveInfo(std::ofstream &out) const override {
        Vehicle::saveInfo(out);
        out << " " << m_number_axles << " " << m_cargo_capacity_tonnes << "\n";
    }

    void loadInfo(std::ifstream &in) override {
        Vehicle::loadInfo(in);
        in >> m_number_axles >> m_cargo_capacity_tonnes;
    }
};

class Bus : public Vehicle {
  private:
    std::string m_route;
    int m_standing_capacity;

  public:
    Bus(int wheels = 0, int seats = 0, std::string fuel_type = "N/A",
        int maximum_fuel_capacity = 0, int maximum_speed = 0,
        std::string registration_number = "N/A", std::string route = "N/A",
        int standing_capacity = 0)
        : Vehicle(wheels, seats, fuel_type, maximum_fuel_capacity,
                  maximum_speed, registration_number),
          m_route(route), m_standing_capacity(standing_capacity) {}

    VehicleType getType() const override { return VehicleType::BUS; }

    void displayInfo() const override {
        Vehicle::displayInfo();
        std::cout << "| Route: " << m_route << "\n"
                  << "| Standing Capacity: " << m_standing_capacity << "\n";
    }

    void saveInfo(std::ofstream &out) const override {
        Vehicle::saveInfo(out);
        out << " " << m_route << " " << m_standing_capacity << "\n";
    }

    void loadInfo(std::ifstream &in) override {
        Vehicle::loadInfo(in);
        in >> m_route >> m_standing_capacity;
    }
};

class Fleet {
  private:
    Vehicle **m_vehicles;
    int m_capacity;
    int m_count;

    void resize() {
        m_capacity *= 2;
        Vehicle **new_array = new Vehicle *[m_capacity];
        for (int i = 0; i < m_count; i++) {
            new_array[i] = m_vehicles[i];
        }
        delete[] m_vehicles;
        m_vehicles = new_array;
    }

  public:
    Fleet() : m_capacity(5), m_count(0) {
        m_vehicles = new Vehicle *[m_capacity];
    }

    ~Fleet() {
        for (int i = 0; i < m_count; i++) {
            delete m_vehicles[i];
        }
        delete[] m_vehicles;
    }

    void addVehicle(Vehicle *v) {
        if (m_count == m_capacity) {
            resize();
        }
        m_vehicles[m_count++] = v;
    }

    void displayAll() const {
        for (int i = 0; i < m_count; i++) {
            m_vehicles[i]->displayInfo();
            std::cout << "\n";
        }
    }

    void startAll() const {
        for (int i = 0; i < m_count; i++) {
            m_vehicles[i]->start();
        }
    }

    void stopAll() const {
        for (int i = 0; i < m_count; i++) {
            m_vehicles[i]->stop();
        }
    }

    void saveFleet(const std::string &filename) const {
        std::ofstream out(filename);
        if (!out.is_open()) {
            std::cout << "Error saving file: " << filename << "\n";
            return;
        }
        for (int i = 0; i < m_count; i++) {
            m_vehicles[i]->saveInfo(out);
        }
        out.close();
    }

    void loadFleet(const std::string &filename) {
        std::ifstream in(filename);
        if (!in.is_open()) {
            std::cout << "Error loading file: " << filename << "\n";
            return;
        }

        // Clear existing fleet before loading
        for (int i = 0; i < m_count; i++) {
            delete m_vehicles[i];
        }
        m_count = 0;

        int typeInt;
        while (in >> typeInt) {
            VehicleType type = static_cast<VehicleType>(typeInt);
            Vehicle *v = nullptr;

            if (type == VehicleType::CAR) {
                v = new Car();
            } else if (type == VehicleType::TRUCK) {
                v = new Truck();
            } else if (type == VehicleType::BUS) {
                v = new Bus();
            }

            if (v) {
                v->loadInfo(in);
                addVehicle(v);
            }
        }
        in.close();
    }
};

} // namespace FleetManagementSystem

int main() {
    using namespace FleetManagementSystem;

    Fleet myFleet;

    // Demonstrating use of parameterized constructors
    myFleet.addVehicle(new Car(5, "Petrol", 50, 180, "CAR-123", "Sedan"));
    myFleet.addVehicle(new Truck(6, 3, "Diesel", 150, 120, "TRK-456", 2));
    myFleet.addVehicle(
        new Bus(8, 40, "Diesel", 200, 100, "BUS-789", "Route-66", 20));

    // Demonstrating use of default constructor
    myFleet.addVehicle(new Car());

    myFleet.displayAll();
    myFleet.startAll();
    myFleet.saveFleet("fleet_data.txt");

    Fleet loadedFleet;
    loadedFleet.loadFleet("fleet_data.txt");
    loadedFleet.displayAll();

    return 0;
}
