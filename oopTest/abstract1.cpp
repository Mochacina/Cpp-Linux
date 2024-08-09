#include <iostream>
using namespace std;

/*
순수 가상 함수(pure virtual function)는 C++에서 객체 지향 프로그래밍의 다형성을 구현하기 위해 사용되는 함수입니다.
순수 가상 함수는 기초 클래스(추상 클래스)에서 선언되지만, 그 클래스 자체에서는 정의되지 않고, 파생 클래스에서 반드시 정의(구현)해야 합니다.
*/

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
