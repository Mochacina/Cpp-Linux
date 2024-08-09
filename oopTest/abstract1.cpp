#include <iostream>
using namespace std;

/*
���� ���� �Լ�(pure virtual function)�� C++���� ��ü ���� ���α׷����� �������� �����ϱ� ���� ���Ǵ� �Լ��Դϴ�.
���� ���� �Լ��� ���� Ŭ����(�߻� Ŭ����)���� ���������, �� Ŭ���� ��ü������ ���ǵ��� �ʰ�, �Ļ� Ŭ�������� �ݵ�� ����(����)�ؾ� �մϴ�.
*/

class Shape {
public:
    virtual void draw() = 0;  // ���� ���� �Լ�
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
