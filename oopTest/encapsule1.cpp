#include <iostream>
#include <string>

using namespace std;

class Person {
private:
    string name;  // ����� ���
    int age;      // ����� ���

public:
    Person(string n, int a) : name(n), age(a) {}

    // �̸��� �����ϴ� �޼ҵ�
    void setName(string n) {
        if (!n.empty()) {
            name = n;
        }
    }

    // �̸��� �������� �޼ҵ�
    string getName() const {
        return name;
    }

    // ���̸� �����ϴ� �޼ҵ�
    void setAge(int a) {
        if (a > 0) {
            age = a;
        }
    }

    // ���̸� �������� �޼ҵ�
    int getAge() const {
        return age;
    }
};

int main(){
    Person person("Soh", 25);

    cout << person.getName() << ", " << person.getAge() << "\n"; 
    person.setName("John");
    person.setAge(20);
    cout << person.getName() << ", " << person.getAge() << "\n"; 

    return 0;
}