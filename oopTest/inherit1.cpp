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

    myCar.start();   // ��ӹ��� �޼ҵ�
    myCar.openTrunk();

    myBike.start();  // ��ӹ��� �޼ҵ�
    myBike.kickStart();

    return 0;
}
