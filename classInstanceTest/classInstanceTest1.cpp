#include <iostream>
#include <string>

using namespace std;

class Person {
private:
    string name;
    int age;

public:
    Person(string n, int a) : name(n), age(a) {}  // 생성자

    // 비정적 멤버 함수
    void display() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }

    // 정적 멤버 함수
    static void printPersonInfo(const Person& p) {
        // 객체 인스턴스를 통해 비정적 멤버에 접근
        cout << "Printing from static function: ";
        p.display();  // 비정적 멤버 함수 호출
    }
};

int main() {
    Person person("John Doe", 30);  // Person 객체 생성
    person.display();
    Person::printPersonInfo(person);  // 정적 함수를 통해 정보 출력

    return 0;
}