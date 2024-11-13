#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Car {
private:
    string make;
    string model;
    int year;
    double pricePerDay;

public:
    Car(string m, string mod, int y, double price) : make(m), model(mod), year(y), pricePerDay(price) {}

    void displayCarInfo() const {
        cout << "Make: " << make << "\n";
        cout << "Model: " << model << "\n";
        cout << "Year: " << year << "\n";
        cout << "Price per day: $" << pricePerDay << "\n";
    }

    double getPricePerDay() const {
        return pricePerDay;
    }
};

class CarRentalSystem {
private:
    vector<Car*> cars; // Store cars in memory

public:
    ~CarRentalSystem() {
        for (auto car : cars) {
            delete car;
        }
    }

    void addCar(Car* car) {
        cars.push_back(car);
        cout << "Thank you for selling your car!\n";
    }

    void removeCar(int carIndex) {
        if (carIndex >= 0 && carIndex < cars.size()) {
            delete cars[carIndex];
            cars.erase(cars.begin() + carIndex);
            cout << "The car has been rented and removed from the list.\n";
        } else {
            cout << "Invalid car index.\n";
        }
    }

    void displayAvailableCars() const {
        if (cars.empty()) {
            cout << "No cars available.\n";
        } else {
            cout << "Available cars:\n";
            for (int i = 0; i < cars.size(); ++i) {
                cout << "\nCar #" << (i + 1) << "\n";
                cars[i]->displayCarInfo();
                cout << "\n";
            }
        }
    }

    bool areCarsAvailable() const {
        return !cars.empty();
    }

    void rentCar(int carIndex, int days) {
        if (carIndex >= 0 && carIndex < cars.size()) {
            double totalCost = cars[carIndex]->getPricePerDay() * days;
            cout << "You have rented this car for " << days << " days.\n";
            cout << "Total rental cost: $" << totalCost << "\n";
            removeCar(carIndex);
        } else {
            cout << "Invalid car selection.\n";
        }
    }
};

void sellCar(CarRentalSystem& rentalSystem) {
    string make, model;
    int year;
    double pricePerDay;

    cout << "Enter make of the car: ";
    cin.ignore();
    getline(cin, make);
    cout << "Enter model of the car: ";
    getline(cin, model);
    cout << "Enter the year of manufacture: ";
    cin >> year;
    cout << "Enter price per day: $";
    cin >> pricePerDay;

    rentalSystem.addCar(new Car(make, model, year, pricePerDay));
}

int main() {
    CarRentalSystem rentalSystem;
    int choice;

    cout << "Welcome to the Car Rental System!\n";

    do {
        cout << "\nPlease select an option:\n";
        cout << "1. Rent a car\n";
        cout << "2. Sell a car\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            if (rentalSystem.areCarsAvailable()) {
                rentalSystem.displayAvailableCars();

                int carIndex, rentalDays;
                cout << "Enter the car number you want to rent: ";
                cin >> carIndex;
                cout << "Enter the number of rental days: ";
                cin >> rentalDays;

                rentalSystem.rentCar(carIndex - 1, rentalDays); // Adjust for 0-based indexing
            } else {
                cout << "No cars available for rent.\n";
            }
        } else if (choice == 2) {
            sellCar(rentalSystem);
        } else if (choice == 3) {
            cout << "Thank you for using the Car Rental System. Goodbye!\n";
        } else {
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 3);

    return 0;
}