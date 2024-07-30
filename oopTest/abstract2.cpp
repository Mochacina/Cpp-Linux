#include <iostream>

// 추상 클래스
class Shape {
public:
    // 순수 가상 함수들, 상속 시 반드시 구현 필요
    virtual void draw() const = 0;
    virtual double area() const = 0;
    virtual ~Shape(){
        std::cout << "Parent Destruct." << std::endl;
    }
};

// 파생 클래스
class Circle : public Shape {
public:
    Circle(double r) : radius(r) {}
    ~Circle() {
        std::cout << "Circle Destruct." << std::endl;
    }
    
    void draw() const override {
        std::cout << "Drawing a circle\n";
    }

    double area() const override {
        return 3.14159 * radius * radius;
    }

private:
    double radius;
};

class Rectangle : public Shape {
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    ~Rectangle() {
        std::cout << "Rectangle Destruct." << std::endl;
    }

    void draw() const override {
        std::cout << "Drawing a rectangle\n";
    }

    double area() const override {
        return width * height;
    }

private:
    double width, height;
};

int main() {
    Shape* shapes[2];
    shapes[0] = new Circle(5.0);
    shapes[1] = new Rectangle(4.0, 6.0);

    for (int i = 0; i < 2; ++i) {
        shapes[i]->draw();
        std::cout << "Area: " << shapes[i]->area() << std::endl;
    }

    for (int i = 0; i < 2; ++i) {
        delete shapes[i];
    }

    return 0;
}