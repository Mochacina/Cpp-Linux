#include <iostream>

// �θ� Ŭ���� Parent ����
class Parent {
public:
    Parent (){
        std::cout << "Parent Created." << std::endl;
    }
    virtual void show() {  // ���� �Լ� ����
        std::cout << "Parent class show function" << std::endl;
    }
    void parentOnly() {
        std::cout << "Parent class only function" << std::endl;
    }
    virtual ~Parent() {  // ���� �Ҹ���
        std::cout << "Parent destructor" << std::endl;
    }
};

// �ڽ� Ŭ���� Child ����
class Child : public Parent {
public:
    Child (){
        std::cout << "Child Created." << std::endl;
    }
    void show() override {  // �θ� Ŭ������ �Լ��� �������̵�
        std::cout << "Child class show function" << std::endl;
    }
    void childOnly() {
        std::cout << "Child class only function" << std::endl;
    }
    ~Child() {  // �Ҹ���
        std::cout << "Child destructor" << std::endl;
    }
};

int main() {
    Parent* p = new Parent();   // Parent Ÿ���� �����ͷ� Parent ��ü ����
    p->show();                  // Parent�� show �Լ� ȣ��
    p->parentOnly();            // Parent Ŭ������ parentOnly �Լ� ȣ��

    std::cout << "---------\n";

    Parent* pc = new Child();  // Parent Ÿ���� �����ͷ� Child ��ü ����. Parent ������ -> Child ������
    pc->show();  // �������� ���� Child�� show �Լ� ȣ��
    pc->parentOnly();  // Parent Ŭ������ parentOnly �Լ� ȣ��
    //pc->childOnly();  // Parent Ŭ�������� childOnly �Լ��� �����Ƿ� ȣ�� �Ұ���

    std::cout << "---------\n";

    Child* c = new Child;  // Child ��ü ����. Parent ������ -> Child ������
    c->show();  // Child Ŭ������ show �Լ� ȣ��
    c->parentOnly();  // Parent Ŭ������ parentOnly �Լ� ȣ��
    c->childOnly();  // Child Ŭ������ childOnly �Լ� ȣ��

    std::cout << "---------\n";
    delete p;   // �Ҵ�� �޸� ����, Parent�� �Ҹ��� ȣ��
    std::cout << "---------\n";
    delete pc;  // �Ҵ�� �޸� ����, Child�� �Ҹ��ڸ� ȣ���� �� Parent�� �Ҹ��� ȣ��
    std::cout << "---------\n";
    delete c;  // �Ҵ�� �޸� ����, Child�� �Ҹ��ڸ� ȣ���� �� Parent�� �Ҹ��� ȣ��
    return 0;
}
