#include <iostream>

// 부모 클래스 Parent 정의
class Parent {
public:
    virtual void show() {  // 가상 함수 정의
        std::cout << "Parent class show function" << std::endl;
    }
    void parentOnly() {
        std::cout << "Parent class only function" << std::endl;
    }
    virtual ~Parent() {  // 가상 소멸자
        std::cout << "Parent destructor" << std::endl;
    }
};

// 자식 클래스 Child 정의
class Child : public Parent {
public:
    void show() override {  // 부모 클래스의 함수를 오버라이드
        std::cout << "Child class show function" << std::endl;
    }
    void childOnly() {
        std::cout << "Child class only function" << std::endl;
    }
    ~Child() {  // 소멸자
        std::cout << "Child destructor" << std::endl;
    }
};

int main() {
    Parent* p = new Parent();
    p->show();
    p->parentOnly();

    std::cout << "---------\n";

    Parent* pc = new Child();  // Parent 타입의 포인터로 Child 객체 생성
    pc->show();  // 다형성을 통해 Child의 show 함수 호출
    pc->parentOnly();  // Parent 클래스의 parentOnly 함수 호출
    //pc->childOnly();  // Parent 클래스에는 childOnly 함수가 없으므로 호출 불가능

    std::cout << "---------\n";

    Child* c = new Child;  // Child 객체 생성
    c->show();  // Child 클래스의 show 함수 호출
    c->parentOnly();  // Parent 클래스의 parentOnly 함수 호출
    c->childOnly();  // Child 클래스의 childOnly 함수 호출

    std::cout << "---------\n";

    delete p;   // 할당된 메모리 해제, Parent의 소멸자 호출
    delete pc;  // 할당된 메모리 해제, Child의 소멸자를 호출한 후 Parent의 소멸자 호출
    delete c;  // 할당된 메모리 해제, Child의 소멸자를 호출한 후 Parent의 소멸자 호출
    return 0;
}
