// Student implementation

#include "Student.h"

Student::Student() {
    major = "No major";
    gpa = -1.0;
    advisor = -1;
}

Student::Student(int id) : Person(id) {
    major = "No major";
    gpa = -1.0;
    advisor = -1;
}

Student::Student(int id, string name, string level, string major, double gpa, int advisor) : Person(id, name, level) {
    this->major = major;
    this->gpa = gpa;
    this->advisor = advisor;
}

Student::Student(const Student& other) : Person(other) {
    this->major = other.major;
    this->gpa = other.gpa;
    this->advisor = other.advisor;
}

Student::~Student() {}

string Student::toString() const {
    return "[Student] ID: " + to_string(id) + ", Name: " + name + ", Level: " + level + ", Major: " + major + ", GPA: " + to_string(gpa) + ", Advisor: " + to_string(advisor);
}
