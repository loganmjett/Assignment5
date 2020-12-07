// Person base class implementation

#include "Person.h"

Person::Person() {
    id = -1;
    name = "no name";
    level = "no level";
}

Person::Person(int id, string name, string level) {
    this->id = id;
    this->name = name;
    this->level = level;
}

Person::Person(int id) {
    this->id = id;
    this->name = "no name";
    this->level = "no level";
}

Person::Person(const Person& other) {
    this->id = other.id;
    this->name = other.name;
    this->level = other.level;
}

Person::~Person() {}

string Person::toString() const {
    return "[Person] ID: " + to_string(id) + ", Name: " + name + ", Level: " + level;
}

bool Person::operator==(const Person& other) const {
    return (this->id == other.id);
}

bool Person::operator!=(const Person& other) const {
    return (this->id != other.id);
}

bool Person::operator>(const Person& other) const {
    return (this->id > other.id);
}

bool Person::operator<(const Person& other) const {
    return (this->id < other.id);
}

ostream& operator<<(ostream& os, const Person& other) {
    string str = other.toString();
    os << str;
    return os;
}
