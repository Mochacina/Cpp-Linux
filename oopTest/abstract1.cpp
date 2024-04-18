#include <iostream>
using namespace std;

class Shape {
public:
    virtual void draw() = 0;  // 순수 가상 함수
};

class Circle : public Shape {
public:
    void draw() override {
        cout << "Drawing circle" << endl;
    }
};

class Rectangle : public Shape {
public:
    void draw() override {
        cout << "Drawing rectangle" << endl;
    }
};

int main() {
    Circle circle;
    Rectangle rectangle;

    circle.draw();
    rectangle.draw();

    return 0;
}
