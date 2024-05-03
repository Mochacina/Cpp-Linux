#include <iostream>
#include <map>
#include <string>

// 구조체 정의
struct Student {
    std::string name;
    int age;
    double gpa;
};

int main() {
    // map 생성 (키: 학생 이름, 값: Student 구조체)
    std::map<std::string, Student> students;

    // 데이터 추가
    students["Alice"] = {"Alice", 20, 3.8};
    students["Bob"] = {"Bob", 22, 3.5};
    students["Charlie"] = {"Charlie", 21, 4.0};

    // 데이터 접근
    std::cout << "Alice's GPA: " << students["Alice"].gpa << std::endl;

    // 데이터 제거
    auto it = students.find("Bob");
    if (it != students.end()) {
        students.erase(it);
        std::cout << "Bob has been removed from the map." << std::endl;
    }

    // 전체 데이터 출력
    for (const auto& pair : students) {
        std::cout << "Name: " << pair.second.name << ", Age: " << pair.second.age
                  << ", GPA: " << pair.second.gpa << std::endl;
    }

    return 0;
}