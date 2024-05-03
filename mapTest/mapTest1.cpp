#include <iostream>
#include <map>
#include <string>

// ����ü ����
struct Student {
    std::string name;
    int age;
    double gpa;
};

int main() {
    // map ���� (Ű: �л� �̸�, ��: Student ����ü)
    std::map<std::string, Student> students;

    // ������ �߰�
    students["Alice"] = {"Alice", 20, 3.8};
    students["Bob"] = {"Bob", 22, 3.5};
    students["Charlie"] = {"Charlie", 21, 4.0};

    // ������ ����
    std::cout << "Alice's GPA: " << students["Alice"].gpa << std::endl;

    // ������ ����
    auto it = students.find("Bob");
    if (it != students.end()) {
        students.erase(it);
        std::cout << "Bob has been removed from the map." << std::endl;
    }

    // ��ü ������ ���
    for (const auto& pair : students) {
        std::cout << "Name: " << pair.second.name << ", Age: " << pair.second.age
                  << ", GPA: " << pair.second.gpa << std::endl;
    }

    return 0;
}