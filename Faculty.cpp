// Faculty implementation

#include "Faculty.h"

Faculty::Faculty() {
    this->department = "No department";
    this->advisees = new vector<int>();
}

Faculty::Faculty(int id) : Person(id) {
    this->department = "No department";
    this->advisees = new vector<int>();
}

Faculty::Faculty(int id, string name, string level, string department) : Person(id, name, level) {
    this->department = department;
    this->advisees = new vector<int>();
}

Faculty::Faculty(int id, string name, string level, string department, vector<int>* advisees) : Person(id, name, level) {
    this->department = department;
    this->advisees = new vector<int>(*advisees);
}

Faculty::Faculty(const Faculty& other) : Person(other) {
    this->department = other.department;
    this->advisees = new vector<int>(*other.advisees);
}

Faculty::~Faculty() {
    delete advisees;
}

string Faculty::toString() const {
    string ret = "[Faculty] ID: " + to_string(id) + ", Name: " + name + ", Level: " + level + ", Department: " + department + ", Advisees:";
    for(int advisee : *advisees) {
        ret += " " + to_string(advisee);
    }
    return ret;
}
