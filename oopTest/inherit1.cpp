#include <iostream>
using namespace std;

class Vehicle {
public:
    void start() {
        cout << "Vehicle started" << endl;
    }
};

class Car : public Vehicle {
public:
    void openTrunk() {
        cout << "Trunk opened" << endl;
    }
};

class Bike : public Vehicle {
public:
    void kickStart() {
        cout << "Bike kick started" << endl;
    }
};

int main() {
    Car myCar;
    Bike myBike;

    myCar.start();   // 상속받은 메소드
    myCar.openTrunk();

    myBike.start();  // 상속받은 메소드
    myBike.kickStart();

    return 0;
}
