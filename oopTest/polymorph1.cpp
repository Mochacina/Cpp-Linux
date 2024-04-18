#include <iostream>
using namespace std;

class Animal {
public:
    virtual void speak() {
        cout << "Some animal sound" << endl;
    }
};

class Cat : public Animal {
public:
    void speak() override {
        cout << "Meow" << endl;
    }
};

class Dog : public Animal {
public:
    void speak() override {
        cout << "Woof" << endl;
    }
};

void makeAnimalSpeak(Animal& animal) {
    animal.speak();  // 다형성을 통한 메소드 호출
}

int main() {
    Cat myCat;
    Dog myDog;

    makeAnimalSpeak(myCat);
    makeAnimalSpeak(myDog);

    return 0;
}
