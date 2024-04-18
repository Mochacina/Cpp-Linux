#include <iostream>
#include <string>

using namespace std;

class Person {
private:
    string name;  // 비공개 멤버
    int age;      // 비공개 멤버

public:
    Person(string n, int a) : name(n), age(a) {}

    // 이름을 설정하는 메소드
    void setName(string n) {
        if (!n.empty()) {
            name = n;
        }
    }

    // 이름을 가져오는 메소드
    string getName() const {
        return name;
    }

    // 나이를 설정하는 메소드
    void setAge(int a) {
        if (a > 0) {
            age = a;
        }
    }

    // 나이를 가져오는 메소드
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