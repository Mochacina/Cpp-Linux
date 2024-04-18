#include <iostream>
#include <string>

using namespace std;

class Person {
private:
    string name;
    int age;

public:
    Person(string n, int a) : name(n), age(a) {}

    static bool compareAges(const Person& p1, const Person& p2) {
        return p1.age < p2.age;
    }
};

int main() {
    Person alice("Alice", 30);
    Person bob("Bob", 25);

    bool isAliceOlder = Person::compareAges(alice, bob);
    cout << "Alice is older than Bob: " << (isAliceOlder ? "No" : "Yes") << endl;

    return 0;
}