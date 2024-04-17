#include <iostream>
#include <string>

using namespace std;

class Person {
private:
    string name;
    int age;

public:
    Person(string n, int a) : name(n), age(a) {}  // ������

    // ������ ��� �Լ�
    void display() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }

    // ���� ��� �Լ�
    static void printPersonInfo(const Person& p) {
        // ��ü �ν��Ͻ��� ���� ������ ����� ����
        cout << "Printing from static function: ";
        p.display();  // ������ ��� �Լ� ȣ��
    }
};

int main() {
    Person person("John Doe", 30);  // Person ��ü ����
    person.display();
    Person::printPersonInfo(person);  // ���� �Լ��� ���� ���� ���

    return 0;
}